# Consts:
# IncludeDIR = *.h DIR
# CC = gcc or g++
# DB = gdb
# CFLAGS = comp line flags (-ansi = ansi law; -Wall, -Wextra = warnings; -I./ = *.h DIR)
# ObjDIR = *.o DIR
# LibDIR = lib DIR
# LibDIR -> enable when using, put $(LIBS) at end of gogo's command
LibDIREC=./lib/
LibDIR=./lib/ /home/user/gtest-1.7.0/include /home/user/gtest-1.7.0/lib/.libs/libgtest.a /usr/local/include/opencv2
IncludeDIR=./include/
CcDIR=./src/
ObjDIR=./src/obj/
CC=g++
DB=gdb
CFLAGS=-ansi -Wall -Wextra -I$(IncludeDIR) -pthread -ftest-coverage -fprofile-arcs -lm
LIBS=-I/usr/local/include/opencv/. -I/usr/local/include/opencv2/. -L/usr/local/lib/ -lopencv_highgui -lopencv_imgproc -lopencv_core -lopencv_videoio -lopencv_imgcodecs -lopencv_video

# Vars:
# -- ADAPT THIS IN YOUR PROGRAM --
headers = funcoes.hpp
mainObject = Main
objects = Main.o funcoes.o

# Set of *.h on which the *.cc depend
_DEPS = $(headers)
DEPS = $(patsubst %,$(IncludeDIR)%,$(_DEPS))

# Set of *.o
_OBJ = $(mainObject).o $(objects)
OBJ = $(patsubst %,$(ObjDIR)%,$(_OBJ))

# Gathers *.o
$(ObjDIR)%.o: $(CcDIR)%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

# Creates executable (Linux)
$(mainObject): $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS) $(LIBS)

# Gets the files and organize in the lib include src/obj structure
.PHONY: prepareDIR
prepareDIR:
	mkdir -p $(LibDIREC)
	mkdir -p $(IncludeDIR)
	mkdir -p $(CcDIR)
	mkdir -p $(ObjDIR)
	mv *.hpp $(IncludeDIR); true
	mv *.cpp $(CcDIR); true

# Call for execution
.PHONY: execute
execute:
	./$(mainObject)

# Call for debugging
.PHONY: debug
debug:
	$(DB) ./$(mainObject)

# Call for cppcheck
.PHONY: cppcheck
cppcheck:
	cppcheck --enable=all . -I./include --suppress=missingIncludeSystem

# Call for *.o clean up
.PHONY: clean
clean:
	rm $(ObjDIR)*.o

# Call for help with this makefile's commands
.PHONY: help
help:
	@echo "\n\t Makefile\n"
	@echo " make............= compiles program"
	@echo " make prepareDIR.= prepares project in the "lib include src/obj" structure (use this if all files are with this makefile)"
	@echo " make execute....= executes succesfully compiled program"
	@echo " make debug......= (gdb) debugs succesfully compiled program"
	@echo " make cppcheck...= invokes cppcheck on all .cc files in the directory, checking for all types of messages*"
	@echo "                         *(except missingIncludeSystem - cppceck can't find the gtest library)"
	@echo " make clean......= removes objects from obj directory\n"
	@echo " For use with program, change variables -headers- and -objects- inside makefile\n\n"
