CC			= g++
WallFlag	= -Wall 
OutPut		= win_test
curses		= -lncurses
ARCH		= 64
main_cpp	= main.cpp

all:
	$(CC) $(WallFlag) -c $(main_cpp) -o main.o
	$(CC) main.o -o $(OutPut) $(curses) -L../../lib -lhos_x$(ARCH) -Wl,-rpath,../../lib
	chmod u=rwx,g=rx,o=rx ./$(OutPut)
	./$(OutPut)

clean:
	rm -rf *.o

clean-all:
	rm -rf *.o
	rm $(OutPut)
