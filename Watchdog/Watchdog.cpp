#include "Watchdog.hpp"

Watchdog::Watchdog()
        :
        max_workers_{DEFAULT_MAX_WORKERS},
        interval_{DEFAULT_INTERVAL}
        {
    main_thread_ = std::thread(&Watchdog::sick_the_watch_dog, this);
}

Watchdog::Watchdog(double deadline_interval, size_t max_workers)
        :
        max_workers_{max_workers},
        interval_{deadline_interval}
        {
    main_thread_ = std::thread(&Watchdog::sick_the_watch_dog, this);
}

Watchdog::~Watchdog() {

    enable_main_thread = false;
    main_thread_.join();
}

bool Watchdog::pet(worker_id &id) {

    std::lock_guard<std::mutex> lock(mutex_);

    if (current_workers_ == max_workers_) {
        return false;
    }

    if (worker_map_.contains(id)) {
        queue_.erase(worker_map_.at(id));
        worker_map_.erase(id);
        current_workers_--;
    }

    auto deadline = calculate_deadline();
    auto queue_item = std::make_pair(id, deadline);
    queue_.emplace_back(queue_item);

    queue_iterator item_location = queue_.end();
    worker_map_[id] = item_location;

    current_workers_++;

    return true;
}

bool Watchdog::complete(worker_id &id) {

    std::lock_guard<std::mutex> lock(mutex_);

    if (worker_map_.contains(id)) {
        queue_.erase(worker_map_.at(id));
        worker_map_.erase(id);
        current_workers_--;
        return true;
    }

    return false;
}

bool Watchdog::is_over_deadline() {

    std::lock_guard<std::mutex> lock(mutex_);

    auto curr_time = std::chrono::system_clock::now();
    if (queue_.size() && (queue_.front().second < curr_time)) {
        return true;
    }

    return false;
}

auto Watchdog::get_next_deadline() {

    std::lock_guard<std::mutex> lock(mutex_);

    auto default_deadline = calculate_deadline();

    if (queue_.size()) {
        return queue_.front().second;
    }
    else {
        return default_deadline;
    }
}

void Watchdog::sick_the_watch_dog() {

    while (enable_main_thread) {

        if (is_over_deadline()) {

            has_dog_barked_ = true;
            std::cout << "A worker has failed to meet the deadline"
                << std::endl;
        }

        std::this_thread::sleep_until(get_next_deadline());
    }
}

auto Watchdog::calculate_deadline() -> decltype(std::chrono::system_clock::now()){

    auto curr_time = std::chrono::system_clock::now();
    auto deadline =
        curr_time + std::chrono::duration_cast<std::chrono::seconds>(interval_);

    return deadline;
}

const bool Watchdog::get_has_barked() {
    return has_dog_barked_;
}

void Watchdog::set_has_barked(bool bark_status) {
    has_dog_barked_ = false;
}