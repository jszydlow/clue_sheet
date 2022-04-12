# Authors: Juliette Liebov, Noor Achkar, Jenna Szydlowski, Monica Cichon
# E-mails: jliebov@nd.edu, nachkar@nd.edu, jszydlow@nd.edu, mcichon@nd.edu
# This is the Makefile for the Cheers! Final Project

# g++ is for the GCC compiler for C++
CC := g++

# CFLAGS are the compiler flages for when we compile C code in this course
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -Werror -lm
CXXFLAGS := -m64 -std=c++11 $(FLAGS)

# Folder Variables
INC := include
SRC := src
OBJ := objects
EXE := exe

# Make initialize - Create the objects and executables

initialize:
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)


# Run Compilation Command
# Command: make clue_sheet

$(OBJ)/clue_functions.o: $(SRC)/clue_functions.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/clue_functions.cpp -o $@
	
$(OBJ)/clue_sheet.o: $(SRC)/clue_sheet.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/clue_sheet.cpp -o $@

clueObjs :=  $(OBJ)/clue_sheet.o $(OBJ)/clue_functions.o

clue_sheet: $(initialize) $(clueObjs)
	$(CC) $(CXXFLAGS) -o $(EXE)/clue_sheet $(clueObjs)
	

# Make clean
clean:
	rm -rf $(OBJ)/* $(EXE)/*
