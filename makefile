all:
	g++ -o run main.o game_call.o -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm
compile:
	g++ -c main.cpp game_call.cpp -Iinclude
allrun:
	g++ -c main.cpp game_call.cpp -Iinclude
	g++ -o run main.o game_call.o -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

go:
	.\run
kill:
	taskkill /F /IM run.exe

Build:
	make compile
	g++ -o Pingpong main.o game_call.o -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm