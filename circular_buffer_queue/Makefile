CXX = g++
CXXFLAGS = -Wall -g -Werror -std=c++2a -fsanitize=address

default: test

test: test.o 
	$(CXX) $(CXXFLAGS) -o test test.o -lpthread

clean:
	$(RM) test *.o *~

