CC			= g++
WallFlag	= -Wall 
OutPut		= file_man
curses		= -lncurses
main_cpp	= file_man_main.cpp

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
