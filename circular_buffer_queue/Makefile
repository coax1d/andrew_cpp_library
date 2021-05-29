CXX = g++
CXXFLAGS = -Wall -g -Werror -std=c++2a -fsanitize=address

.PHONY: default
default: test
	./test

test: test.cpp Queue.hpp
	$(CXX) $(CXXFLAGS) -o test $^ -lpthread

.PHONY: clean
clean:
	$(RM) test *.o
