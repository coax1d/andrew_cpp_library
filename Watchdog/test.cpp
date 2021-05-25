#include <iostream>
#include "circular_buffer_queue/Queue.hpp"


int main(void) {

    Queue<int> queue_;

    queue_.put_queue(2);

    std::cout << queue_.get_queue()
        << " Grabbed from the queue" << std::endl;


    Watchdog(4.3, 5);

    return 0;
}