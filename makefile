
compile:
	g++ -c main.cpp game_call.cpp -Iinclude
link:
	g++ -o runii main.o lib/Thegamelib.dll -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm
runlib:
	make compile 
	ar rcs lib/Thegamelib.dll game_call.o 
go:
	.\runii
kill:
	taskkill /F /IM runii.exe
Build:
	make runlib
	g++ -o Pingpong main.o lib/Thegamelib.dll -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

all:
	make runlib
	make link
	make go