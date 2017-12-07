CC				= g++
FLAGS_LIB		= -c -fPIC -Wall -g -std=c++11
FLAGS 			= -c -Wall -g
OutPut			= hos_alpha
StarterName		= hos_starter
HOS_LIB			= libhos.so
_HOS_VERSION	= \"0.0.12\"

Lib_Modules		= timework.o fswork.o windlg.o screen.o lang.o settings.o configurator.o windows_api.o hos_api.o win_obj.o hos_video.o
Modules			= desktop.o menu_apps.o apps_starter.o system.o video_buf.o
Main			= bootloader.o

VPATH			= ./system:./hos_lib:./hos_lib/windlg

all: $(Modules) $(Main) 
		$(CC) $^ -o $(OutPut) -lrt -lcurses -Llib -lhos -Wl,-rpath=./lib
		chmod u=rwx,g=rx,o=rx ./$(OutPut)

start:
		./$(StarterName)

.PHONY: hos_lib
hos_lib: $(Lib_Modules) stat_file.o
		mkdir -p lib
		$(CC) -lrt -shared -o lib/$(HOS_LIB) $^

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
