// ReservationHistory.h
// ReservationHistory class definition. Represents reservation history

#ifndef VIEWING_CANCELING_H
#define VIEWING_CANCELING_H

#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "SouthboundTimetable.h" // SouthboundTimetable class definition
#include "NorthboundTimetable.h" // SouthboundTimetable class definition

class ReservationHistory
{
public:
   ReservationHistory( ReservationDatabase &theReservationDatabase,
                       SouthboundTimetable &theSouthboundTimetable,
                       NorthboundTimetable &theNorthboundTimetable );
   void execute();     // perform the operation

private:
   char idNumber[ 12 ]; // the id number of the contact person
   char reservationNumber[ 12 ]; // used to identify a reservation
   ReservationDatabase &reservationDatabase; // reference to the reservation database
   SouthboundTimetable &southboundTimetable; // reference to the southbound timetable
   NorthboundTimetable &northboundTimetable; // reference to the northbound timetable
};

#endif // VIEWING_CANCELING_H