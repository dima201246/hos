CC = g++
WallFlag = #-Wall 
OutPut = desktop
curses = -lncurses

Modules =

all:
	$(CC) -c desktop.cpp -o main.o
	$(CC) $(Modules) main.o -o $(OutPut) $(curses)
	chmod u=rwx,g=rx,o=rx ./$(OutPut)
	./$(OutPut)

clean:
	rm -rf *.o

clean_all:
	rm -rf *.o
	rm $(OutPut)
