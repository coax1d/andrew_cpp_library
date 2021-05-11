/* FIFO Queue using Linked List
Author: Andrew Burger */

#ifndef QUEUE_QUEUE_HPP_
#define QUEUE_QUEUE_HPP_
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <assert.h>
#include <cstring>

template<class T>
struct ListNode {

    ListNode() = default;
    explicit ListNode(T &&value, std::shared_ptr<ListNode<T>> next = nullptr) :
        value_{value},
        next_{next} {}

    T value_{};
    std::shared_ptr<ListNode<T>> next_{nullptr};
};

template<class T>
class Queue {

    public:
        Queue<T>();
        ~Queue<T>();

        Queue<T>(Queue<T> &) = delete;
        Queue<T> & operator=(Queue<T> &) = delete;

        template<class U>
        void put_queue(U &&item);

        T get_queue();

    private:
        std::shared_ptr<ListNode<T>> front_queue_{nullptr};
        std::shared_ptr<ListNode<T>> back_queue_{nullptr};
        size_t queue_len_{};
};

template<class T>
Queue<T>::Queue() {}

template<class T>
Queue<T>::~Queue() {}

template<class T>
template<class U>
void Queue<T>::put_queue(U &&item) {

    auto new_node = std::make_shared<ListNode<T>>(std::forward<T>(item));

    auto temp = front_queue_;
    front_queue_ = new_node;
    new_node->next_ = temp;

    if (!new_node->next_) {
        back_queue_ = new_node;
    }

    queue_len_++;
}

template<class T>
T Queue<T>::get_queue() {

    assert(queue_len_ != 0);

    T return_val;

    if (front_queue_ == back_queue_) { // One node in the list
        return_val = front_queue_->value_;
        front_queue_ = nullptr;
        back_queue_ = nullptr;
        return return_val;
    }

    auto current = front_queue_;
    while (current != back_queue_) {

        // Need to get to the ListNode which is two nodes
        // prior to the back_queue_ ListNode
        if (current->next_ != back_queue_) {
            current = current->next_;
            continue;
        }

        back_queue_ = current;

        auto removed_node = current->next_;
        return_val = removed_node->value_;
        queue_len_--;
    }

    return return_val;
}

#endif // QUEUE_QUEUE_HPP_