CC = g++
WallFlag = -Wall 
OutPut = file_man
curses = -lncurses

Modules = fswork.o lang.o configurator.o #windlg.o desktop.o

main_cpp = file_man_main.cpp

all: fswork_c lang_c configurator_c #win_dlg_c desktop_c
	$(CC) $(WallFlag) -c $(main_cpp) -o main.o
	$(CC) $(Modules) main.o -o $(OutPut) $(curses)
	chmod u=rwx,g=rx,o=rx ./$(OutPut)
	./$(OutPut)

#win_dlg_c:
#	$(CC) $(WallFlag) -c ./windlg/windlg.cpp -o windlg.o

configurator_c:
	$(CC) $(WallFlag) -c ./../../configurator/configurator.cpp -o configurator.o

#desktop_c:
#	$(CC) $(WallFlag) -c ./desktop/desktop.cpp -o desktop.o

fswork_c:
	$(CC) $(WallFlag) -c ./../../fswork/fswork.cpp -o fswork.o

lang_c:
	$(CC) $(WallFlag) -c ./../../lang/lang.cpp -o lang.o

clean:
	rm -rf *.o

clean-all:
	rm -rf *.o
	rm $(OutPut)
