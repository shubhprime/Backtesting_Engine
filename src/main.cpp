#include <iostream>
#include "./data/MarketDataHandler.hpp"
#include "./core/EventQueue.hpp"
#include "./events/MarketEvent.hpp"
#include "./events/SignalEvent.hpp"
#include "./strategy/MovingAverageStrategy.hpp"

int main() {
    EventQueue eventQueue;
    MarketDataHandler data("./data/prices.csv", eventQueue);
    MovingAverageStrategy strategy(eventQueue, 3);

    for (int i = 0; i < 4; i++) {
        data.stream_next();
    }

    while (!eventQueue.empty()) {
        auto event = eventQueue.pop();

        if (event->type == EventType::MARKET) {
            auto marketEvent = std::static_pointer_cast<MarketEvent>(event);
            std::cout << marketEvent->timeStamp
                      << " → "
                      << marketEvent->price
                      << "\n";

                      strategy.onMarketEvent(*marketEvent);
        } else if(event->type == EventType::SIGNAL) {
            auto signalEvent = std::static_pointer_cast<SignalEvent>(event);

            std::cout << " SIGNAL: " << (signalEvent->signal == SignalType::BUY ? "BUY" : "SELL") << "\n";
        }
    }

    return 0;
}