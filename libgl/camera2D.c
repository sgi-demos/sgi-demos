#include "camera2D.h"

#define false 0
#define true 1

static const int cWinWidth = 800, cWinHeight = 480;
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
    .winSize    = (Size2D){ cWinWidth, cWinHeight },
    .viewport   = (Vec2D) { cWinWidth, cWinHeight },
    .basePan    = (Vec2D) { 0.0, 0.0 },
    .pan        = (Vec2D) { 0.0, 0.0 },
    .zoom       = 1.0,
    .aspect     = cWinWidth / (float)cWinHeight
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

Size2D cam2DWindowSize(){ return activeCam.winSize; }
Vec2D cam2DViewport()   { return activeCam.viewport; }
Vec2D cam2DBasePan()    { return activeCam.basePan; }
Vec2D cam2DPan()        { return activeCam.pan; }
float cam2DZoom()       { return activeCam.zoom; }
float cam2DAspect()     { return activeCam.aspect; }

void cam2DSetWindowSize(Size2D winSize)
{
    if (activeCam.winSize.width != winSize.width || 
        activeCam.winSize.height != winSize.height)
    {
        activeCam.winResized = true;
        activeCam.winSize = winSize; 
        activeCam.viewport = (Vec2D) { .x = (float)winSize.width, 
                                       .y = (float)winSize.height };
        cam2DSetAspect(winSize.width / (float)winSize.height);
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
void cam2DNormWindowToDevice (Vec2D normWin, Vec2D* device)
{
    device->x = (normWin.x - 0.5f) * 2.0f;
    device->y = (1.0f - normWin.y - 0.5f) * 2.0f;
}

// Convert from window coords (x,y) in ([0, winSize.width], [winSize.height, 0]) to device coords ([-1.0, 1.0], [-1.0,1.0])
void cam2DWindowToDevice (Pixel2D win, Vec2D* device)
{
    Vec2D normWin = { win.x / (float)activeCam.winSize.width,  
                      win.y / (float)activeCam.winSize.height };
    cam2DNormWindowToDevice(normWin, device);
}

// Convert from device coords ([-1.0, 1.0], [-1.0,1.0]) to world coords ([-inf, inf], [-inf, inf])
void cam2DDeviceToWorld (Vec2D device, Vec2D* world)
{
    world->x = device.x / activeCam.zoom - activeCam.pan.x;
    world->y = device.y / activeCam.aspect / activeCam.zoom - activeCam.pan.y;
}

// Convert from window coords (x,y) in ([0, windowWidth], [windowHeight, 0]) to world coords ([-inf, inf], [-inf, inf])
void cam2DWindowToWorld(Pixel2D win, Vec2D* world)
{
    Vec2D device; 
    cam2DWindowToDevice(win, &device);   
    cam2DDeviceToWorld(device, world);
}

// Convert from normalized window coords (x,y) in in ([0.0, 1.0], [1.0, 0.0]) to world coords ([-inf, inf], [-inf, inf])
void cam2DNormWindowToWorld(Vec2D normWin, Vec2D* world)
{
    Vec2D device; 
    cam2DNormWindowToDevice(normWin, &device);
    cam2DDeviceToWorld(device, world);
}
