#include <iostream>
#include "ReservationHistory.h" // ReservationHistory class definition

extern int inputAnInteger( int begin, int end );

// ReservationHistory default constructor
ReservationHistory::ReservationHistory( ReservationDatabase &theReservationDatabase,
                                        SouthboundTimetable &theSouthboundTimetable,
                                        NorthboundTimetable &theNorthboundTimetable )
   : idNumber(),
     reservationNumber(),
     reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
} // end ReservationHistory default constructor

void ReservationHistory::execute()
{
    cout << "\nEnter ID Number:  ";
    cin >> idNumber;
    cout << "\nEnter Reservation Number: ";
    cin >> reservationNumber;

    if (!reservationDatabase.exist(idNumber, reservationNumber))
    {
        cout << "\nReservation record not found.\n\n";
        return;
    }

    cout << "\nReservation Details";

    reservationDatabase.displayReservation(idNumber, reservationNumber);

    int choice;

    cout << "\nEnter Your Choice\n"
        << "1. Cancellation\n"
        << "2. Reduce\n"
        << "3. End";

    do cout << "\n? ";
    while ((choice = inputAnInteger(1, 3)) == -1);
    cout << endl;

    switch (choice)
    {
        case 1:
            reservationDatabase.cancelReservation(idNumber, reservationNumber);
            break;
        case 2:
            reservationDatabase.reduceSeats(idNumber, reservationNumber);
            break;
        case 3:
            break;
    }
     
}