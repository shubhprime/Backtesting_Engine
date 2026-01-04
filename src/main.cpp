#include <iostream>
#include "./data/MarketDataHandler.hpp"

int main() {
    MarketDataHandler data("../data/prices.csv");

    while (data.has_next()) {
        MarketEvent event = data.next();
        std::cout << event.timeStamp << " → " << event.price << "\n";
    }

    return 0;
}