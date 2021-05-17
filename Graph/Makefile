CXX = g++
CXXFLAGS = -Wall -Werror -g -O3 -std=c++2a -fsanitize=address

.PHONY: default
default: test

test: test.cpp Graph.hpp
	$(CXX) $(CXXFLAGS) -o test test.cpp -lpthread

.PHONY: clean
clean:
	$(RM) test *.o *~
