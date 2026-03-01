

get_time_us(){
	local sec nano
	read -r sec nano <<< "$(date +'%s %N')"
	echo $(( (10#$sec * 1000000) + (10#$nano / 1000) ))
}

compiler="$1"
build_type="$2"

if [[ -z "$compiler" ]]; then
	$compiler="TCC"	
fi



libraries=" -lm -lpthread -lvulkan -lxcb -lxcb-keysyms -lxcb-randr -lfreetype -I/usr/include/freetype2"

TIME=$(get_time_us)
if [[ "$compiler" = "GCC" ]]; then
	gcc src/main.c -march=native -O4 -gdwarf $libraries 
elif [[ "$compiler" = "CLANG" ]]; then
	clang src/main.c -march=native -O0 -gdwarf -Wpedantic $libraries
else
	tcc -gdwarf $libraries src/main.c -Wpedantic 
fi

TIME=$(($(get_time_us)-TIME))
printf "$compiler %'u ms\n" $((10#$TIME / 1000))

objdump -d a.out > dump.txt

