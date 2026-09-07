# Movie Ticket Booking System — C++ Console App

## How to compile and run
This project follows the "one class per file, no header files" rule using
`#pragma once` include-guards; every class file is `#include`d into the next,
and `main.cpp` pulls in the whole chain, so a single-command build works:

```
g++ -std=c++17 -Wall -o booking main.cpp
./booking
```

## Files (in dependency order)
- 01_Movie.cpp
- 02_Seat.cpp
- 03_Screen.cpp
- 04_Cinema.cpp
- 05_Show.cpp
- 06_ShowSeat.cpp
- 07_Customer.cpp
- 08_Booking.cpp
- 09_Payment.cpp            (abstract base)
- 10_PaymentTypes.cpp       (UpiPayment, CardPayment, CashPayment)
- 11_PriceCalculator.cpp
- 12_TicketPrinter.cpp
- 13_BookingService.cpp     (orchestrator)
- main.cpp                  (console menu)

## Edge cases handled (see demo_run_output.txt)
1. Booking a seat that is already BOOKED -> rejected, nothing changes.
2. Cancelling a CONFIRMED booking -> its seats become AVAILABLE again.
3. Invalid menu choice / non-numeric input -> clear message, no crash.
4. Cancelling when there is no active confirmed booking -> clear message.

demo_run_output.txt contains two captured runs:
  1) a normal booking + payment + ticket print + cancel flow
  2) a rejected double-booking, an invalid menu input, and a cancel-after-cancel case
