/*
    Camera2D - pan, zoom, and window resizing
*/
typedef short bool;
typedef struct { int width; int height; } Size2D;
typedef struct { float x; float y; } Vec2D;

extern bool cam2DUpdated();
extern bool cam2DWindowResized();

extern Size2D cam2DWindowSize();
extern Vec2D  cam2DViewport();
extern Vec2D  cam2DBasePan();
extern Vec2D  cam2DPan();
extern float  cam2DZoom();
extern float  cam2DAspect();

extern void cam2DSetWindowSize(int width, int height);
extern void cam2DSetBasePan();
extern void cam2DSetPan(Vec2D pan);
extern void cam2DSetPanDelta(Vec2D panDelta);
extern void cam2DSetZoom(float zoom);
extern void cam2DSetZoomDelta(float zoomDelta);
extern void cam2DSetAspect(float aspect);

extern void cam2dNormWindowToDevice(float normWinX, float normWinY, float* deviceX, float* deviceY);
extern void cam2DWindowToDevice(int winX, int winY, float* deviceX, float* deviceY);
extern void cam2DDeviceToWorld(float deviceX, float deviceY, float* worldX, float* worldY);
extern void cam2DWindowToWorld(int winX, int winY, float* worldX, float* worldY);
extern void cam2DNormWindowToWorld(float normWinX, float normWinY, float* worldX, float* worldY);
