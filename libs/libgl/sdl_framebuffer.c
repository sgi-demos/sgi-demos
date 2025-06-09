//
//  Provide an SDL framebuffer for IRIS GL to render into
//
//  Two types of framebuffers are provided:
//  1. An SDL_texture is updated with IRIS GL's ref rasterizer buffer, and displayed using SDL_RenderCopy & SDL_RenderPresent
//  2. An OpenGL texture is updated with IRIS GL's ref rasterizer buffer, and displayed using glDrawArrays & SDL_GL_SwapWindow
//
//  The OpenGL texture framebuffer is a stepping stone towards having an OpenGL rasterizer, which opens up
//  faster rendering -- especially important for arbitrary window sizes and texture mapping.
//
#include <stdio.h>

#include <SDL.h>
#include <SDL_opengles2.h>

#include "sdl_framebuffer.h"
#include "sdl_events.h"

static bool useGLFramebuffer = false;

typedef struct
{
    // SDL Window
    char title[256];
    SDL_Window* pWindow;
    Uint32 windowID;
    Size2D windowSize;

    // Rendered framebuffer
    Size2D size;                // Framebuffer size (<= window size)
    unsigned char* pSrcPixels;  // Framebuffer source pixels

    // OGL framebuffer
    GLuint  glShaderProg;       // Framebuffer shader
    GLint   glShaderVpSize;     // Viewport size is same as window size
    GLint   glShaderFbSize;      
    GLint   glShaderTexSize;     
    GLuint  glTex;              // Texture object for displaying the framebuffer
    GLsizei glTexSize[2];       // Texture size >= framebuffer size (due to GLES 2^ texture reqmt)
    GLuint  glQuadVBO;          // Quad geometry for displaying the texture
    GLuint  glQuadPosAttrib;

    SDL_GLContext glContext;    // OGL renderer context

    // SDL framebuffer
    SDL_Texture*  pSDLTex;      // Texture for displaying the framebuffer
    SDL_Renderer* pSDLRenderer; // SDL renderer
} SDLFramebuffer;

static SDLFramebuffer fb = (SDLFramebuffer)
{
    .title = {"sgi-demos"},
    .pWindow = NULL,
    .windowID = 0,
    .windowSize = {880, 560},

    .size = {800, 480},
    .pSrcPixels = NULL, 

    // OGL framebuffer
    .glShaderProg = 0,
    .glShaderVpSize = 0,
    .glShaderFbSize = 0,
    .glShaderTexSize = 0,
    .glTex = 0,
    .glTexSize = {0, 0},
    .glQuadVBO = 0,
    .glQuadPosAttrib = 0,
    .glContext = NULL,

    // SDL framebuffer
    .pSDLTex = NULL,
    .pSDLRenderer = NULL,
};

// Shader for displaying the framebuffer texture on a quad which fills the viewport
const GLchar* fbVertexSource =
    "attribute vec4 position;                              \n"
    "varying vec2 texCoord;                                \n"
    "uniform vec2 vpSize;                                  \n"
    "uniform vec2 fbSize;                                  \n"
    "uniform vec2 texSize;                                 \n"
    "void main()                                           \n"
    "{                                                     \n"
    "    // Scale to framebuffer size                      \n"
    "    gl_Position = vec4(position.xyz, 1.0);            \n"
    "    gl_Position.x *= fbSize.x;                        \n"
    "    gl_Position.y *= fbSize.y;                        \n"
    "                                                      \n"
    "    // Translate to framebuffer's lower left          \n"
    "    gl_Position.x -= fbSize.x / 2.0 + 1.0;            \n"
    "    gl_Position.y -= fbSize.y / 2.0 + 1.0;            \n"
    "                                                      \n"
    "    // Ortho project                                  \n"
    "    gl_Position.x += 1.0;                             \n"
    "    gl_Position.x *= 2.0 / vpSize.x;                  \n"
    "    gl_Position.y += 1.0;                             \n"
    "    gl_Position.y *= 2.0 / vpSize.y;                  \n"
    "                                                      \n"
    "    // Framebuffer subrectangle from overall texture  \n"
    "    texCoord.x = position.x * fbSize.x / texSize.x;   \n"
    "    texCoord.y = -position.y * fbSize.y / texSize.y;  \n"
    "}                                                     \n";

const GLchar* fbFragmentSource =
    "precision mediump float;                              \n"
    "varying vec2 texCoord;                                \n"
    "uniform sampler2D texSampler;                         \n"
    "void main()                                           \n"
    "{                                                     \n"
    "    gl_FragColor = texture2D(texSampler, texCoord);   \n"
    "}                                                     \n";

