#Makefile Jean Franco Hernández García

CXX = g++
CXXFLAGS = -Wall -std=c++17
######################################
files = *cc
######################################
all: cell

cell: $(files)
	@$(CXX) $(CXXFLAGS) -o p06_automata_simulator $(files)

######################################
.PHONY: clean
######################################
clean:
	@echo "cleaning up the directory..."
	@rm -rf *.o *gch *.out p06_automata_simulator
######################################