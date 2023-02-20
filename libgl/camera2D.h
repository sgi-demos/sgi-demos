//
//  Camera2D - pan, zoom, and window resizing
//
#include "geom_types.h"

// camera properties get/set
extern bool cam2DUpdated();
extern bool cam2DWindowResized();

extern Size2D cam2DWindowSize();
extern Vec2D  cam2DViewport();
extern Vec2D  cam2DBasePan();
extern Vec2D  cam2DPan();
extern float  cam2DZoom();
extern float  cam2DAspect();

extern void cam2DSetWindowSize(Size2D winSize);
extern void cam2DSetBasePan();
extern void cam2DSetPan(Vec2D pan);
extern void cam2DSetPanDelta(Vec2D panDelta);
extern void cam2DSetZoom(float zoom);
extern void cam2DSetZoomDelta(float zoomDelta);
extern void cam2DSetAspect(float aspect);

// zoom/pan camera from mouse and touch events
extern void cam2DZoomEventMouse(bool mouseWheelDown, Pixel2D mousePosition);
extern void cam2DZoomEventPinch(float pinchDist, Vec2D pinchCoord);
extern void cam2DPanEventMouse(Pixel2D mousePos, Pixel2D mouseButtonDownCoord);
extern void cam2DPanEventFinger(Vec2D fingerCoord, Vec2D fingerDownCoord);