void checkShaderBuilt(const char* shader_name, GLenum status, GLuint shader) 
{
    GLint success;
    glGetShaderiv(shader, status, &success);
    if (success)
        printf("INFO: %s id %d build OK\n", shader_name, shader);
    else
        printf("ERROR: %s id %d build FAILED!\n", shader_name, shader);
}

void updateShaderVars()
{
    glUseProgram(fb.glShaderProg);

    GLfloat windowSize[2] = {fb.windowSize.width, fb.windowSize.height};
    glUniform2fv(fb.glShaderVpSize, 1, windowSize);
    
    GLfloat fbSize[2] = {fb.size.width, fb.size.height};
    glUniform2fv(fb.glShaderFbSize, 1, fbSize);
    
    GLfloat texSize[2] = {fb.glTexSize[0], fb.glTexSize[1]};
    glUniform2fv(fb.glShaderTexSize, 1, texSize);
}

void initShader()
{
    // Create and compile vertex shader
    GLuint fbVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fbVertexShader, 1, &fbVertexSource, NULL);
    glCompileShader(fbVertexShader);
    checkShaderBuilt("fbVertexShader", GL_COMPILE_STATUS, fbVertexShader);

    // Create and compile fragment shader
    GLuint fbFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fbFragmentShader, 1, &fbFragmentSource, NULL);
    glCompileShader(fbFragmentShader);
    checkShaderBuilt("fbFragmentShader", GL_COMPILE_STATUS, fbFragmentShader);

    // Link vertex and fragment shader into shader program
    fb.glShaderProg = glCreateProgram();
    glAttachShader(fb.glShaderProg, fbVertexShader);
    glAttachShader(fb.glShaderProg, fbFragmentShader);
    glBindAttribLocation(fb.glShaderProg, fb.glQuadPosAttrib, "position");
    glEnableVertexAttribArray(fb.glQuadPosAttrib);
    glLinkProgram(fb.glShaderProg);

    // Get shader variables and initalize them
    fb.glShaderVpSize  = glGetUniformLocation(fb.glShaderProg, "vpSize");
    fb.glShaderFbSize  = glGetUniformLocation(fb.glShaderProg, "fbSize");
    fb.glShaderTexSize = glGetUniformLocation(fb.glShaderProg, "texSize");
    
    updateShaderVars();
}

