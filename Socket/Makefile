CXX = g++
CXXFLAGS = -Wall -g -std=c++2a -fsanitize=address
#LIB = -L/Users/andrewburger/Desktop/andrew_cpp_library/Watchdog/circular_buffer_queue/

default: all

test: test.cpp UdpSocket.hpp
	$(CXX) $(CXXFLAGS) -o test test.cpp $(LIB) -lpthread -lgtest

test_server: test_server.cpp
	$(CXX) $(CXXFLAGS) -o test_server test_server.cpp $(LIB) -lpthread -lgtest

test_client: test_client.cpp
	$(CXX) $(CXXFLAGS) -o test_client test_client.cpp $(LIB) -lpthread -lgtest

all: test test_server test_client

clean:
	$(RM) test *.o *~
