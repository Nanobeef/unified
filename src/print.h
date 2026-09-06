

typedef enum{
	TERMINAL_COLOR_NONE = 0,
	TERMINAL_COLOR_BLACK = 1,
	TERMINAL_COLOR_RED,
	TERMINAL_COLOR_GREEN,
	TERMINAL_COLOR_YELLOW,
	TERMINAL_COLOR_BLUE,
	TERMINAL_COLOR_MAGENTA,
	TERMINAL_COLOR_TEAL,
	TERMINAL_COLOR_WHITE,

	TERMINAL_COLOR_HI_BLACK,
	TERMINAL_COLOR_HI_RED,
	TERMINAL_COLOR_HI_GREEN,
	TERMINAL_COLOR_HI_YELLOW,
	TERMINAL_COLOR_HI_BLUE,
	TERMINAL_COLOR_HI_MAGENTA,
	TERMINAL_COLOR_HI_TEAL,
	TERMINAL_COLOR_HI_WHITE,

	TERMINAL_COLOR_MAX,
}TerminalColor;

typedef struct{
	u32 sig_figs;	
	TerminalColor terminal_color;
}Print;

String8 str8_print(Arena *arena, const char *format, ...);
String8 str8_vprint(Arena *arena, const char *format, va_list l); 

u64 print(const char *format, ...);
u64 vprint(Arena *arena, const char *format, va_list l);

u64 vmemprint(Arena *conflict, u64 size, u8* buffer, const char *format, va_list l);
u64 memprint(Arena *conflict, u64 size, u8* buffer, const char *format, ...);
