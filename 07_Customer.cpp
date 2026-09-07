#pragma once
#include <string>
using namespace std;

// Customer: knows only a name and a phone number.
// Must NOT know about bookings, seats, or payments.
class Customer {
private:
    string name;
    string phone;

public:
    Customer(string name = "Guest", string phone = "NA")
        : name(name), phone(phone) {}

    string getName() const { return name; }
    string getPhone() const { return phone; }
};
