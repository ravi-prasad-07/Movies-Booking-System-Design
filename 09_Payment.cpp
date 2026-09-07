#pragma once

// Payment: the abstract payment contract. Demonstrates ABSTRACTION -
// callers only ever see "pay(amount) -> bool", never the mechanics of
// any particular payment method.
// Must NOT contain any concrete payment logic itself.
class Payment {
public:
    virtual bool pay(double amount) = 0; // pure virtual
    virtual ~Payment() {}
};