void initGeometry()
{
    // Create vertex buffer object and copy vertex data into them
    glGenBuffers(1, &fb.glQuadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, fb.glQuadVBO);
    GLfloat quadVertices[] = 
    {
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
}

void sdlInitWindow()
{  
    // Create SDL window
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_version version;
    SDL_GetVersion(&version);
    printf("INFO: SDL version: %d.%d.%d\n", version.major, version.minor, version.patch);

    // OpenGLES framebuffer
    if (useGLFramebuffer) 
    {
        // Init OpenGLES driver and context
        SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); 
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetSwapInterval(1); // 1 = sync framerate to refresh rate (no screen tearing)

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        // Explicitly set channel depths, otherwise we might get some < 8
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

        fb.pWindow = SDL_CreateWindow(
            fb.title,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            fb.windowSize.width, fb.windowSize.height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
        );

        fb.glContext = SDL_GL_CreateContext(fb.pWindow);

        printf("INFO: GL vendor: %s\n", glGetString(GL_VENDOR));
        printf("INFO: GL renderer: %s\n", glGetString(GL_RENDERER));
        printf("INFO: GL version: %s\n", glGetString(GL_VERSION));

        glDisable(GL_DEPTH_TEST);        
        glClearColor(0, 0, 0, 0);
        glViewport(0, 0, fb.windowSize.width, fb.windowSize.height);
    }

    // SDL framebuffer
    else
    {
        fb.pWindow = SDL_CreateWindow(
            fb.title,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            fb.windowSize.width, fb.windowSize.height,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

        fb.pSDLRenderer = SDL_CreateRenderer(fb.pWindow, -1, 0);
        SDL_SetRenderDrawColor(fb.pSDLRenderer, 0, 0, 0, 0);
    }

    fb.windowID = SDL_GetWindowID(fb.pWindow);
    SDL_StartTextInput();
}

void sdlResizeWindow(Uint32 windowID, Size2D windowSize)
{
    if (windowID == fb.windowID)
    {
        fb.windowSize = windowSize;
        
        // TODO: For now, framebuffer size is static.  Future: make framebuffer and
        // window size the same, and rebuild framebuffer texture here on resizes (and
        // communicate size change back to IRIS GL)
        if (useGLFramebuffer)
        {
            glViewport(0, 0, fb.windowSize.width, fb.windowSize.height);
            updateShaderVars();
        }
    }
}

void sdlOpenWindow(char *title, int32_t frameWidth, int32_t frameHeight)
{
    strncpy(fb.title, title, sizeof(fb.title));

#ifndef __EMSCRIPTEN__
    // Emscripten sets window title to 'this.program' on calling SDL_SetWindowTitle
    if (fb.pWindow)
        SDL_SetWindowTitle(fb.pWindow, fb.title);
#endif

    fb.size = (Size2D) { frameWidth, frameHeight };
    
    // how does the timing on this work, it needs to be called
    // before sdlInitWindow so SDL framebuffer can be initialized at
    // the correct size???
}

void sdlSetFramebufferSource(unsigned char* pSrcPixels)
{
    fb.pSrcPixels = pSrcPixels;
}

static int clamp(int v, int low, int high)          { return v > high ? high : (v < low ? low : v); }
static bool would_clamp(int v, int low, int high)   { return v < low || v > high; }
static int windowToFramebufferOffsetX()             { return fb.windowSize.width / 2 - fb.size.width / 2; }
static int windowToFramebufferOffsetY()             { return fb.windowSize.height / 2 - fb.size.height / 2; }
static int framebufferX(int windowX)                { return windowX - windowToFramebufferOffsetX(); }
static int framebufferY(int windowY)                { return fb.windowSize.height - windowY - windowToFramebufferOffsetY(); }

int sdlClampToFramebufferX(int windowX)             { return clamp(framebufferX(windowX), 1, fb.size.width - 1); }
int sdlClampToFramebufferY(int windowY)             { return clamp(framebufferY(windowY), 1, fb.size.height - 1); }

bool sdlInsideFramebuffer(int windowX, int windowY)
{
    // For now, window and framebuffer dimensions may differ, so convert
    // incoming window coords to framebuffer coords, including inverting y    
    return !would_clamp(framebufferX(windowX), 1, fb.size.width - 1) 
        && !would_clamp(framebufferY(windowY), 1, fb.size.height - 1);
}

// Create grey checkerboard surface with yellow border for testing
// NOTE: Caller must free returned surface when they are done with it!
SDL_Surface* createTestSurface(int width, int height)
{
    const int bitsPerPixel = 32;

    SDL_Surface* pSurface = SDL_CreateRGBSurface(0, width, height, bitsPerPixel, 0, 0, 0, 0);
    unsigned int* surfacePixels = (unsigned int*)pSurface->pixels;
    
    for (int y = 0; y < pSurface->h; ++y)
        for (int x = 0; x < pSurface->w; ++x)
        {
            const int i = x + y * pSurface->w;
            if (y == 0 || x == 0 || y == pSurface->h-1 || x == pSurface->w - 1)
                surfacePixels[i] = 0xff00ffff; // yellow
            else 
            {
                const int checkerSize = 100, halfChecker = checkerSize / 2,
                        yMod = y % checkerSize, xMod = x % checkerSize;
                if ((yMod < halfChecker && xMod < halfChecker) 
                    || (yMod >= halfChecker && xMod >= halfChecker))
                    surfacePixels[i] = 0xffc4c4c4; // light grey
                else
                    surfacePixels[i] = 0xff808080; // dark grey
            }
        }

    return pSurface;
}

int min(int x, int y) { return x < y ? x : y; }
int nextPowerOfTwo(int val) { int power = 1; while (power < val) power *= 2; return power; }

void sdlInitFramebufferTexture()
{
    if (useGLFramebuffer) 
    {
        // Don't exceed max GL texture size
        // - Also may need to increase WASM heap via -s TOTAL_MEMORY
        // - Typical framebuffer sizes and memory usage:
        //   5120x2880 57MB
        //   3840x2160 32MB
        //   2738x2048 22MB
        //   1920x1080 8MB
        //   1280x1024 5MB
        GLint maxTextureSize = 256;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
        int fbWidth = min(fb.size.width, maxTextureSize),
            fbHeight = min(fb.size.height, maxTextureSize);
        printf("INFO: framebuffer size=%dx%d  clamped framebuffer size=%dx%d\n", fb.size.width, fb.size.height, fbWidth, fbHeight);

        // Create texture at size of framebuffer
        SDL_Surface* fbTestImage = createTestSurface(fbWidth, fbHeight);

        // OpenGLES requires power of 2 dimension textures, so create the smallest
        // power of 2 image that fits the framebuffer, along with 1 texel border
        int bitsPerPixel = 32;
        int texWidth = nextPowerOfTwo(fbTestImage->w + 2),
            texHeight = nextPowerOfTwo(fbTestImage->h + 2);
        SDL_Surface* fbTexture = SDL_CreateRGBSurface(0, texWidth, texHeight, bitsPerPixel, 0, 0, 0, 0);

        // Clear the texture and copy the initial checkerboard framebuffer into it, centered
        unsigned int* texPixels = (unsigned int*)fbTexture->pixels;
        memset(texPixels, 0x0, fbTexture->w * fbTexture->h * fbTexture->format->BytesPerPixel);
        SDL_Rect destRect = {1, fbTexture->h - fbTestImage->h - 1, fbTestImage->w + 1, fbTexture->h - 1};
        SDL_BlitSurface(fbTestImage, NULL, fbTexture, &destRect);
        
        // Generate a GL texture object and bind it as current
        fb.glTexSize[0] = (GLsizei)fbTexture->w;
        fb.glTexSize[1] = (GLsizei)fbTexture->h;
        glGenTextures(1, &fb.glTex);
        glBindTexture(GL_TEXTURE_2D, fb.glTex);

        // Set the GL texture's wrapping and stretching properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Upload SDL image to GL texture
        GLint level = 0, border = 0;
        glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, 
                     fb.glTexSize[0], fb.glTexSize[1], 
                     border, GL_RGBA, GL_UNSIGNED_BYTE,
                     fbTexture->pixels);

        // Check for errors
        char texture_info[256];
        snprintf(texture_info, sizeof(texture_info), "texture %d (%dx%d)", 
            fb.glTex, fb.glTexSize[0], fb.glTexSize[1]);
        GLenum glError = glGetError();
        if (glError == GL_NO_ERROR)
            printf("OK: texture built %s\n", texture_info);
        else
            printf("ERROR: texture not built %s\n", texture_info);

        // Unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Update shader with texture size
        updateShaderVars();

        SDL_FreeSurface(fbTestImage);
        SDL_FreeSurface(fbTexture);
    }
    else
    {
        // Create SDL texture from checkerboard surface
        SDL_Surface* pSurface = createTestSurface(fb.size.width, fb.size.height);
        fb.pSDLTex = SDL_CreateTextureFromSurface(fb.pSDLRenderer, pSurface);
        SDL_FreeSurface(pSurface);
    }
}

