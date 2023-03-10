//
//  OpenGLES framebuffer - displays an image in the center of the window
//
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#else
#include <SDL2/SDL.h>
#endif
#include "sdl_events.h"
#include "EM_MAIN_DEFN.h"

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
    "    // Center image in viewport                            \n"
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

void updateShader()
{
    float viewport[2] = {sdlViewport().x, sdlViewport().y};
   
    glUseProgram(quadShaderProgram);
    glUniform2fv(shaderViewport, 1, viewport);
    glUniform2fv(shaderImageSize, 1, imageSize);
    glUniform2fv(shaderTexSize, 1, texSize);
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

    // Get shader variables and initialize them
    shaderViewport = glGetUniformLocation(quadShaderProgram, "viewport");
    shaderImageSize = glGetUniformLocation(quadShaderProgram, "imageSize");
    shaderTexSize = glGetUniformLocation(quadShaderProgram, "texSize");

    updateShader();
}

void initGeometry()
{
   // Create vertex buffer object and copy vertex data into them
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
    int winWidth = sdlWindowSize().width,
        winHeight = sdlWindowSize().height;

    // Don't exceed max GL texture size
    GLint maxTextureSize = 256;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    winWidth = min(winWidth, maxTextureSize);
    winHeight = min(winHeight, maxTextureSize);

    int bitsPerPixel = 32;

    #ifdef EM_CHILD_MAIN
        // Copy GL framebuffer into image
        Size2D fbSize = sdlFramebufferSize();
        SDL_Surface* bgImage = SDL_CreateRGBSurface(0, fbSize.width, fbSize.height, bitsPerPixel, 0, 0, 0, 0);
        unsigned int* bgImagePixels = (unsigned int*)bgImage->pixels;
        unsigned char* pFramebuffer = sdlFramebuffer();
        memcpy(bgImagePixels, pFramebuffer, fbSize.width*fbSize.height*4);       
    #else
        // Create grey checkerboard image with yellow border
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
    #endif

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
    //else
    //    printf("OK: Texture %d (%dx%d) built.\n", textureObj, bgImageTexture->w, bgImageTexture->h);

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

void updateTexture()
{
    // TBD: Use subtexture updates instead of rebuilding texture every frame
	if (0)
	{
        static unsigned char grayLevel = 0;
        unsigned int* texPixels = (unsigned int*)bgImageTexture->pixels;
        memset(texPixels, grayLevel, bgImageTexture->w * bgImageTexture->h * bgImageTexture->format->BytesPerPixel);

        GLint level = 0, xoffset = 0, yoffset = 0;
        GLsizei width = bgImageTexture->w, height = bgImageTexture->h;
        GLenum format = GL_RGBA, type = GL_UNSIGNED_BYTE;
        const GLvoid * data = texPixels;

        glBindTexture(GL_TEXTURE_2D, textureObj);
        glTexSubImage2D(GL_TEXTURE_2D, level, xoffset, yoffset, width, height, format, type, data);
        glBindTexture(GL_TEXTURE_2D, 0);

        grayLevel = (grayLevel + 10) % 255;
	}
}

void redraw()
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the quad VBO with texture bound and image texture shader
    glBindTexture(GL_TEXTURE_2D, textureObj);
    glUseProgram(quadShaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Swap front/back framebuffers
    sdlPresent();
}

void main_loop(void* main_loop_arg) 
{    
    sdlProcessEvents();

    #ifdef EM_CHILD_MAIN
        // Update texture every frame from child app's framebuffer
        initTexture();        // Re-initialize texture if window resized
    #else
        if (cam2DWindowResized())
            initTexture();
    #endif

    // Update shader if view changed
    if (sdlViewChanged())
        updateShader();

    // Run child main loop
    extern void child_main_loop(void *main_loop_arg);
    child_main_loop(main_loop_arg);

    redraw();
}

int main(int argc, char** argv)
{
    // Initialize SDL window
    sdlInit("sgi-demos");

    // Initialize OGLES graphics
    initShaders();
    initGeometry();
    initTexture();

    // Run child main
    child_main(argc, argv);

    // Start the main loop
    void* main_loop_arg = NULL; // User-defined data to pass to main_loop() and child_main_loop()
    #ifdef __EMSCRIPTEN__
        int fps = 0; // Set to 0 to use browser's requestAnimationFrame (recommended)
        int simulate_infinite_loop = 1;
        emscripten_set_main_loop_arg(main_loop, main_loop_arg, fps, simulate_infinite_loop);
    #else
        while(true) 
            main_loop(main_loop_arg);
    #endif

    freeTexture();
    return 0;
}