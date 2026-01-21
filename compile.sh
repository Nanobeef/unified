

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

TIME=$(get_time_us)
if [[ "$compiler" = "GCC" ]]; then
	gcc main.c -march=x86-64 -lm -O0 -gdwarf -Wpedantic
elif [[ "$compiler" = "CLANG" ]]; then
	clang main.c -march=x86-64 -lm -O0 -gdwarf -Wpedantic
else
	tcc main.c -lm -gdwarf -Wpedantic
fi
TIME=$(($(get_time_us)-TIME))
printf "$compiler %'u ms\n" $((10#$TIME / 1000))

objdump -d a.out > dump.txt

