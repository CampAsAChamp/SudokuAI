# ======================================================================
# FILE:        Makefile
#
# DESCRIPTION: This file contains useful commands for this project. You
#              may use the following commands:
#
#              - make            - compiles the project and places
#                                  the executable in the bin folder
#              - clean           - deletes the executable and executable
#                                  folder
#
#              - Don't make changes to this file.
# ======================================================================

RAW_SOURCES = \
	BTSolver.cpp\
	Constraint.cpp\
	ConstraintNetwork.cpp\
	Domain.cpp\
	Main.cpp\
	SudokuBoard.cpp\
	Trail.cpp\
	Variable.cpp

SOURCE_DIR = src
BIN_DIR = bin
SOURCES = $(foreach s, $(RAW_SOURCES), $(SOURCE_DIR)/$(s))

all: $(SOURCES)
	@rm -rf $(BIN_DIR)
	@mkdir -p $(BIN_DIR)
	@g++ -std=c++0x $(SOURCES) -o $(BIN_DIR)/Sudoku

clean: 
	@rm -rf $(BIN_DIR)