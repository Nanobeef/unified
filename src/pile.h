



typedef struct{
// Graphics
	GraphicsInstance *instance;
	GraphicsDevice *device;
	GraphicsSurface *surface;

	GraphicsSwapchain swapchain;
	
		
}State;
State s = {0};


typedef enum{
	MAIN_PILE,
	GRAPHICS_PILE,
	AUDIO_PILE,
	SIM_PILE,
}PileType;

typedef enum{
	MAIN_PILEUP_INIT,	
}MainPileupType;

typedef enum{
	MAIN_PILEDOWN_CLEANUP = MAIN_PILEUP_INIT,
}MainPiledownType;


typedef enum{
	GRAPHICS_PILEUP_INSTANCE,	
	GRAPHICS_PILEUP_DEVICE,	
	GRAPHICS_PILEUP_SURFACE,
	GRAPHICS_PILEUP_RENDER,
	GRAPHICS_PILEUP_FRAME,
}GraphicsPileup;
