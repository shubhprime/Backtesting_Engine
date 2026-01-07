#pragma once

#include <string>
#include "../core/Event.hpp"
#include "./OrderEvent.hpp"

struct FillEvent : public Event {

    std::string timeStamp;
    OrderType orderType;
    int quantity;
    double fillPrice;

    FillEvent() {
        type = EventType::FILL;
    }
};