#include <sstream>
#include  "./MarketDataHandler.hpp"

MarketDataHandler::MarketDataHandler(
    const std::string& filename,
    EventQueue& eventQueue
) : eventQueue(eventQueue)
{
    file.open(filename);
    std::getline(file, current_line);
}

void MarketDataHandler::stream_next() {
    if (!std::getline(file, current_line)) {
        return;
    }

    std::stringstream ss(current_line);
    std::string timeStamp;
    std::string price_str;

    std::getline(ss, timeStamp, ',');
    std::getline(ss, price_str, ',');

    auto event = std::make_shared<MarketEvent>();
    event->timeStamp = timeStamp;
    event->price = std::stod(price_str);

    eventQueue.push(event);
}