#include <iostream>
#include <string>
#include "Queue.hpp"


void test() {
    Queue<int> queue;

    int test1 = 1;
    int test2 = 2;
    queue.put_queue(1);
    queue.put_queue(test2);

    int test3 = queue.get_queue();

    std::cout << "Got " << test3 << " from the queue" << std::endl;
    int test4 = queue.get_queue();
    std::cout << "Got " << test4 << " from the queue" << std::endl;
}

void print(const std::string &msg) {
    std::cout << msg << std::endl;
}


int main(void) {

    test();

    return 0;
}