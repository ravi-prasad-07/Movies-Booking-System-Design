#pragma once
#include "05_Show.cpp"
#include "06_ShowSeat.cpp"
#include "07_Customer.cpp"
#include <vector>
#include <string>
using namespace std;

// Booking: knows a booking id, which show, which ShowSeats, which
// customer, the total amount and the status (PENDING/CONFIRMED/FAILED/
// CANCELLED). Encapsulation: status/totalAmount are private and only
// change through confirm()/fail()/cancelBooking().
// Aggregation with Show and ShowSeat - a Booking references them but
// they exist independently (cancelling a booking must not delete the
// show or the seats, only flip their status back).
// Association with Customer - the same Customer can have many bookings.
// Must NOT print tickets or talk to a Payment object directly.
class Booking {
private:
    int bookingId;
    static int nextBookingId; // static member -> unique ids across all objects

    Show* show;                  // aggregation
    vector<ShowSeat*> showSeats; // aggregation
    Customer customer;
    double totalAmount;
    string status;

public:
    Booking(Show* show, vector<ShowSeat*> showSeats, Customer customer, double totalAmount)
        : show(show), showSeats(showSeats), customer(customer),
          totalAmount(totalAmount), status("PENDING") {
        this->bookingId = nextBookingId++; // 'this' used to be explicit/clear
    }

    int getBookingId() const { return bookingId; }
    Show* getShow() const { return show; }
    vector<ShowSeat*> getShowSeats() const { return showSeats; }
    Customer getCustomer() const { return customer; }
    double getTotalAmount() const { return totalAmount; }
    string getStatus() const { return status; }

    void confirm() { status = "CONFIRMED"; }

    // FR6: a failed payment must not confirm the booking, and its seats
    // must be released back to AVAILABLE
    void fail() {
        status = "FAILED";
        for (ShowSeat* s : showSeats) s->cancelSeat();
    }

    // FR8: cancelling a booking releases its seats
    void cancelBooking() {
        status = "CANCELLED";
        for (ShowSeat* s : showSeats) s->cancelSeat();
    }
};

int Booking::nextBookingId = 1001;
