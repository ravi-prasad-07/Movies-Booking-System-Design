#include "13_BookingService.cpp"
#include "10_PaymentTypes.cpp"
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

// Compile-time polymorphism demo: two overloaded helpers with the same
// name but different parameter lists.
void printMessage(string msg) { cout << msg << endl; }
void printMessage(string msg, int code) { cout << msg << " (code " << code << ")" << endl; }

void setupCatalog(Cinema& cinema, BookingService& service) {
    Screen screen1(1);
    screen1.addSeat(Seat(1, "SILVER"));
    screen1.addSeat(Seat(2, "SILVER"));
    screen1.addSeat(Seat(3, "GOLD"));
    screen1.addSeat(Seat(4, "GOLD"));
    screen1.addSeat(Seat(5, "PLATINUM"));

    Screen screen2(2);
    screen2.addSeat(Seat(1, "SILVER"));
    screen2.addSeat(Seat(2, "GOLD"));
    screen2.addSeat(Seat(3, "PLATINUM"));

    cinema.addScreen(screen1);
    cinema.addScreen(screen2);

    static Movie interstellar("Interstellar", "English", 169);
    static Movie idiots("3 Idiots", "Hindi", 170);
    static Movie inception("Inception", "English", 148);

    service.addMovie(&interstellar);
    service.addMovie(&idiots);
    service.addMovie(&inception);

    static Show show1(&interstellar, &cinema.getScreens()[0], "10:00 AM");
    static Show show2(&idiots, &cinema.getScreens()[0], "02:00 PM");
    static Show show3(&inception, &cinema.getScreens()[1], "06:30 PM");

    service.addShow(&show1);
    service.addShow(&show2);
    service.addShow(&show3);
}

bool readIntChoice(int& value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

void handleListMovies(BookingService& service) {
    vector<Movie*> movies = service.listMovies();
    cout << "\nAvailable Movies:\n";
    for (size_t i = 0; i < movies.size(); i++) {
        cout << (i + 1) << ". " << movies[i]->getTitle()
             << " | " << movies[i]->getLanguage()
             << " | " << movies[i]->getDuration() << " min\n";
    }
}

void handleListShows(BookingService& service) {
    vector<Show*> shows = service.listShows();
    cout << "\nAvailable Shows:\n";
    for (size_t i = 0; i < shows.size(); i++) {
        cout << (i + 1) << ". " << shows[i]->getMovie()->getTitle()
             << " | Screen " << shows[i]->getScreen()->getScreenNumber()
             << " | " << shows[i]->getStartTime() << endl;
    }
}

Show* pickShow(BookingService& service) {
    handleListShows(service);
    cout << "Enter show number: ";
    int showChoice;
    if (!readIntChoice(showChoice)) { printMessage("Invalid input.", 1); return nullptr; }
    Show* show = service.getShowByIndex(showChoice);
    if (show == nullptr) printMessage("Invalid show number.");
    return show;
}

void handleShowSeats(Show* show) {
    cout << "\nSeat Layout:\n";
    vector<ShowSeat>& seats = show->getShowSeats();
    for (ShowSeat& ss : seats) {
        cout << "Seat " << ss.getSeat().getSeatNumber()
             << " [" << ss.getSeat().getSeatType() << "] : "
             << ss.getStatus() << endl;
    }
}

vector<int> readSeatNumbers() {
    cout << "Enter seat number(s) to book (space separated): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream lineStream(line);
    vector<int> seatNumbers;
    int seatNo;
    while (lineStream >> seatNo) seatNumbers.push_back(seatNo);
    return seatNumbers;
}

Payment* chooseAndCreatePayment() {
    cout << "1. UPI\n2. Card\n3. Cash\n";
    cout << "Choose payment method: ";
    int method;
    if (!readIntChoice(method)) return nullptr;

    if (method == 1) return new UpiPayment();
    if (method == 2) return new CardPayment();
    if (method == 3) return new CashPayment();
    return nullptr;
}

void handleBookAndPay(BookingService& service, Customer& customer) {
    Show* show = pickShow(service);
    if (show == nullptr) return;

    handleShowSeats(show);
    vector<int> seatNumbers = readSeatNumbers();
    if (seatNumbers.empty()) { printMessage("No seats entered."); return; }

    Booking* booking = service.bookSeats(show, seatNumbers, customer);
    if (booking == nullptr) {
        printMessage("Booking rejected: invalid or already-booked seat. Nothing changed.");
        return;
    }

    Payment* payment = chooseAndCreatePayment();
    if (payment == nullptr) { printMessage("Invalid payment method."); return; }

    bool paymentSucceeded = service.makePayment(booking, payment);
    if (paymentSucceeded) {
        printMessage("Payment Successful");
        service.printLastTicket();
    } else {
        printMessage("Payment Failed. Booking not confirmed. Seats released.");
    }
    delete payment;
}

void showMenu() {
    cout << "\n===== MOVIE TICKET BOOKING =====\n";
    cout << "1. List Movies\n";
    cout << "2. List Shows\n";
    cout << "3. Show Seats\n";
    cout << "4. Book Seat and Pay\n";
    cout << "5. Print Last Ticket\n";
    cout << "6. Cancel Last Booking\n";
    cout << "7. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    Cinema cinema("PVR Cinemas");
    BookingService service;
    setupCatalog(cinema, service);
    Customer customer("Rahul", "9999999999");

    int choice = 0;
    do {
        showMenu();
        if (!readIntChoice(choice)) { printMessage("Invalid input. Enter a number."); continue; }

        switch (choice) {
            case 1: handleListMovies(service); break;
            case 2: handleListShows(service); break;
            case 3: {
                Show* show = pickShow(service);
                if (show != nullptr) handleShowSeats(show);
                break;
            }
            case 4: handleBookAndPay(service, customer); break;
            case 5: service.printLastTicket(); break;
            case 6: service.cancelLastBooking(); break;
            case 7: printMessage("Exiting. Thank you!"); break;
            default: printMessage("Invalid choice. Try again.");
        }
    } while (choice != 7);

    return 0;
}
