/* FIFO Queue using Linked List
Author: Andrew Burger */

#ifndef QUEUE_QUEUE_HPP_
#define QUEUE_QUEUE_HPP_
#include <iostream>
#include <string>
#include <assert.h>
#include <cstring>

template<class T>
struct ListNode {

    ListNode(ListNode *next) : next_{next} {}
    ListNode(T &value) : value_{std::move(value)} {}
    ListNode(T &value, ListNode *next) :
        value_{std::move(value)},
        next_{next} {}

    T value_;
    ListNode *next_;
};

template<class T>
class Queue {

    public:
        Queue<T>();
        ~Queue<T>();

        Queue(Queue &) = delete;
        Queue & operator=(Queue &) = delete;

        void put_queue(T &item);
        void put_queue(T &&item);
        T get_queue();

    private:
        ListNode<T> *front_queue_;
        ListNode<T> *back_queue_;
        size_t queue_len_ = 0;
};

template<class T>
Queue<T>::Queue() {

    front_queue_ = new ListNode<T>(nullptr);
    back_queue_ = new ListNode<T>(nullptr);
    front_queue_->next_ = back_queue_;
}

template<class T>
Queue<T>::~Queue() {

    auto current = front_queue_;
    while (current) {
        auto temp = current;
        current = current->next_;
        delete temp;
    }
}

template<class T>
void Queue<T>::put_queue(T &item) {

    auto new_node = new ListNode<T>(item);

    auto temp = front_queue_->next_;
    front_queue_->next_ = new_node;
    new_node->next_ = temp;
    queue_len_++;
}

template<class T>
void Queue<T>::put_queue(T &&item) {

    auto new_node = new ListNode<T>(item);

    auto temp = front_queue_->next_;
    front_queue_->next_ = new_node;
    new_node->next_ = temp;
    queue_len_++;
}

template<class T>
T Queue<T>::get_queue() {

    assert(queue_len_ != 0);

    T return_val;

    auto current = front_queue_;
    while (current != back_queue_) {

        // Need to get to the ListNode which is two nodes
        // prior to the back_queue_ ListNode
        if (current->next_->next_ != back_queue_) {
            current = current->next_;
            continue;
        }

        auto removed_node = current->next_;
        current->next_ = current->next_->next_;

        return_val = removed_node->value_;
        delete removed_node;
        queue_len_--;
    }

    return return_val;
}

#endif // QUEUE_QUEUE_HPP_