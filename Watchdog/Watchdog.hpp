#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <unordered_map>
#include "circular_buffer_queue/Queue.hpp"

#define DEFAULT_INTERVAL 5 // Seconds
#define DEFAULT_MAX_THREADS 5

class Watchdog {

    using time_point_t =
        std::chrono::time_point<std::chrono::system_clock>;

    using queue_index = size_t;
    using worker_id = std::thread::id;

    public:
        Watchdog();
        Watchdog(double deadline_interval, size_t max_workers);
        ~Watchdog();

        bool pet(worker_id &id);
        bool complete(worker_id &id);
        bool is_over_deadline(worker_id &id);
        auto get_next_deadline();

        private:
            std::mutex mutex_;

            /*
            Queue of workers and their corresponding deadlines.
            */
            Queue<std::pair<worker_id, time_point_t>> queue_;

            /*
            Workers may finish their job before they get to the queue_exit,
            therefore if they pet the dog early they must be removed from the queue.
            This helps keep track of where they are in the queue for quick removal.
            */
            std::unordered_map<worker_id, queue_index> worker_map_;

            size_t max_workers_{};
            size_t current_workers_{};

            /*
            Time interval which workers have to complete task
            and pet the doggy
            */
            std::chrono::duration<double> interval_;

            /*
            For easy start and stop of the main watchdog thread
            */
            std::atomic<bool> enable_main_thread{true};

            /*
            This main thread monitors all of the workers in the queue
            and their corresponding deadlines. I.E. the big scary doggy dog.
            */
            std::thread main_thread_;

            void sick_the_watch_dog();
            auto calculate_deadline();
};