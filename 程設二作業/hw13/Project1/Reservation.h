// Reservation.h
// Reservation class definition. Represents a reservation.
#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

class Reservation
{
public:
   Reservation( string theReservationNumber = "", string theTrainNumber = "",
                string theIdNumber = "", string thePhone = "", string theDate = "",
                int theOriginStation = 0, int theDestinationStation = 12,
                int theCarClass = 1, int theAdultTickets = 1, int theConcessionTickets = 0 );

   void setReservationNumber( string theReservationNumber );
   string getReservationNumber();

   void setTrainNumber( string theTrainNumber );

   void setIdNumber( string theIdNumber );
   string getIdNumber();

   void setPhone( string thePhone );

   void setDate( string theDate );

   void setOriginStation( int theOriginStation );
   int getOriginStation();

   void setDestinationStation( int theDestinationStation );
   int getDestinationStation();

   void setCarClass( int theCarClass );

   void setAdultTickets( int theAdultTickets );
   int getAdultTickets();

   void setConcessionTickets( int theConcessionTickets );
   int getConcessionTickets();

   void displayReservationDetails(); // display the information of a reservation

private:
   char reservationNumber[ 12 ]; // used to identify a reservation
   char trainNumber[ 8 ]; // used to identify a train
   char idNumber[ 12 ]; // the id number of the contact person
   char phone[ 12 ]; // the (local or mobile) phone number of the contact person
   char date[ 12 ]; // outbound date
   int originStation; // the origin station code
   int destinationStation; // the destination station code
   int carClass; // the car class code; 1:standard car, 2:business car
   int adultTickets; // the number of adult tickets
   int concessionTickets; // the number of concession tickets
};

#endif