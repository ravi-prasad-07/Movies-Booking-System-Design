#pragma once
#include "08_Booking.cpp"
#include <iostream>
using namespace std;

// TicketPrinter: formats and prints a ticket. Printing only.
// Must NOT change a Booking's status or any seat's status.
class TicketPrinter {
public:
    static void printTicket(Booking* booking) {
        bool isConfirmedTicket = (booking->getStatus() == "CONFIRMED");
        if (!isConfirmedTicket) {
            cout << "Cannot print ticket: booking is not CONFIRMED.\n";
            return;
        }

        vector<ShowSeat*> bookedSeats = booking->getShowSeats();

        cout << "\n========== MOVIE TICKET ==========\n";
        cout << "Booking ID : " << booking->getBookingId() << endl;
        cout << "Movie      : " << booking->getShow()->getMovie()->getTitle() << endl;
        cout << "Screen     : " << booking->getShow()->getScreen()->getScreenNumber() << endl;
        cout << "Show Time  : " << booking->getShow()->getStartTime() << endl;
        cout << "Seats      : ";
        for (size_t i = 0; i < bookedSeats.size(); i++) {
            cout << bookedSeats[i]->getSeat().getSeatNumber();
            if (i != bookedSeats.size() - 1) cout << ", ";
        }
        cout << endl;
        cout << "Total      : Rs. " << booking->getTotalAmount() << endl;
        cout << "Status     : " << booking->getStatus() << endl;
        cout << "===================================\n";
    }
};
