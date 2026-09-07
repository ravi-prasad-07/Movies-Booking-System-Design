#pragma once
#include <string>
using namespace std;

// Seat: knows its physical seat number and seat type only.
// Must NOT know whether it is booked for any particular show -
// that is ShowSeat's job.
class Seat {
private:
    int seatNumber;
    string seatType; // SILVER / GOLD / PLATINUM

public:
    Seat(int seatNumber = 0, string seatType = "SILVER")
        : seatNumber(seatNumber), seatType(seatType) {}

    int getSeatNumber() const { return seatNumber; }
    string getSeatType() const { return seatType; }
};
