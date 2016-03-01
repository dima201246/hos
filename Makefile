CC = g++
WallFlag = -Wall 
OutPut = hos_alpha
curses = -lncurses

Modules =  windlg.o configurator.o desktop.o fswork.o lang.o menu_apps.o apps_starter.o

bootloader = ./bootloader/bootloader.cpp

all: win_dlg.o desktop.o fswork.o lang.o apps_starter.o configurator.o
	$(CC) $(WallFlag) -c $(bootloader) -o main.o
	$(CC) $(Modules) main.o -o $(OutPut) $(curses)
	chmod u=rwx,g=rx,o=rx ./$(OutPut)
	./$(OutPut)

win_dlg.o:       
	$(CC) $(WallFlag) -c ./windlg/windlg.cpp -o windlg.o

configurator.o:
	$(CC) $(WallFlag) -c ./configurator/configurator.cpp -o configurator.o

desktop.o:
	$(CC) $(WallFlag) -c ./desktop/header/menu_apps.cpp -o menu_apps.o	
	$(CC) $(WallFlag) -c ./desktop/desktop.cpp -o desktop.o

fswork.o:
	$(CC) $(WallFlag) -c ./fswork/fswork.cpp -o fswork.o

lang.o:
	$(CC) $(WallFlag) -c ./lang/lang.cpp -o lang.o

apps_starter.o:
	$(CC) $(WallFlag) -c ./apps_starter/apps_starter.cpp -o apps_starter.o

clean:
	rm -rf *.o

clean-all:
	rm -rf *.o
	rm $(OutPut)
