#include <iostream>
#include <string>
#include "Queue.hpp"

//TODO: Add proper testing
int main(void) {

    Queue<int> queue(5);

    for(int i = 0; i < 7; i++) {
        std::cout << i << " Is being put in the queue" << std::endl;
        queue.put_queue(i);
    }

    return 0;
}
