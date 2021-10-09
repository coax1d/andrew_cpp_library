#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class MinHeap{
public:
  MinHeap()                     = default;
  ~MinHeap()                    = default;
  MinHeap(MinHeap &)            = delete;
  MinHeap& operator=(MinHeap &) = delete;

  void printHeap() {
    for_each(items.begin(), items.end(), [](int x){ cout << x << ' '; });
    cout << endl;
  }

  void push(int val) {
    items.push_back(val);
    printHeap();
    heapifyUp();
  }

  int pop() {
    int result = 0;
    swap(0, items.size() - 1);
    result = items.back();
    items.pop_back();
    heapifyDown();
    return result;
  }

private:
  vector<int> items{3,6,7,8,9,10,11,12};

  int getLeftChildIdx(int parentIdx) { return 2 * parentIdx + 1; };
  int getRightChildIdx(int parentIdx) { return 2 * parentIdx + 2; };
  int getParentIdx(int childIdx) {
    if (childIdx == 0) {
    return -1;
    }
    return (childIdx - 1) / 2;
  }

  bool hasLeftChild(int parentIdx) { return getLeftChildIdx(parentIdx) < items.size(); };
  bool hasRightChild(int parentIdx) { return getRightChildIdx(parentIdx) < items.size(); };
  bool hasParent(int childIdx) { return getParentIdx(childIdx) >= 0; };

  int leftChild(int parentIdx) { return items[getLeftChildIdx(parentIdx)]; };
  int rightChild(int parentIdx) { return items[getRightChildIdx(parentIdx)]; };
  int parent(int childIdx) { return items[getParentIdx(childIdx)]; };

  void swap(int idxA, int idxB) {
    int temp = items[idxA];
    items[idxA] = items[idxB];
    items[idxB] = temp;
  }

  void heapifyUp() {
    int idx = items.size() - 1;
    while (hasParent(idx)) {
      int parentIdx = getParentIdx(idx);
      if (items[idx] > parent(idx)) {
        break;
      }
      swap(parentIdx, idx);
      idx = parentIdx;
    }
  }

  void heapifyDown() {
    int parentIdx = 0;

    while (hasLeftChild(parentIdx)) {

      int smallestChildIdx = getLeftChildIdx(parentIdx);

      if (hasRightChild(parentIdx) && rightChild(parentIdx) < leftChild(parentIdx)) {
        smallestChildIdx = getRightChildIdx(parentIdx);
      }

      if (items[smallestChildIdx] > items[parentIdx]) {
        break;
      }

      swap(parentIdx, smallestChildIdx);
      parentIdx = smallestChildIdx;
    }

  }

};

