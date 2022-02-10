// NorthboundTimetable.cpp
// Member-function definitions for class NorthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "NorthboundTimetable.h"

extern string departureTimes[ 37 ];

// NorthboundTimetable default constructor
// loads northbound timetable from the file "Northbound timetable.dat"
NorthboundTimetable::NorthboundTimetable()
{
   loadNorthboundTimetable();
}

void NorthboundTimetable::loadNorthboundTimetable()
{
    ifstream inFile("Northbound timetable.dat", ios::in | ios::binary);

    Train a;
    int size = sizeof(a.getTrainNumber());
    for (int i = 0; i < 13; i++)
        size += sizeof(a.getDepartureTimes(i));

    inFile.seekg(0, ios::end); 	//seekg的第一個參數是偏移量 ,第二個參數是起始地址 
    int end = inFile.tellg();

    int times = 92;   //計算讀取所需花的次數

    inFile.seekg(0, ios::beg);

    for (int i = 0; i < times; i++)
    {
        inFile.read(reinterpret_cast<char*>(&a), sizeof(a));
        northboundTimetable.push_back(a);
    }


    inFile.close();
}

// returns departureTimes[ station ]
string NorthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool NorthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
    for (int k = 0; k < northboundTimetable.size() ; k++)
    {
        if (northboundTimetable[k].getDepartureTimes(originStation)!="-"&& northboundTimetable[k].getDepartureTimes(destinationStation)!="-"&&(northboundTimetable[k].getDepartureTimes(13 - originStation)[0] * 10 + northboundTimetable[k].getDepartureTimes(13 - originStation)[1]) * 60 + (northboundTimetable[k].getDepartureTimes(13 - originStation)[3] * 10 + northboundTimetable[k].getDepartureTimes(13 - originStation)[4]) >=
            (departureTimes[departureTime][0] * 10 + departureTimes[departureTime][1]) * 60 + (departureTimes[departureTime][3] * 10 + departureTimes[departureTime][4]))
        {
            return true;
        }
    }
    return false;
}

void NorthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
    int count = 0;

    cout << "\nTrain No.  Departure  Arrival\n";

    for (int k = 0; k < northboundTimetable.size() && count != 10; k++)
    {
        if (northboundTimetable[k].getDepartureTimes(13 - originStation) != "-" && northboundTimetable[k].getDepartureTimes(13- destinationStation) != "-" && (northboundTimetable[k].getDepartureTimes(13- originStation)[0] * 10 + northboundTimetable[k].getDepartureTimes(13 - originStation)[1]) * 60 + (northboundTimetable[k].getDepartureTimes(13 - originStation)[3] * 10 + northboundTimetable[k].getDepartureTimes(13 - originStation)[4]) >=
            (departureTimes[departureTime][0] * 10 + departureTimes[departureTime][1]) * 60 + (departureTimes[departureTime][3] * 10 + departureTimes[departureTime][4]))
        {
            count += 1;
            cout << setw(9) << northboundTimetable[k].getTrainNumber() << setw(11) << northboundTimetable[k].getDepartureTimes(13 - originStation) << setw(9) << northboundTimetable[k].getDepartureTimes(13- destinationStation) << endl;
        }
    }


}

vector< Train >::iterator NorthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = northboundTimetable.begin();
   for( ; it != northboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return northboundTimetable.end();
}