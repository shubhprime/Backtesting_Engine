#pragma once

#include <string>
#include "../core/Event.hpp"

enum class SignalType {
    BUY,
    SELL
};

struct SignalEvent : public Event {
    std::string timeStamp;
    SignalType signal;

    SignalEvent() {
        type = EventType::SIGNAL;
    }
};