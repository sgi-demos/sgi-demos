/*
    OpenGLES framebuffer - displays an image in the center of the window
*/
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengles2.h>

#include "camera2D.h"
#include "sdl_events.h"

// Geometry
GLuint triangleVbo = 0;
GLuint quadVbo = 0;

// Texture
SDL_Surface* bgImageTexture = NULL;
GLuint textureObj = 0;

// Shader vars
const GLint positionAttrib = 0;
GLint shaderPan, shaderZoom, shaderAspect, shaderViewport, shaderImageSize, shaderTexSize;
float imageSize[2] = {0.0f, 0.0f}, texSize[2] = {0.0f, 0.0f};

// Image quad vertex & fragment shaders
GLuint quadShaderProgram = 0;
const GLchar* quadVertexSource =
    "attribute vec4 position;                                   \n"
    "varying vec2 texCoord;                                     \n"
    "uniform vec2 viewport;                                     \n"
    "uniform vec2 imageSize;                                    \n"
    "uniform vec2 texSize;                                      \n"
    "void main()                                                \n"
    "{                                                          \n"
    "    gl_Position = vec4(position.xyz, 1.0);                 \n"
    "    gl_Position.x *= imageSize.x;                          \n"
    "    gl_Position.y *= imageSize.y;                          \n"
    "                                                           \n"
    "    // Translate to lower left viewport                    \n"
    "    gl_Position.x -= imageSize.x / 2.0 + 1.0;              \n"
    "    gl_Position.y -= imageSize.y / 2.0 + 1.0;              \n"
    "                                                           \n"
    "    // Ortho projection                                    \n"
    "    gl_Position.x += 1.0;                                  \n"
    "    gl_Position.x *= 2.0 / viewport.x;                     \n"
    "    gl_Position.y += 1.0;                                  \n"
    "    gl_Position.y *= 2.0 / viewport.y;                     \n"
    "                                                           \n"
    "    // Image subrectangle from overall texture             \n"
    "    texCoord.x = position.x * imageSize.x / texSize.x;     \n"
    "    texCoord.y = -position.y * imageSize.y / texSize.y;    \n"
    "}                                                          \n";

const GLchar* quadFragmentSource =
    "precision mediump float;                                   \n"
    "varying vec2 texCoord;                                     \n"
    "uniform sampler2D texSampler;                              \n"
    "void main()                                                \n"
    "{                                                          \n"
    "    gl_FragColor = texture2D(texSampler, texCoord);        \n"
    "}                                                          \n";

// Colorful triangle vertex & fragment shaders
GLuint triShaderProgram = 0;
const GLchar* triVertexSource =
    "uniform vec2 pan;                             \n"
    "uniform float zoom;                           \n"
    "uniform float aspect;                         \n"
    "attribute vec4 position;                      \n"
    "varying vec3 color;                           \n"
    "void main()                                   \n"
    "{                                             \n"
    "    gl_Position = vec4(position.xyz, 1.0);    \n"
    "    gl_Position.xy += pan;                    \n"
    "    gl_Position.xy *= zoom;                   \n"
    "    gl_Position.y *= aspect;                  \n"
    "    color = gl_Position.xyz + vec3(0.5);      \n"
    "}                                             \n";

const GLchar* triFragmentSource =
    "precision mediump float;                     \n"
    "varying vec3 color;                          \n"
    "void main()                                  \n"
    "{                                            \n"
    "    gl_FragColor = vec4 ( color, 1.0 );      \n"
    "}                                            \n";

void updateShader()
{
    float viewport[2], pan[2], zoom, aspect;
    viewport[0] = cam2DViewport().x;
    viewport[1] = cam2DViewport().y;
    pan[0] = cam2DPan().x;
    pan[1] = cam2DPan().y;
    zoom = cam2DZoom();
    aspect = cam2DAspect();
    
    glUseProgram(quadShaderProgram);
    glUniform2fv(shaderViewport, 1, viewport);
    glUniform2fv(shaderImageSize, 1, imageSize);
    glUniform2fv(shaderTexSize, 1, texSize);

    glUseProgram(triShaderProgram);
    glUniform2fv(shaderPan, 1, pan);
    glUniform1f(shaderZoom, zoom); 
    glUniform1f(shaderAspect, aspect);
}

GLuint initShader(const GLchar* vertexSource, const GLchar* fragmentSource)
{
    // Create and compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link vertex and fragment shader into shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindAttribLocation(shaderProgram, positionAttrib, "position");
    glEnableVertexAttribArray(positionAttrib);
    glLinkProgram(shaderProgram);

    return shaderProgram;
}

void initShaders()
{
    // Compile & link shaders
    quadShaderProgram = initShader(quadVertexSource, quadFragmentSource);
    triShaderProgram = initShader(triVertexSource, triFragmentSource);

    // Get shader variables and initalize them
    shaderViewport = glGetUniformLocation(quadShaderProgram, "viewport");
    shaderImageSize = glGetUniformLocation(quadShaderProgram, "imageSize");
    shaderTexSize = glGetUniformLocation(quadShaderProgram, "texSize");

    shaderPan = glGetUniformLocation(triShaderProgram, "pan");
    shaderZoom = glGetUniformLocation(triShaderProgram, "zoom");    
    shaderAspect = glGetUniformLocation(triShaderProgram, "aspect");
    
    updateShader();
}

void initGeometry()
{
   // Create vertex buffer objects and copy vertex data into them
    glGenBuffers(1, &quadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    float quadVertices[] = 
    {
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &triangleVbo);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo);
    float triangleVertices[] = 
    {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);  
 }

