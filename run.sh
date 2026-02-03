


mode="$1"
if [[ -z "$mode" ]]; then
	./a.out
elif [[ "$mode" = "debug" ]]; then
	gdb a.out	
fi




