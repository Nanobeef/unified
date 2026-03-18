
void pile_init()
{
	PileMarker pile_markers[PILE_STAGE_COUNT];
	PileDependencyArray pile_dependency_arrays[PILE_TYPE_COUNT];
	PileStage pile_stage_ranges[PILE_TYPE_COUNT][2];
	for(u32 i = 0; i < Arrlen(pile_markers); i++)
	{
		pile_markers[i] = (PileMarker){
			
		};
	}
	
}

void execute_pile(PileStage desired_stage)
{
}
