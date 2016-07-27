CC			= g++
WallFlag	= -Wall 
OutPut		= win_test
curses		= -lncurses
main_cpp	= main.cpp

all:
	$(CC) $(WallFlag) -c $(main_cpp) -o main.o
	$(CC) main.o -o $(OutPut) $(curses) -L../../lib -lhos -Wl,-rpath,../../lib
	chmod u=rwx,g=rx,o=rx ./$(OutPut)
	./$(OutPut)

clean:
	rm -rf *.o

clean-all:
	rm -rf *.o
	rm $(OutPut)
