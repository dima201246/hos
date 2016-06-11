CC			= g++
ARCH		= 64
FLAGS_LIB	= -O2 -c -fPIC -Wall -g
FLAGS 		= -c -Wall -g
OutPut		= hos_alpha
OUT_LIB		= libhos_x$(ARCH).so

Modules		= desktop.o menu_apps.o apps_starter.o
bootloader	= ./bootloader/bootloader.cpp

all:	$(Modules)
		$(CC) $(FLAGS) -c $(bootloader) -o main.o
		$(CC) $(Modules) main.o -o $(OutPut) -lcurses -Llib -lhos_x$(ARCH) -lconfigurator_x$(ARCH) -Wl,-rpath,lib
		chmod u=rwx,g=rx,o=rx ./$(OutPut)

start:
		./$(OutPut)

hos_lib:
		mkdir -p lib
		$(CC) $(FLAGS_LIB) fswork/fswork.cpp -o fswork.o -m$(ARCH)
		$(CC) $(FLAGS_LIB) fswork/stat_file.c -o stat_file.o -m$(ARCH)
		$(CC) $(FLAGS_LIB) windlg/windlg.cpp -o windlg.o -m$(ARCH)
		$(CC) $(FLAGS_LIB) screen/screen.cpp -o screen.o -m$(ARCH)
		$(CC) $(FLAGS_LIB) lang/lang.cpp -o lang.o -m$(ARCH)
		$(CC) -shared fswork.o stat_file.o windlg.o screen.o lang.o -o lib/$(OUT_LIB) -m$(ARCH)

desktop.o:
		$(CC) $(FLAGS) ./desktop/desktop.cpp -o desktop.o

menu_apps.o:
		$(CC) $(FLAGS) ./desktop/header/menu_apps.cpp -o menu_apps.o	

apps_starter.o:
		$(CC) $(FLAGS) ./apps_starter/apps_starter.cpp -o apps_starter.o

clean:
	rm -rf *.o

clean-all:
	rm -rf *.o
	rm -rf lib/$(OUT_LIB)
	rm $(OutPut)
