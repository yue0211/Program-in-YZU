// SouthboundTimetable.h
// SouthboundTimetable class definition. Represents the southbound timetable.
#ifndef SOUTHBOUND_TIMETABLE_H
#define SOUTHBOUND_TIMETABLE_H

#include "Vector.h"
//#include <vector>
#include "Train.h"

class SouthboundTimetable
{
public:
   SouthboundTimetable();   // call loadSouthboundTimetable()

   // returns departureTimes[ station ] for the southbound train with the specified trainNumber
   string getDepartureTimes( string trainNumber, int station );

   // returns true iff there is a southbound train whose departure time
   // for the origin station is just after the user entered departure time
   bool trainsAvailable( int departureTime, int originStation, int destinationStation );

   // display timetables for 10 coming southbound trains with
   // the departure time for the origin station >= departureTimes[ departureTime ],
   // the departure time for the origin station != "-", and
   // the departure time for the destination station != "-"
   void displayComingTrains( int departureTime, int originStation, int destinationStation );
private:
   vector< Train > southboundTimetable; // the southbound timetable

   // loads the southbound timetable from the file "Southbound timetable.dat"
   void loadSouthboundTimetable();

   // returns an iterator which points to the southbound train with the specified trainNumber
   vector< Train >::iterator searchTrain( string trainNumber );
};

#endif // SOUTHBOUND_TIMETABLE_H
