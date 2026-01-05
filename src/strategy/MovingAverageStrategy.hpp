#pragma once

#include <memory>
#include <deque>

#include "../core/EventQueue.hpp"
#include "../events/MarketEvent.hpp"
#include "../events/SignalEvent.hpp"

class MovingAverageStrategy {
    public:
        MovingAverageStrategy(EventQueue& eventQueue, int window) : eventQueue(eventQueue), window(window) {}

        void onMarketEvent(const MarketEvent& event) {
            prices.push_back(event.price);

            if(prices.size() < window) {
                return;
            }

            if(prices.size() > window) {
                prices.pop_front();
            }

            double sum{0.0};

            for(double p : prices) {
                sum += p;
            }

            double avg = sum / window;

            auto signal = std::make_shared<SignalEvent>();
            signal->timeStamp = event.timeStamp;

            if(event.price > avg) {
                signal->signal = SignalType::BUY;
            } else {
                signal->signal = SignalType::SELL;
            }

            eventQueue.push(signal);
        }

    private:
        EventQueue& eventQueue;
        int window;
        std::deque<double> prices;
};