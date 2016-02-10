CC = g++
WallFlag = -Wall 
OutPut = hos_alpha
curses = -lncurses

Modules =  windlg.o configurator.o desktop.o fswork.o lang.o menu_apps.o

bootloader = ./bootloader/bootloader.cpp

all: win_dlg_c configurator_c desktop_c fswork_c lang_c
	$(CC) $(WallFlag) -c $(bootloader) -o main.o
	$(CC) $(Modules) main.o -o $(OutPut) $(curses)
	chmod u=rwx,g=rx,o=rx ./$(OutPut)
	./$(OutPut)

win_dlg_c:       
	$(CC) $(WallFlag) -c ./windlg/windlg.cpp -o windlg.o

configurator_c:
	$(CC) $(WallFlag) -c ./configurator/configurator.cpp -o configurator.o

desktop_c:
	$(CC) $(WallFlag) -c ./desktop/header/menu_apps.cpp -o menu_apps.o	
	$(CC) $(WallFlag) -c ./desktop/desktop.cpp -o desktop.o

fswork_c:
	$(CC) $(WallFlag) -c ./fswork/fswork.cpp -o fswork.o

lang_c:
	$(CC) $(WallFlag) -c ./lang/lang.cpp -o lang.o

clean:
	rm -rf *.o

clean-all:
	rm -rf *.o
	rm $(OutPut)
