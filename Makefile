CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

OBJS = tree.o truth_table.o infix_prefix.o

all: task1 logic_a1

task1: task1.cpp infix_prefix.o
	$(CXX) $(CXXFLAGS) -o task1 task1.cpp infix_prefix.o

infix_prefix.o: infix_prefix.cpp infix_prefix.hpp
	$(CXX) $(CXXFLAGS) -c infix_prefix.cpp

logic_a1: main.cpp tree.o truth_table.o infix_prefix.o
	$(CXX) $(CXXFLAGS) -o logic_a1 main.cpp tree.o truth_table.o infix_prefix.o

tree.o: tree.cpp tree.hpp
	$(CXX) $(CXXFLAGS) -c tree.cpp

truth_table.o: truth_table.cpp truth_table.hpp tree.hpp
	$(CXX) $(CXXFLAGS) -c truth_table.cpp

clean:
	rm -f task1 logic_a1 tree.o truth_table.o infix_prefix.o

.PHONY: all clean
