#pragma once
#include "09_Payment.cpp"
#include <iostream>
using namespace std;

// UpiPayment / CardPayment / CashPayment: INHERITANCE - each IS-A Payment
// and implements pay() its own way. Calling code holds a Payment* and
// gets RUNTIME POLYMORPHISM: the correct pay() runs without the caller
// knowing which subclass it actually has.
// Must NOT do anything except decide success/failure of one payment.

class UpiPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Processing UPI payment of Rs. " << amount << endl;
        return true; // simulated gateway success
    }
};

class CardPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Processing Card payment of Rs. " << amount << endl;
        return true; // simulated gateway success
    }
};

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Processing Cash payment of Rs. " << amount << endl;
        return true; // cash collected at counter always "succeeds"
    }
};
