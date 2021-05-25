CXX = g++
CXXFLAGS = -Wall -g -std=c++2a -fsanitize=address
LIB = -L/Users/andrewburger/Desktop/andrew_cpp_library/Watchdog/circular_buffer_queue/

default: test

test: test.cpp Watchdog.cpp Watchdog.hpp
	$(CXX) $(CXXFLAGS) -o test test.cpp $(LIB) -lpthread -lgtest

clean:
	$(RM) test *.o *~

