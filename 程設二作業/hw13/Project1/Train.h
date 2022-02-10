// Train.h
// Train class definition. Represents a train.
#ifndef TRAIN_H
#define TRAIN_H

#include <string>
using namespace std;

class Train
{
public:
   Train( string theTrainNumber = "", string *theDepartureTimes = nullptr );
   string getTrainNumber();                 // returns trainNumber
   string getDepartureTimes( int station ); // returns departureTimes[ station ]
private:
   char trainNumber[ 8 ];          // used to identify a train
   char departureTimes[ 13 ][ 8 ]; // the departure time of a train for each station

   void setTrainNumber( string theTrainNumber );
   void setDepartureTimes( string *theDepartureTimes );
};

#endif