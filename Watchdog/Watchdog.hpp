#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <deque>
#include <unordered_map>

#define DEFAULT_INTERVAL 5 // Seconds
#define DEFAULT_MAX_WORKERS 5

class Watchdog {

    using time_point_t =
        std::chrono::time_point<std::chrono::system_clock>;

    using worker_id = std::thread::id;
    using queue_iterator = std::deque<std::pair<worker_id, time_point_t>>::iterator;

    public:
        Watchdog();
        Watchdog(double deadline_interval, size_t max_workers);
        ~Watchdog();

        /*
        Worker signals to the watchdog that they are in a good state
        while working on their task. The watchdog removes them from the queue/map
        and places them at the back of the queue to continue working.
        */
        bool pet(worker_id &id);

        /*
        The worker signals that they have fully completed their task
        and can be removed from the work queue/map
        */
        bool complete(worker_id &id);

        /*
        The main watchdog thread checks to see if the worker at the front
        of the queue has passed their work deadline without petting the dog.
        (i.e. signaling that they are in a good state while working on their task)
        */
        bool is_over_deadline(worker_id &id);

        /*
        Gets the deadline for the next worker in the queue.
        if there are no workers in the queue it will be the standard interval
        to keep the system going.
        */
        auto get_next_deadline();

        /*
        Allows for testing of the watchdog to see if there has
        been a failure.
        */
        const bool get_has_barked();

        /*
        Allows test to reset the watchdog
        */
        void set_has_barked(bool bark_status);


        private:
            std::mutex mutex_;

            /*
            Queue of workers and their corresponding deadlines.
            */
            std::deque<std::pair<worker_id, time_point_t>> queue_;

            /*
            Workers can finish their job before they get to the front of the queue,
            therefore if finish their job sooner than others they must be removed from
            the queue and then placed at the back of the line. This helps keep track of
            where they are in the queue for quick removal.
            */
            std::unordered_map<worker_id, queue_iterator> worker_map_;

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

            /*
            Flag which tells whether a worker went over his deadline
            */
            bool has_dog_barked_{false};

            void sick_the_watch_dog();
            auto calculate_deadline();
};