CXX = g++
CXXFLAGS = -Wall -g -std=c++2a -fsanitize=address

default: test

test: test.cpp UdpSocketImpl.cpp UdpSocketImpl.hpp
	$(CXX) $(CXXFLAGS) -o test test.cpp UdpSocketImpl.cpp -lpthread -lgtest

clean:
	$(RM) test *.o *~
