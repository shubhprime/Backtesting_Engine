#pragma once

enum class EventType {
    MARKET
};

struct Event {
    EventType type;

    virtual ~Event() = default;
};