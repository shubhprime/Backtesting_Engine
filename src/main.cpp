#include <iostream>
#include <fstream>
#include "./data/MarketDataHandler.hpp"
#include "./core/EventQueue.hpp"
#include "./events/MarketEvent.hpp"
#include "./events/OrderEvent.hpp"
#include "./events/FillEvent.hpp"
#include "./strategy/MovingAverageStrategy.hpp"
#include "./execution/ExecutionSimulator.hpp"
#include "./portfolio/Portfolio.hpp"

int main() {
    EventQueue eventQueue;
    MarketDataHandler data("./data/prices.csv", eventQueue);
    MovingAverageStrategy strategy(eventQueue, 3);
    ExecutionSimulator executor(eventQueue, 1.0);
    // ExecutionSimulator executor(eventQueue, 0.0);

    //SCALED TRANSACTION COST
    // ExecutionSimulator executor(eventQueue, 500.0);

    double lastPrice = 0.0;
    Portfolio portfolio(100000.0);

    while (true) {
        data.stream_next();
        if (!data.has_more()) break;
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

            std::cout << "    FILL @ " << fillEvent->fillPrice << " x" << fillEvent->quantity << " | cost: " << fillEvent->commission << "\n";

            portfolio.onFillEvent(*fillEvent);
        }
    }

    std::ofstream out("assets/equity_curve_txnc_enabled.csv");
    // std::ofstream out("assets/equity_curve_txnc_disabled.csv");
    // std::ofstream out("assets/equity_curve_scaled_txnc_enabled.csv");
    
    for (double e : portfolio.getEquityCurve()) {
        out << e << "\n";
    }
    out.close();

    return 0;
}