void sdlUpdateFramebufferTexture()
{
    if (fb.pSrcPixels)
    {
        if (useGLFramebuffer) 
        {
            glBindTexture(GL_TEXTURE_2D, fb.glTex);
            GLint level = 0, xoffset = 0, yoffset = 0;
            glTexSubImage2D(GL_TEXTURE_2D, level, 
                            xoffset, yoffset, 
                            fb.size.width, fb.size.height, 
                            GL_RGBA, GL_UNSIGNED_BYTE,
                            fb.pSrcPixels);
            // TODO: watch out for framebuffer exceeding gl texture size
        }
        else 
        {       
            int pitch = fb.size.width * 4;
            SDL_UpdateTexture(fb.pSDLTex, NULL, fb.pSrcPixels, pitch);
        }
    }
}

void sdlFreeFramebufferTexture()
{
    if (fb.glTex > 0)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &fb.glTex);
        fb.glTex = 0;
    }
    
    if (fb.pSDLTex)
    {
        SDL_DestroyTexture(fb.pSDLTex);
        fb.pSDLTex = NULL;
    }
}

void sdlRenderFramebufferTexture()
{
    // Draw the quad VBO with texture bound and use framebuffer shader
    if (useGLFramebuffer)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, fb.glTex);
        glUseProgram(fb.glShaderProg);
        glBindBuffer(GL_ARRAY_BUFFER, fb.glQuadVBO);
        glVertexAttribPointer(fb.glQuadPosAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindTexture(GL_TEXTURE_2D, 0);

        SDL_GL_SwapWindow(fb.pWindow);
    }
    else
    {  
        SDL_RenderClear(fb.pSDLRenderer);
        SDL_Rect destRect = (SDL_Rect) {
            .x = windowToFramebufferOffsetX(), 
            .y = windowToFramebufferOffsetY(), 
            fb.size.width, 
            fb.size.height };
        SDL_RenderCopy(fb.pSDLRenderer, fb.pSDLTex, NULL, &destRect);

        SDL_RenderPresent(fb.pSDLRenderer);
    }
}