#include "MinHeap.hpp"

int main(void) {
  MinHeap heap;
  heap.printHeap();
  heap.pop();
  heap.printHeap();
  heap.push(1);
  heap.printHeap();
}
