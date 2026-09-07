#pragma once
#include "02_Seat.cpp"
#include <string>
using namespace std;

// ShowSeat: knows ONE physical Seat and its AVAILABLE/BOOKED status
// for one specific Show. This is why Seat A1 can be AVAILABLE for the
// 6 PM show and BOOKED for the 9 PM show - status lives here, not on Seat.
// Encapsulation: status is private; it can only change through
// bookSeat()/cancelSeat() so a caller can never set it to a bad value.
// Must NOT know which Show or Booking it belongs to.
class ShowSeat {
private:
    Seat seat;
    string status; // AVAILABLE / BOOKED

public:
    ShowSeat(Seat seat) : seat(seat), status("AVAILABLE") {}

    Seat getSeat() const { return seat; }
    string getStatus() const { return status; }

    // returns false (and changes nothing) if the seat is already booked
    bool bookSeat() {
        if (status == "AVAILABLE") {
            status = "BOOKED";
            return true;
        }
        return false;
    }

    void cancelSeat() { status = "AVAILABLE"; }
};
