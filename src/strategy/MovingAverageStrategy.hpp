#pragma once

#include <memory>
#include <deque>

#include "../core/EventQueue.hpp"
#include "../events/MarketEvent.hpp"
#include "../events/OrderEvent.hpp"

class MovingAverageStrategy {
    public:
        MovingAverageStrategy(EventQueue& eventQueue, int window) : eventQueue(eventQueue), window(window), currentPosition(0) {}

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

            auto order = std::make_shared<OrderEvent>();
            order->timeStamp = event.timeStamp;
            order->quantity = 10;
            order->referencePrice = event.price;

            if(event.price > avg  && currentPosition <= 0) {
                order->orderType = OrderType::BUY;
                eventQueue.push(order);
                currentPosition = 1;
            } else if(event.price < avg && currentPosition >= 0) {
                order->orderType = OrderType::SELL;
                eventQueue.push(order);
                currentPosition = -1;
            }

            // auto signal = std::make_shared<SignalEvent>();
            // signal->timeStamp = event.timeStamp;

            // if(event.price > avg) {
            //     signal->signal = SignalType::BUY;
            // } else {
            //     signal->signal = SignalType::SELL;
            // }

            // eventQueue.push(signal);
        }

    private:
        EventQueue& eventQueue;
        int window;
        std::deque<double> prices;
        int currentPosition;
};