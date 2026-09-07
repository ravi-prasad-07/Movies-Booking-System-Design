#pragma once
#include "06_ShowSeat.cpp"
#include <vector>
#include <string>
using namespace std;

// PriceCalculator: turns a list of seats into a total amount. Nothing else.
// Must NOT book seats, take payment, or print anything.
class PriceCalculator {
public:
    // constants instead of magic numbers (clean-code checklist)
    static const int SILVER_PRICE = 150;
    static const int GOLD_PRICE = 250;
    static const int PLATINUM_PRICE = 400;

    static double calculateTotal(const vector<ShowSeat*>& seats) {
        double total = 0;
        for (ShowSeat* s : seats) {
            string seatType = s->getSeat().getSeatType();
            if (seatType == "SILVER") total += SILVER_PRICE;
            else if (seatType == "GOLD") total += GOLD_PRICE;
            else if (seatType == "PLATINUM") total += PLATINUM_PRICE;
        }
        return total;
    }
};
