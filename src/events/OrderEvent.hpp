#pragma once

#include <string>
#include "../core/Event.hpp"

enum class OrderType {
    BUY,
    SELL
};

struct OrderEvent : public Event {
    std::string timeStamp;
    OrderType orderType;
    int quantity;
    double referencePrice;

    OrderEvent() {
        type = EventType::ORDER;
    }
};