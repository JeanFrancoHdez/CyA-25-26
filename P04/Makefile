#Makefile Jean Franco Hernández García

CXX = g++
CXXFLAGS = -Wall -std=c++17
######################################
files = *cc
######################################
all: cell

cell: $(files)
	@$(CXX) $(CXXFLAGS) -o p04_code_analyzer $(files)

######################################
.PHONY: clean
######################################
clean:
	@echo "cleaning up the directory..."
	@rm -rf *.o *gch *.out p04_code_analyzer
######################################