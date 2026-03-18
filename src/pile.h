
typedef enum {
	PROCESS_PILE = 1,
	SURFACE_PILE,
	GRAPHICS_PILE,
	AUDIO_PILE,
	FRAME_PILE,
	SIM_PILE,
	UPDATE_PILE,
	PILE_TYPE_COUNT,
}PileType;

typedef enum{
	PROCESS_PILE_INIT = 1,

	SURFACE_PILE_CREATE_WINDOW,
	SURFACE_PILE_CREATE_SURFACE,

	GRAPHICS_PILE_CREATE_INSTANCE,
	GRAPHICS_PILE_CREATE_DEVICE,
	GRAPHICS_PILE_CREATE_PIPELINES,
	GRAPHICS_PILE_CREATE_FRAME,
	GRAPHICS_PILE_CREATE_SWAPCHAIN,

	AUDIO_PILE_CREATE_DEVICE,

	PILE_STAGE_COUNT,
}PileStage;




typedef struct{
	GraphicsInstance *instance;
	GraphicsDevice *device;
	GraphicsSurface *surface;
	GraphicsSwapchain swapchain;

	u32 frame_count;
	Arena *frame_arenas;
	Arena *arena;
}GraphicsPile;

typedef struct{
	Window *window;
	GraphicsSurface surface;
	Arena *arena;
}SurfacePile;

typedef struct{
	Arena *arena;
}SimPile;

typedef struct{
	Arena *arena;
}ProcessPile;

typedef struct{
	AudioDevice *device;
}AudioPile;

typedef struct{
	PileStage dependent;
	PileType type;
	PileStage stage;
	b32 is_concurrent;
}PileDependency;

typedef struct{
	PileStage current_stage;
	u32 count;
	PileDependency *data;
}PileDependencyArray;

typedef struct{
	Scratch arena_marker;
	u64 previous_stage_elapsed_time;
}PileMarker;

PileMarker pile_markers[PILE_STAGE_COUNT];
PileDependencyArray pile_dependency_arrays[PILE_TYPE_COUNT];
PileStage pile_stage_ranges[PILE_TYPE_COUNT][2];

ProcessPile process;
SurfacePile surface;
GraphicsPile graphics;
AudioPile audio;

SimPile sim;


void pile_init();


void execute_pile(PileStage desired_stage);

















