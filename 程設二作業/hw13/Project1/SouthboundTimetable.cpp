// FlightSchedule.cpp
// Member-function definitions for class SouthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "SouthboundTimetable.h"

extern string departureTimes[ 37 ];

// SouthboundTimetable default constructor
// loads southbound timetable from the file "Southbound timetable.dat"
SouthboundTimetable::SouthboundTimetable()
{
   loadSouthboundTimetable();
}

void SouthboundTimetable::loadSouthboundTimetable()
{
    ifstream inFile("Southbound timetable.dat", ios::in | ios::binary);

    Train a;
    int size = sizeof(a.getTrainNumber());
    for (int i = 0; i < 13; i++)
        size += sizeof(a.getDepartureTimes(i));

    inFile.seekg(0, ios::end); 	//seekg的第一個參數是偏移量 ,第二個參數是起始地址 
    int end = inFile.tellg();

    int times = 87;   //計算讀取所需花的次數

    inFile.seekg(0, ios::beg);

    for (int i = 0; i < times; i++)
    {
        inFile.read(reinterpret_cast<char*>(&a), sizeof(a));
        southboundTimetable.push_back(a);
    }

    inFile.close();
    
}

// returns departureTimes[ station ]
string SouthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool SouthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
    for (int k = 0; k < southboundTimetable.size(); k++)
    {
        if (southboundTimetable[k].getDepartureTimes(originStation) != "-" &&southboundTimetable[k].getDepartureTimes(destinationStation) != "-"&&(southboundTimetable[k].getDepartureTimes(originStation)[0] * 10 + southboundTimetable[k].getDepartureTimes(originStation)[1]) * 60 + (southboundTimetable[k].getDepartureTimes(originStation)[3] * 10 + southboundTimetable[k].getDepartureTimes(originStation)[4]) >=
            (departureTimes[departureTime][0] * 10 + departureTimes[departureTime][1]) * 60 + (departureTimes[departureTime][3] * 10 + departureTimes[departureTime][4]) )
        {
            return true; 
        }
   }
    return false;
}

void SouthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
    int count = 0;

    cout << "\nTrain No.  Departure  Arrival\n";

    for (int k = 0; k < southboundTimetable.size() && count != 10; k++)
    {
        if (southboundTimetable[k].getDepartureTimes(originStation) != "-" && southboundTimetable[k].getDepartureTimes(destinationStation) != "-" && (southboundTimetable[k].getDepartureTimes(originStation)[0] * 10 + southboundTimetable[k].getDepartureTimes(originStation)[1]) * 60 + (southboundTimetable[k].getDepartureTimes(originStation)[3] * 10 + southboundTimetable[k].getDepartureTimes(originStation)[4]) >=
            (departureTimes[departureTime][0] * 10 + departureTimes[departureTime][1]) * 60 + (departureTimes[departureTime][3] * 10 + departureTimes[departureTime][4]) )
        {
            count += 1;
            cout << setw(9) << southboundTimetable[k].getTrainNumber()<< setw(11) << southboundTimetable[k].getDepartureTimes(originStation) << setw(9) << southboundTimetable[k].getDepartureTimes(destinationStation) << endl;
        }
    }

}

vector< Train >::iterator SouthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = southboundTimetable.begin();
   for( ; it != southboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return southboundTimetable.end();
}