CXX = g++
CXXFLAGS = -Wall -g -std=c++2a -fsanitize=address
#LIB = -L/Users/andrewburger/Desktop/andrew_cpp_library/Watchdog/circular_buffer_queue/

default: test

test: test.cpp UdpSocket.hpp UdpSocket.cpp
	$(CXX) $(CXXFLAGS) -o test test.cpp UdpSocket.cpp $(LIB) -lpthread -lgtest

clean:
	$(RM) test *.o *~
