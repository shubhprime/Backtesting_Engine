#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include "../events/FillEvent.hpp"

class Portfolio {
    public: 
        Portfolio(double initialCash) : cash(initialCash), position(0), lastPrice(0.0) {
            equityCurve.push_back(initialCash);
        }

        void onFillEvent(const FillEvent& fillEvent) {
            lastPrice = fillEvent.fillPrice;

            if(fillEvent.orderType == OrderType::BUY) {
                position += fillEvent.quantity;
                cash -= fillEvent.fillPrice * fillEvent.quantity;
            } else {
                position -= fillEvent.quantity;
                cash += fillEvent.fillPrice * fillEvent.quantity;
            }

            cash -= fillEvent.commission;

            printStatus();
            equityCurve.push_back(getPnL());
            double pnl = getPnL();
            assert(std::abs(pnl - (cash + position * lastPrice)) < 1e-6);
        }

        double getPnL() const {
            return cash + (position * lastPrice);
        }

        const std::vector<double>& getEquityCurve() const {
            return equityCurve;
        }


    private:
        double cash;
        int position;
        double lastPrice;
        std::vector<double> equityCurve;

        void printStatus() const {
            std::cout << "      POSITION: " << position << " | CASH: " << cash << " | PnL: " << getPnL() << "\n";
        }
};