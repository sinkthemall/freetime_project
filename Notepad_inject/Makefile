main:
	gcc -s -o codeinj.exe codeinj.c 
	gcc -fPIC -shared -o my_dll.dll my_dll.c
	gcc -fPIC -static -shared -o mh_dll.dll mh_dll.c -lMinhook
another:
	gcc -s -o sethook.exe sethook.c 
	gcc -fPIC -shared -o another_dll.dll another_dll.c