CXX = g++
CXXFLAGS = -Wall -g -std=c++2a -fsanitize=address

default: test

test: test.cpp 
	$(CXX) $(CXXFLAGS) -o test test.cpp -lpthread -lgtest

clean:
	$(RM) test *.o *~

