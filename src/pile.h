




typedef struct{
	GraphicsInstance *instance;
	GraphicsDevice *device;
	GraphicsSurface *surface;
	GraphicsSwapchain swapchain;
	Arena *arena;
}GraphicsArena;

typedef struct{
	Arena *arena;
}FrameArena;

typedef struct{
	Window *window;
	GraphicsSurface surface;
	Arena *arena;
}SurfaceArena;

typedef struct{
	Arena *arena;
}SimArena;

typedef struct{
	Arena *arena;
}UpdateArena;

typedef struct{
	Arena *arena;
}ProcessArena;

typedef struct{

}AudioArena;
