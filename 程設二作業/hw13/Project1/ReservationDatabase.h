// ReservationDatabase.h
// ReservationDatabase class definition. Represents the reservation database.
#ifndef RESERVATION_DATABASE_H
#define RESERVATION_DATABASE_H

#include "Vector.h"
//#include <vector>
#include "Reservation.h"

class ReservationDatabase
{
public:
   // constructor loads train reservations from the file Reservation details.dat
   ReservationDatabase();

   // destructor stores train reservations into the file Reservation details.dat
   ~ReservationDatabase();

   bool exist( string idNumber, string reservationNumber );

   // calls it->displayReservationDetails()
   void displayReservation( string idNumber, string reservationNumber );

   // cancels the Reservation object pointed by it
   void cancelReservation( string idNumber, string reservationNumber );

   // calls reservations.push_back( reservation );
   void addReservation( Reservation reservation );

   // reduces adultTickets and concessionTickets in the Reservation object pointed by it
   void reduceSeats( string idNumber, string reservationNumber );
private:
   vector< Reservation > reservations; // vector of the train reservations

   void loadReservations(); // loads train reservations from the file Reservation details.dat
   void storeReservations(); // stores train reservations into the file Reservation details.dat

   // returns an iterator which points to a Reservation object
   // with specified idNumber and reservationNumber
   vector< Reservation >::iterator searchReservation( string idNumber, string reservationNumber );
};

#endif // RESERVATION_DATABASE_H