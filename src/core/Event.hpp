#pragma once

enum class EventType {
    MARKET,
    SIGNAL,
    ORDER,
    FILL
};

struct Event {
    EventType type;

    virtual ~Event() = default;
};