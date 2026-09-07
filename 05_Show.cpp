#pragma once
#include "01_Movie.cpp"
#include "03_Screen.cpp"
#include "06_ShowSeat.cpp"
#include <vector>
#include <string>
using namespace std;

// Show: one screening = a Movie on a Screen at a start time.
// Aggregation with Movie and Screen - a Show BORROWS them; cancelling a
// show must not destroy the movie or the screen it used.
// Composition with ShowSeat - the per-show seat statuses are created
// fresh for this Show and are meaningless without it.
// Must NOT calculate prices or take payments.
class Show {
private:
    Movie* movie;               // aggregation
    Screen* screen;             // aggregation
    string startTime;
    vector<ShowSeat> showSeats; // composition (1 Show *-- 1..* ShowSeat)

public:
    Show(Movie* movie, Screen* screen, string startTime)
        : movie(movie), screen(screen), startTime(startTime) {
        vector<Seat> physicalSeats = screen->getSeats();
        for (Seat& s : physicalSeats) {
            showSeats.push_back(ShowSeat(s));
        }
    }

    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }
};
