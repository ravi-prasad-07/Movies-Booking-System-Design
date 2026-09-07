#pragma once
#include <string>
using namespace std;

// Movie: knows a title, language and duration only.
// Must NOT know about shows, screens or bookings.
class Movie {
private:
    string title;
    string language;
    int duration; // minutes

public:
    Movie(string title, string language, int duration)
        : title(title), language(language), duration(duration) {}

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDuration() const { return duration; }
};
