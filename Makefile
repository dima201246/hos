CC				= g++
FLAGS_LIB		= -c -fPIC -Wall -g
FLAGS 			= -c -Wall -g
OutPut			= hos_alpha
StarterName		= hos_starter
HOS_LIB			= libhos.so
_HOS_VERSION	= \"0.0.12\"

Lib_Modules		= timework.o fswork.o windlg.o screen.o lang.o settings.o configurator.o windows_api.o hos_api.o win_obj.o
Modules			= desktop.o menu_apps.o apps_starter.o system.o 
Main			= bootloader.o

VPATH			= ./isca_alpha:./isca_alpha/windlg:./system:./hos_lib

all: $(Modules) $(Main) 
		$(CC) $^ -o $(OutPut) -lcurses -Llib -lhos -Wl,-rpath=./lib
		chmod u=rwx,g=rx,o=rx ./$(OutPut)

start:
		./$(StarterName)

.PHONY: hos_lib
hos_lib: $(Lib_Modules) stat_file.o
		mkdir -p lib
		$(CC) -shared -o lib/$(HOS_LIB) $^

$(Modules) $(Main) : %.o : %.cpp
		$(CC) -D_HOS_VERSION=$(_HOS_VERSION) $(FLAGS) $< -o $@

$(Lib_Modules) : %.o : %.cpp
		$(CC) -D_HOS_VERSION=$(_HOS_VERSION) $(FLAGS_LIB) $< -o $@
		
stat_file.o : stat_file.c
		$(CC) -D_HOS_VERSION=$(_HOS_VERSION) $(FLAGS_LIB) $< -o $@

.PHONY: hos_starter
hos_starter: starter.o
		$(CC) $^ -o $(StarterName)
		chmod u=rwx,g=rx,o=rx ./$(StarterName)

.PHONY: clean 
clean:
	rm -rf *.o

.PHONY: clean-all
clean-all:
	rm -rf *.o
	rm -rf lib/$(OUT_LIB)
	rm $(OutPut)
	rm $(StarterName)
