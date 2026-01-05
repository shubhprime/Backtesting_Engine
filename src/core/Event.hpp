#pragma once

enum class EventType {
    MARKET,
    SIGNAL
};

struct Event {
    EventType type;

    virtual ~Event() = default;
};