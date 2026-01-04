#include <sstream>
#include  "./MarketDataHandler.hpp"

MarketDataHandler::MarketDataHandler(const std::string& filename) {
    file.open(filename);
    std::getline(file, current_line);
}

bool MarketDataHandler::has_next() {
    return static_cast<bool>(std::getline(file, current_line));
}

MarketEvent MarketDataHandler::next() {
    std::stringstream ss(current_line);
    std::string timeStamp;
    std::string price_str;

    std::getline(ss, timeStamp, ',');
    std::getline(ss, price_str, ',');

    MarketEvent event;
    event.timeStamp = timeStamp;
    event.price = std::stod(price_str);

    return event;
}