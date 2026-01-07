#pragma once

#include <memory>
#include "../core/EventQueue.hpp"
#include "../events/MarketEvent.hpp"
#include "../events/OrderEvent.hpp"
#include "../events/FillEvent.hpp"

class ExecutionSimulator {
    public:
        ExecutionSimulator(EventQueue& eventQueue) : eventQueue(eventQueue) {}

        void onOrderEvent(const OrderEvent& order) {
            auto fill = std::make_shared<FillEvent>();
            fill->timeStamp = order.timeStamp;
            fill->orderType = order.orderType;
            fill->quantity = order.quantity;
            fill->fillPrice = order.referencePrice;

            eventQueue.push(fill);
        }

    private:
        EventQueue& eventQueue;
};