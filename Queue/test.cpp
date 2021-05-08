#include <iostream>
#include <string>
#include "Queue.hpp"

template<class T>
void print(const std::string &msg, const T &value) {
    std::cout << value << msg << std::endl;
}

void test() {

    Queue<int> queue;

    int test1 = 1;
    int test2 = 2;
    std::string put_queue_msg(" Put in the queue");
    std::string get_queue_msg(" Retrieved from the queue");

    // put_queue test
    queue.put_queue(1);
    queue.put_queue(test2);
    print(put_queue_msg, 1);
    print(put_queue_msg, test2);

    // get_queue test
    print(get_queue_msg, queue.get_queue());
    print(get_queue_msg, queue.get_queue());
}

int main(void) {

    test();

    return 0;
}