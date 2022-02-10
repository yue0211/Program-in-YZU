// NorthboundTimetable.h
// NorthboundTimetable class definition. Represents the northbound timetable.
#ifndef NORTHBOUND_TIMETABLE_H
#define NORTHBOUND_TIMETABLE_H

#include "Vector.h"
//#include <vector>
#include "Train.h"

class NorthboundTimetable
{
public:
   NorthboundTimetable();   // call loadNorthboundTimetable()

   // returns departureTimes[ station ] for the northbound train with the specified trainNumber
   string getDepartureTimes( string trainNumber, int station );

   // returns true iff there is a northbound train whose departure time
   // for the origin station is just after the user entered departure time
   bool trainsAvailable( int departureTime, int originStation, int destinationStation );

   // display timetables for 10 coming northbound trains with
   // the departure time for the origin station >= departureTimes[ departureTime ],
   // the departure time for the origin station != "-", and
   // the departure time for the destination station != "-"
   void displayComingTrains( int departureTime, int originStation, int destinationStation );
private:
   vector< Train > northboundTimetable; // the northbound timetable

   // loads the northbound timetable from the file "Northbound timetable.dat"
   void loadNorthboundTimetable();

   // returns an iterator which points to the northbound train with the specified trainNumber
   vector< Train >::iterator searchTrain( string trainNumber );
};

#endif // NORTHBOUND_TIMETABLE_H