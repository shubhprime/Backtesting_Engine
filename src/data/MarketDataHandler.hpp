#pragma once
#include <fstream>
#include <string>
#include "../events/MarketEvent.hpp"

class MarketDataHandler {
    public:
        MarketDataHandler(const std::string& filename);

        bool has_next();
        MarketEvent next();

    private:
        std::ifstream file;
        std::string current_line;
};