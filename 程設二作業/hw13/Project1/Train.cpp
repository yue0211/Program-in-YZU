// Train.cpp
// Member-function definitions for class Train.
#include "Train.h"

Train::Train( string theTrainNumber, string *theDepartureTimes )
{
   setTrainNumber( theTrainNumber );
   setDepartureTimes( theDepartureTimes );
}

void Train::setTrainNumber( string theTrainNumber )
{
   int length = theTrainNumber.size();
   length = ( length < 8 ? length : 7 );
   for( int i = 0; i < length; i++ )
      trainNumber[ i ] = theTrainNumber[ i ];
   trainNumber[ length ] = '\0';
}

string Train::getTrainNumber()
{
   return trainNumber;
}

void Train::setDepartureTimes( string *theDepartureTimes )
{
   // important! if this case is not considered, there will be many runtime errors
   if( theDepartureTimes == nullptr )
      for( int i = 0; i < 13; i++ )
         departureTimes[ i ][ 0 ] = '\0';
   else
      for( int i = 0; i < 13; i++ )
      {
         int length = theDepartureTimes[i].size();
         length = ( length < 8 ? length : 7 );
         for( int j = 0; j < length; j++ )
            departureTimes[ i ][ j ] = theDepartureTimes[ i ][ j ];
         departureTimes[ i ][ length ] = '\0';
      }
}

string Train::getDepartureTimes( int station )
{
   return departureTimes[ station ];
}