//#include <algorithm>
//#include <SDL.h>
//#include <SDL_opengles2.h>
#include "camera2D.h"

#define false 0
#define true 1

static const int cInitWidth = 800, cInitHeight = 480;
static const float cZoomMin = 0.1, cZoomMax = 10.0f;

typedef struct {
    bool    updated;
    bool    winResized;
    Size2D  winSize;
    Vec2D   viewport;
    Vec2D   basePan;
    Vec2D   pan;
    float   zoom;
    float   aspect;
} Camera2D;

static Camera2D activeCam = (Camera2D) 
{ 
    .updated    = true, 
    .winResized = true, 
    .winSize    = (Size2D) { .width = cInitWidth, .height = cInitHeight },
    .viewport   = (Vec2D) { .x = cInitWidth, .y = cInitHeight },
    .basePan    = (Vec2D) { .x = 0.0, .y = 0.0 },
    .pan        = (Vec2D) { .x = 0.0, .y = 0.0 },
    .zoom       = 1.0,
    .aspect     = cInitWidth / (float)cInitHeight
};
   
bool cam2DUpdated()
{
    bool updated = activeCam.updated;
    activeCam.updated = false;
    return updated;
}

bool cam2DWindowResized()
{
    bool resized = activeCam.winResized;
    activeCam.winResized = false;
    return resized;
}

Size2D cam2DWindowSize() { return activeCam.winSize; }
Vec2D cam2DViewport() { return activeCam.viewport; }
Vec2D cam2DBasePan() { return activeCam.basePan; }
Vec2D cam2DPan() { return activeCam.pan; }
float cam2DZoom() { return activeCam.zoom; }
float cam2DAspect() { return activeCam.aspect; }

void cam2DSetWindowSize(int width, int height)
{
    if (activeCam.winSize.width != width || activeCam.winSize.height != height)
    {
        activeCam.winResized = true;
        activeCam.winSize = (Size2D) { .width = 0, .height = 0 };
        activeCam.viewport = (Vec2D) { .x = (float)width, .y = (float)height };
        cam2DSetAspect(width / (float)height);
    }
}

void cam2DSetPan (Vec2D pan) 
{ 
    activeCam.pan = pan;
    activeCam.updated = true; 
}    

void cam2DSetPanDelta (Vec2D panDelta) 
{ 
    activeCam.pan.x += panDelta.x; 
    activeCam.pan.y += panDelta.y;
    activeCam.updated = true; 
}

#define MAX(x,y)  (x > y ? x : y)
#define MIN(x,y)  (x < y ? x : y)
float clamp (float val, float lo, float hi) 
{ 
    return MAX(lo, MIN(val, hi)); 
}

void cam2DSetZoom (float zoom) 
{ 
    activeCam.zoom = clamp(zoom, cZoomMin, cZoomMax);
    activeCam.updated = true; 
}

void cam2DSetZoomDelta (float zoomDelta) 
{ 
    activeCam.zoom = clamp(activeCam.zoom + zoomDelta, cZoomMin, cZoomMax);
    activeCam.updated = true; 
}

void cam2DSetAspect (float aspect)
{ 
    activeCam.aspect = aspect; 
    activeCam.updated = true; 
}

void cam2DSetBasePan () 
{ 
    activeCam.basePan = activeCam.pan;
}

// Convert from normalized window coords (x,y) in ([0.0, 1.0], [1.0, 0.0]) to device coords ([-1.0, 1.0], [-1.0,1.0])
void cam2DNormWindowToDevice (float normWinX, float normWinY, float* deviceX, float* deviceY)
{
    *deviceX = (normWinX - 0.5f) * 2.0f;
    *deviceY = (1.0f - normWinY - 0.5f) * 2.0f;
}

// Convert from window coords (x,y) in ([0, winSize.width], [winSize.height, 0]) to device coords ([-1.0, 1.0], [-1.0,1.0])
void cam2DWindowToDevice (int winX, int winY, float* deviceX, float* deviceY)
{
    cam2DNormWindowToDevice(winX / (float)activeCam.winSize.width,  
                            winY / (float)activeCam.winSize.height,
                            deviceX, deviceY);
}

// Convert from device coords ([-1.0, 1.0], [-1.0,1.0]) to world coords ([-inf, inf], [-inf, inf])
void cam2DDeviceToWorld (float deviceX, float deviceY, float* worldX, float* worldY)
{
    *worldX = deviceX / activeCam.zoom - activeCam.pan.x;
    *worldY = deviceY / activeCam.aspect / activeCam.zoom - activeCam.pan.y;
}

// Convert from window coords (x,y) in ([0, windowWidth], [windowHeight, 0]) to world coords ([-inf, inf], [-inf, inf])
void cam2DWindowToWorld(int winX, int winY, float* worldX, float* worldY)
{
    float deviceX, deviceY;
    cam2DWindowToDevice(winX, winY, &deviceX, &deviceY);   
    cam2DDeviceToWorld(deviceX, deviceY, worldX, worldY);
}

// Convert from normalized window coords (x,y) in in ([0.0, 1.0], [1.0, 0.0]) to world coords ([-inf, inf], [-inf, inf])
void cam2DNormWindowToWorld(float normWinX, float normWinY, float* worldX, float* worldY)
{
    float deviceX, deviceY;
    cam2DNormWindowToDevice(normWinX, normWinY, &deviceX, &deviceY);
    cam2DDeviceToWorld(deviceX, deviceY, worldX, worldY);
}
