
get_time_us(){
	local sec nano
	read -r sec nano <<< "$(date +'%s %N')"
	echo $(( (10#$sec * 1000000) + (10#$nano / 1000) ))
}

glsl_flags=" -O0 --target-env=vulkan1.2"

compile_shaders(){

if [[ 0 = 1 ]]; then

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
	echo "Boid Shaders"

fi

	echo "2D Compute Shaders"
	glslc $glsl_flags -DDRAW src/unified.comp -o build/draw.spv &
	glslc $glsl_flags -DCOUNT src/unified.comp -o build/count.spv &
	glslc $glsl_flags -DPREFIX src/unified.comp -o build/prefix.spv &
	glslc $glsl_flags -DFILL src/unified.comp -o build/fill.spv &
	glslc $glsl_flags -DRESOLVE src/unified.comp -o build/resolve.spv &

}

compiler="$1"
build_type="$2"

target="unified_compiling"


if [[ -z "$compiler" ]]; then
	$compiler="TCC"	
fi


libraries=" -lm -lpthread -lvulkan -lxcb -lxcb-keysyms -lxcb-randr -lxcb-xkb -lxcb-ewmh -lfreetype -I/usr/include/freetype2 -lasound -D_GNU_SOURCE "

TIME=$(get_time_us)

tcc_debug(){
	tcc -g3 $libraries src/main.c -Wall -o "$target"
}
gcc_debug(){
	gcc src/main.c -march=native -O0 -g3 -Wall $libraries -o "$target"
}
clang_debug(){
	clang src/main.c -march=native -O0 -g3 -Wall $libraries -o "$target"
}

tcc_release(){
	tcc_debug
}
gcc_release(){
	gcc src/main.c -march=native -O4 -Wall $libraries -o "$target" 
}
clang_release(){
	clang src/main.c -march=native -O4 -Wall $libraries -o "$target"
}

TIME=$(get_time_us)

if [[ -f "$target" ]]; then
	rm "$target"
fi

if [[ "$build_type" = "release" ]]; then

	if [[ "$compiler" = "TCC" ]]; then
		tcc_release
	fi
	if [[ "$compiler" = "GCC" ]]; then
		gcc_release
	fi
	if [[ "$compiler" = "CLANG" ]]; then
		clang_release
	fi
	if [[ "$compiler" = "GLSLC" ]]; then
		compile_shaders
	fi
	
elif [[ "$build_type" = "debug" ]]; then

	if [[ "$compiler" = "TCC" ]]; then
		tcc_debug
	fi
	if [[ "$compiler" = "GCC" ]]; then
		gcc_debug
	fi
	if [[ "$compiler" = "CLANG" ]]; then
		clang_debug
	fi
	if [[ "$compiler" = "GLSLC" ]]; then
		compile_shaders
	fi
fi




	

if [[ "$compiler" != "GLSLC" ]]; then
	if [[ -f "$target" ]]; then
		echo "SUCCESS"
		cp "$target" unified
		rm "$target"
		objdump -d unified > dump.txt
		TIME=$(($(get_time_us)-TIME))
		printf "Build $build_type $compiler %'u ms\n" $((10#$TIME / 1000))
	else
		echo "FAIL"	
	fi
fi





wait
