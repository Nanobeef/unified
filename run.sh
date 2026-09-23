


mode="$1"
if [[ -z "$mode" ]]; then
	./unified
elif [[ "$mode" = "detached" ]]; then
	./unified $
elif [[ "$mode" = "debug" ]]; then
#	~/dev/raddebugger/build/raddbg unified
	gdb unified
fi



