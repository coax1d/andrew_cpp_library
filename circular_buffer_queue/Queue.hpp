/* FIFO Queue using Circular Buffer
Author: Andrew Burger */

#ifndef QUEUE_CIRCULARBUFFERQUEUE_HPP_
#define QUEUE_CIRCULARBUFFERQUEUE_HPP_
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <assert.h>
#include <cstring>

#define DEFAULT_QUEUE_SIZE 512

template<class T>
class Queue {

    public:
        Queue<T>();
        Queue<T>(size_t queue_len);
        ~Queue<T>() = default;

        Queue<T>(Queue<T> &) = delete;
        Queue<T> & operator=(Queue<T> &) = delete;

        template <class U>
        void put_queue(U &&item);

        bool is_empty();
        T get_queue();

    private:
        size_t queue_entry_{};
        size_t queue_exit_{};
        std::unique_ptr<T[]>queue_{nullptr};
        const size_t queue_len_{DEFAULT_QUEUE_SIZE};
        bool is_full_{false};
};


template <class T>
Queue<T>::Queue() : queue_len_{DEFAULT_QUEUE_SIZE} {
    queue_ = std::make_unique<T[]>(queue_len_);
}

template <class T>
Queue<T>::Queue(size_t queue_len) : queue_len_{queue_len} {
    queue_ = std::make_unique<T[]>(queue_len_);
}

template<class T>
template<class U>
void Queue<T>::put_queue(U &&item) {

    //TODO: Add in thread safety here
    // std::lock_guard<std::mutex> lock(mutex_);

    if (is_full_) {
        queue_exit_ = (queue_exit_ + 1) % queue_len_;
    }

    queue_[queue_entry_++] = item;
    queue_entry_ = queue_entry_ % queue_len_;

    if (queue_entry_ == queue_exit_) {
        is_full_ = true;
    }
    else {
        is_full_ = false;
    }
}

template<class T>
T Queue<T>::get_queue() {

    //make thread safe
    //TODO: std::lock_guard<std::thread> lock(mutex_)

    assert(!is_empty());

    if (is_full_) {
        is_full_ = false;
    }

    T return_val;
    return_val = queue_[queue_exit_++];

    queue_exit_ = queue_exit_ % queue_len_;

    return return_val;
}

template<class T>
bool Queue<T>::is_empty() {

    if (!is_full_ && queue_exit_ == queue_entry_) {
        return true;
    }

    return false;
}

#endif // QUEUE_CIRCULARBUFFERQUEUE_HPP_