int min(int x, int y)
{
    return x < y ? x : y;
}

int nextPowerOfTwo(int val)
{
    int power = 1;
    while (power < val)
        power *= 2;
    return power;
}

void freeTexture()
{
    // Free existing SDL image and GL texture
    if (bgImageTexture)
    {
        SDL_FreeSurface (bgImageTexture);
        bgImageTexture = NULL;
    }
    if (textureObj > 0)
    {
        glDeleteTextures(1, &textureObj);
        textureObj = 0;
    }
}

void initTexture()
{
    freeTexture();

    // Create background image at size of window
    int winWidth = cam2DWindowSize().width,
        winHeight = cam2DWindowSize().height;

    // Don't exceed max GL texture size
    GLint maxTextureSize = 256;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    winWidth = min(winWidth, maxTextureSize);
    winHeight = min(winHeight, maxTextureSize);

    // Create grey checkerboard image with yellow border
    int bitsPerPixel = 32;
    SDL_Surface* bgImage = SDL_CreateRGBSurface(0, winWidth, winHeight, bitsPerPixel, 0, 0, 0, 0);
    unsigned int* bgImagePixels = (unsigned int*)bgImage->pixels;
    for (int y = 0; y < bgImage->h; ++y)
        for (int x = 0; x < bgImage->w; ++x)
        {
            const int i = x+y*bgImage->w;
            if (y == 0 || x == 0 || y == bgImage->h-1 || x == bgImage->w - 1)
                bgImagePixels[i] = 0xff00ffff; // yellow
            else 
            {
                const int checkerSize = 100, halfChecker = checkerSize / 2,
                        yMod = y % checkerSize, xMod = x % checkerSize;
                if ((yMod < halfChecker && xMod < halfChecker) 
                    || (yMod >= halfChecker && xMod >= halfChecker))
                    bgImagePixels[i] = 0xffc4c4c4; // light grey
                else
                    bgImagePixels[i] = 0xff808080; // dark grey
            }
        }

    // OpenGLES requires power of 2 dimension textures, so create the smallest
    // power of 2 image that fits the background image, along with 1 texel border
    int texWidth = nextPowerOfTwo(bgImage->w + 2),
        texHeight = nextPowerOfTwo(bgImage->h + 2);
    bgImageTexture = SDL_CreateRGBSurface(0, texWidth, texHeight, bitsPerPixel, 0, 0, 0, 0);

    // Clear the image and copy the background image into it, centered
    unsigned int* texPixels = (unsigned int*)bgImageTexture->pixels;
    memset(texPixels, 0x0, bgImageTexture->w * bgImageTexture->h * bgImageTexture->format->BytesPerPixel);
    SDL_Rect destRect = {1, bgImageTexture->h - bgImage->h - 1, bgImage->w + 1, bgImageTexture->h - 1};
    SDL_BlitSurface(bgImage, NULL, bgImageTexture, &destRect);
    
    // Build GL texture
    //

    // Generate a GL texture object and bind it as current
    glGenTextures(1, &textureObj);
    glBindTexture(GL_TEXTURE_2D, textureObj);

    // Set the GL texture's wrapping and stretching properties
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Upload SDL image to GL texture
    GLint level = 0, border = 0;
    glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, 
                 bgImageTexture->w, bgImageTexture->h, 
                 border, GL_RGBA, GL_UNSIGNED_BYTE, bgImageTexture->pixels);

    // Check for errors
    GLenum glError = glGetError();
    if (glError != GL_NO_ERROR)
        printf("ERROR: Texture %d (%dx%d) not built, error code %d\n", textureObj, bgImageTexture->w, bgImageTexture->h, glError);
    else
        printf("OK: Texture %d (%dx%d) built.\n", textureObj, bgImageTexture->w, bgImageTexture->h);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Update quad shader
    imageSize[0] = (float)bgImage->w + 2;
    imageSize[1] = (float)bgImage->h + 2;
    texSize[0] = (float)bgImageTexture->w;
    texSize[1] = (float)bgImageTexture->h;
    updateShader();

    SDL_FreeSurface (bgImage); 
}

void redraw()
{
    //static int frameCt = 0;
    //printf("INFO: frame %d\n", frameCt++);

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the background quad VBO with texture bound and image texture shader
    glBindTexture(GL_TEXTURE_2D, textureObj);
    glUseProgram(quadShaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw the foreground triangle VBO with a colorful shader
    // No depth buffering here - triangle is in front by virtue of being drawn after quad
    glUseProgram(triShaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo);
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // Swap front/back framebuffers
    sdlEventsSwapWindow();
}

void mainLoop(void* mainLoopArg) 
{    
    sdlEventsProcess();

    // Re-initialize texture if window resized
    if (cam2DWindowResized())
        initTexture();

    // Update shader if camera changed
    if (cam2DUpdated())
        updateShader();

    // childMainLoop(mainLoopArg);

    redraw();
}

int main(int argc, char** argv)
{
    sdlEventsInit("SGI demo");

    // Initialize graphics
    initShaders();
    initGeometry();
    initTexture();

    // Start the main loop
    void* mainLoopArg = NULL; // User-defined data

#ifdef __EMSCRIPTEN__
    int fps = 0; // Use browser's requestAnimationFrame to determine FPS (recommended)
    int simulate_infinite_loop = 0; // Throw an exception in order to stop execution of the caller
    emscripten_set_main_loop_arg(mainLoop, mainLoopArg, fps, simulate_infinite_loop);
#else
    while(true) 
        mainLoop(mainLoopArg);
#endif

    freeTexture();
    return 0;
}