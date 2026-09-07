#pragma once
#include "03_Screen.cpp"
#include <vector>
#include <string>
using namespace std;

// Cinema: knows its name and the screens it physically houses.
// Composition with Screen - a Screen does not outlive its Cinema.
// Must NOT run the menu or booking logic (that is BookingService/main's job).
class Cinema {
private:
    string name;
    vector<Screen> screens; // composition (1 Cinema *-- 1..* Screen)

public:
    Cinema(string name) : name(name) {}

    void addScreen(const Screen& s) { screens.push_back(s); }

    string getName() const { return name; }
    vector<Screen>& getScreens() { return screens; }
};
