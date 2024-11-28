all:
	gcc -oFast bit.c -o bit
	# x86_64-w64-mingw32-gcc -oFast bit.c -o bit.exe
debug:
	gcc bit.c -o bit
	# x86_64-w64-mingw32-gcc bit.c -o bit.exe