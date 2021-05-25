#include "Watchdog.hpp"

bool Watchdog::pet(worker_id &id) {

    std::lock_guard<std::mutex> lock(mutex_);

    if (current_workers_ == max_workers_) {
        return false;
    }

    if (worker_map_.contains(id)) {

        queue_.erase(worker_map_.at(id)); // Todo: Impelment this method in Queue
        worker_map_.erase(id);
        current_workers_--;
    }

    auto deadline = calculate_deadline();

    auto queue_item = std::make_pair(id, deadline);
    queue_index idx = queue_.put_queue(queue_item); //TODO: have put_queue return the queue_idx
    worker_map_[id] = idx;

    current_workers_++;

    return true;
}

auto Watchdog::calculate_deadline() {

    auto curr_time = std::chrono::system_clock::now();
    auto deadline =
        curr_time + std::chrono::duration_cast<std::chrono::seconds>(interval_);

    return deadline;
}