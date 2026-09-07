#pragma once
#include "04_Cinema.cpp"
#include "05_Show.cpp"
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
#include <vector>
#include <iostream>
using namespace std;

// BookingService: the orchestrator. Runs the booking flow end to end by
// calling the other classes; owns none of the business rules itself.
// Dependency Inversion: it depends on the abstract Payment type, never
// on UpiPayment/CardPayment/CashPayment directly (main.cpp decides which
// concrete Payment to hand it), so adding NetBanking needs no change here.
// Must NOT read from or write to the console directly (that is main's job)
// except for the simulated payment log, which is Payment's job, not this one.
class BookingService {
private:
    vector<Movie*> movies;
    vector<Show*> shows;
    Booking* lastBooking = nullptr;

public:
    void addMovie(Movie* m) { movies.push_back(m); }
    void addShow(Show* s) { shows.push_back(s); }

    vector<Movie*> listMovies() const { return movies; }
    vector<Show*> listShows() const { return shows; }

    Show* getShowByIndex(int index) const {
        if (index < 1 || index > (int)shows.size()) return nullptr;
        return shows[index - 1];
    }

    // FR4: reject the whole booking if ANY requested seat is already
    // booked, and change nothing in that case.
    Booking* bookSeats(Show* show, vector<int> seatNumbers, Customer customer) {
        vector<ShowSeat*> requestedSeats;
        vector<ShowSeat>& showSeats = show->getShowSeats();

        for (int seatNo : seatNumbers) {
            ShowSeat* match = nullptr;
            for (ShowSeat& ss : showSeats) {
                if (ss.getSeat().getSeatNumber() == seatNo) { match = &ss; break; }
            }
            if (match == nullptr) return nullptr;          // invalid seat number
            if (match->getStatus() == "BOOKED") return nullptr; // already booked
            requestedSeats.push_back(match);
        }

        for (ShowSeat* s : requestedSeats) s->bookSeat();

        double total = PriceCalculator::calculateTotal(requestedSeats);
        lastBooking = new Booking(show, requestedSeats, customer, total);
        return lastBooking;
    }

    // FR6: exactly one Payment method per booking, via the abstract type
    bool makePayment(Booking* booking, Payment* method) {
        bool paymentSucceeded = method->pay(booking->getTotalAmount());
        if (paymentSucceeded) booking->confirm();
        else booking->fail();
        return paymentSucceeded;
    }

    void printLastTicket() {
        if (lastBooking != nullptr) TicketPrinter::printTicket(lastBooking);
        else cout << "No booking to print yet.\n";
    }

    void cancelLastBooking() {
        if (lastBooking != nullptr && lastBooking->getStatus() == "CONFIRMED") {
            lastBooking->cancelBooking();
            cout << "Booking " << lastBooking->getBookingId() << " cancelled. Seats released.\n";
        } else {
            cout << "No active confirmed booking to cancel.\n";
        }
    }

    Booking* getLastBooking() const { return lastBooking; }
};
