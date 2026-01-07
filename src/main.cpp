#include <iostream>
#include "./data/MarketDataHandler.hpp"
#include "./core/EventQueue.hpp"
#include "./events/MarketEvent.hpp"
#include "./events/SignalEvent.hpp"
#include "./events/OrderEvent.hpp"
#include "./strategy/MovingAverageStrategy.hpp"
#include "./execution/ExecutionSimulator.hpp"

int main() {
    EventQueue eventQueue;
    MarketDataHandler data("./data/prices.csv", eventQueue);
    MovingAverageStrategy strategy(eventQueue, 3);
    ExecutionSimulator executor(eventQueue);
    double lastPrice = 0.0;

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
        } else if(event->type == EventType::ORDER) {
            auto orderEvent = std::static_pointer_cast<OrderEvent>(event);

            std::cout << " Order: " << (orderEvent->orderType == OrderType::BUY ? "BUY" : "SELL") << "\n";

            executor.onOrderEvent(*orderEvent);
        } else if(event->type == EventType::FILL) {
            auto fillEvent = std::static_pointer_cast<FillEvent>(event);

            std::cout << "    FILL @ " << fillEvent->fillPrice << " x" << fillEvent->quantity << "\n";
        }
    }

    return 0;
}