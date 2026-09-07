#pragma once
#include "02_Seat.cpp"
#include <vector>
using namespace std;

// Screen: knows its screen number and the seats physically fixed inside it.
// Composition with Seat - a Seat has no meaning outside its Screen.
// Must NOT know about shows or bookings.
class Screen {
private:
    int screenNumber;
    vector<Seat> seats; // composition (1 Screen *-- 1..* Seat)

public:
    Screen(int screenNumber = 0) : screenNumber(screenNumber) {}

    void addSeat(const Seat& s) { seats.push_back(s); }

    int getScreenNumber() const { return screenNumber; }
    vector<Seat> getSeats() const { return seats; }
};
