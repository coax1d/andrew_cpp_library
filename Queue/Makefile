CXX = g++
CXXFLAGS = -Wall -g -std=c++2a -fsanitize=address

default: test

test: test.o 
	$(CXX) $(CXXFLAGS) -o test test.o -lpthread -lgtest

clean:
	$(RM) test *.o *~

