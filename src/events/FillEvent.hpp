#pragma once

#include <string>
#include "../core/Event.hpp"
#include "./OrderEvent.hpp"

struct FillEvent : public Event {

    std::string timeStamp;
    OrderType orderType;
    int quantity;
    double fillPrice;
    double commission;

    FillEvent() {
        type = EventType::FILL;
    }
};