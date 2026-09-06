
get_time_us(){
	local sec nano
	read -r sec nano <<< "$(date +'%s %N')"
	echo $(( (10#$sec * 1000000) + (10#$nano / 1000) ))
}

compiler="$1"
build_type="$2"

glsl_flags=" -O --target-env=vulkan1.2"

if [[ -z "$compiler" ]]; then
	$compiler="TCC"	
fi

libraries=" -lm -lpthread -lvulkan -lxcb -lxcb-keysyms -lxcb-randr -lxcb-xkb -lxcb-ewmh -lfreetype -I/usr/include/freetype2 -lasound -D_GNU_SOURCE "

TIME=$(get_time_us)
if [[ "$compiler" = "GCC" ]]; then
	gcc src/main.c -march=native -O4 -gdwarf $libraries &
elif [[ "$compiler" = "CLANG" ]]; then
	clang src/main.c -march=native -O0 -gdwarf -Wpedantic $libraries &
else
	tcc -gdwarf $libraries src/main.c -Wpedantic &
fi
	
TIME=$(get_time_us)
glslc $glsl_flags src/boid_resolve.comp -o build/boid_resolve_comp.spv &
glslc $glsl_flags src/boid_reset.comp -o build/boid_reset_comp.spv &
glslc $glsl_flags src/boid_count.comp -o build/boid_count_comp.spv &
glslc $glsl_flags src/boid_prefix_sum.comp -o build/boid_prefix_sum_comp.spv &
glslc $glsl_flags src/boid_fill.comp -o build/boid_fill_comp.spv &

glslc $glsl_flags src/boid.vert -o build/boid_vert.spv &
glslc $glsl_flags src/boid.frag -o build/boid_frag.spv &
glslc $glsl_flags src/boid.mesh -o build/boid_mesh.spv &
glslc $glsl_flags src/boid.task -o build/boid_task.spv & 

glslc $glsl_flags src/boid_grid_overlay.mesh -o build/boid_grid_overlay_mesh.spv & 
glslc $glsl_flags src/boid_grid_overlay.frag -o build/boid_grid_overlay_frag.spv & 

glslc $glsl_flags src/vertex2.vert -o build/vertex2_vert.spv & 
glslc $glsl_flags src/vertex2.frag -o build/vertex2_frag.spv & 


wait
TIME=$(($(get_time_us)-TIME))
printf "Build GLSLC + $compiler %'u ms\n" $((10#$TIME / 1000))


objdump -d a.out > dump.txt
