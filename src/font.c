

u16 be16(u16 x)
{
	u8* p = (u8*)&x;
	return (p[0] << 8) | p[1]; 	
}

u32 be32(u32 x)
{
	u8* p = (u8*)&x;
	return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}


typedef struct {
	u32 scaler;	
	u16 num_tables;
	u16 search_range;
	u16 entry_selector;
	u16 range_shift;
}TTF_Offset_Subtable;

typedef struct {
	u32 tag;
	u32 checksum;
	u32 offset;
	u32 length;
}TTF_Table_Record;

typedef u32 Fix32;


/* Need
*head - font units
*maxp - numGlyphs
*cmap - unicode codepoint to glyph ID
*loca - glyph ID to offset info 'glyf'
*glyf - quadratic outlines
*hhea - ascent, descent
*hmtx - advance and bearing
kern - pair kerning
*/


typedef struct{
	u16 major_version;
	u16 minor_version;
	Fix32 font_revision;
	u32 checksum_adjustment;
	u32 magic_number; // 0x5F0F3CF5
	u16 flags;
	u16 units_per_em;
	s64 created; // get_time_s();
	s64 modified;
	s16 x_min;
	s16 y_min;
	s16 x_max;
	s16 y_max;
	u16 mac_style;
	u16 lowest_rec_ppem;
	s16 font_direction_hint;
	s16 index_to_loc_format; // u16 or u32
	s16 glyph_data_format;
}TTF_Font_Header_Table; // head

typedef struct{
	u16 major_version;
	u16 minor_version;

	s16 ascender;
	s16 descender;
	s16 line_gap;
	u16 advance_width_max;
	s16 min_left_side_bearing;
	s16 min_right_side_bearing;
	s16 x_max_extent;

	s16 caret_slope_rise;
	s16 caret_slope_run;
	s16 caret_offset;
	
	s16 reserved_and_set_to_zero[4];

	s16 matric_data_format;
	u16 number_of_H_metrics; // for htmx table
}TTF_Horizontal_Header_Table;  // hhea


typedef struct{
	u16 advance_width;
	s16 left_side_bearing; // lsb
}TTF_Long_Hor_Metric;

/* Example

	typedef struct{
		TTF_Long_Hor_Metric metrics[];	
		s16 left_side_bearing[];
	}TTF_Horizontal_Metrics_Table; // hmtx
*/


typedef struct{
	u16vec2 version;	
	u16 num_glyphs; // loca 
	u16 max_points;
	u16 max_contours;
	u16 max_composite_points;
	u16 max_composite_contours;
	u16 max_zones;
	u16 max_twilight_points;
	u16 max_storage;
	u16 max_function_defs;
	u16 max_instruction_defs;
	u16 max_stack_elements;
	u16 max_stack_of_instructions;
	u16 max_component_elements;
	u16 max_component_depth;
}TTF_Maximum_Profile; // maxp

typedef struct{
	u16 platform_id;	
	u16 encoding_id;
	u16 subtable_offset;
}TTF_Encoding_Record;

typedef struct{
	u16 version;	
	u16 num_tables;
	TTF_Encoding_Record encoding_records[];
}TTF_Character_To_Glyph_Index_Mapping_Table; // cmap

/* // loca
	See header table, "index_to_loc_format" is either, 0 for u16, or 1 for u32.
	If offsets are more than 1 apart, the glyph description os longer.
	The offsets must be ascending but they may be spread apart.
	If offset is zero, the glyph is missing.
	If there is no fallback glyph to represent a missing glyph, check offsets 1 and 2.
	If offsets 1 and 2 are the same, there is not fallback glyph.
	If loca[n] == loca[n+] , that glyph "has no outline or instructions".
*/




typedef struct{
	s16 number_of_contours;
	s16 x_min;
	s16 y_min;
	s16 x_max;
	s16 y_max;
}TTF_Glyph_Header;

typedef enum{
	SIMPLE_GLYPH_ON_CURVE_POINT = 0x01,
	SIMPLE_GLYPH_X_SHORT_VECTOR = 0x02,	
	SIMPLE_GLYPH_Y_SHORT_VECTOR = 0x04,	
	SIMPLE_GLYPH_REPEAT_FLAG = 0x08,	
	SIMPLE_GLYPH_X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR = 0x10,
	SIMPLE_GLYPH_Y_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR = 0x20,	
	SIMPLE_GLYPH_OVERLAP_SIMPLE = 0x40,	
}TTF_Simple_Flyyph_Flags;

/*
typedef struct{
	u16 end_pts_of_contours[];

	u16 instruction_length;
	u8 instructions[];

	u8 flags[];

	//u8 x_coordinates[];
	//u8 y_coordinates[];
	//u16 x_coordinates[];
	//u16 y_coordinates[];

}TTF_Simple_Glyph_Table;
*/




s32 font_test()
{
	const char *name = "bin/BerkeleyMono-Regular.ttf";
	
	Scratch scratch = find_scratch(0,0,0);
	s32 fd = open(name, O_RDONLY);
	if(fd == -1)
	{
		print("Failed to open: %cs\n", name);
		return 0;
	}
	struct stat st;
	if(fstat(fd, &st) == -1)
	{
		print("Failed to get size: %cs\n", name);
		return 0;
	}

	u64 size = st.st_size;
	u8 *data = arena_push(scratch.arena, 0, size);
	
	u64 read_size = read(fd, data, size);
	if(read_size != size)
	{
		print("Incorrect shader read size: %cs\n", name);
		return 0;
	}

	TTF_Offset_Subtable *ost = (void*)data;
	TTF_Table_Record *tables = (void*)(data + sizeof(TTF_Offset_Subtable));

	u32 offset = sizeof(TTF_Offset_Subtable);
	for(u16 i = 0; i < be16(ost->num_tables); i++)
	{
		for(u32 j = 0; j < 4; j++)
		{
			print("%c", ((char*)&(tables[i].tag))[j]);
		}
		print("\n");
	}
	


	return 0;
}
