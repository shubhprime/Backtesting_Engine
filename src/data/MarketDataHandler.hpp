#pragma once

#include <fstream>
#include <string>
#include "../events/MarketEvent.hpp"
#include "../core/EventQueue.hpp"

class MarketDataHandler {
    public:
        MarketDataHandler(
            const std::string& filename,
            EventQueue& eventQueue
        );

        void stream_next();
        bool has_more() const;

    private:
        std::ifstream file;
        std::string current_line;
        EventQueue &eventQueue;
};