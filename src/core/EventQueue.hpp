#pragma once

#include <queue>
#include <memory>
#include "Event.hpp"

class EventQueue {
    public:
        void push(std::shared_ptr<Event> event) {
            queue.push(event);
        }

        bool empty() const {
            return queue.empty();
        }

        std::shared_ptr<Event> pop() {
            auto event = queue.front();
            queue.pop();
            return event;
        }

    private:
        std::queue<std::shared_ptr<Event>> queue;
};