#pragma once

#include <string>
#include "../core/Event.hpp"

struct MarketEvent : public Event {
    std::string timeStamp;
    double price;

    MarketEvent() {
        type = EventType::MARKET;
    }
};