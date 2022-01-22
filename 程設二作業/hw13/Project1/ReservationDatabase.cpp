// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <fstream>
using namespace std;
#include "ReservationDatabase.h"

// ReservationDatabase default constructor loads reservations from the file Reservation details.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores reservations into the file Reservation details.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

void ReservationDatabase::loadReservations()
{
    ifstream inFile("Reservation details.dat", ios::binary);

    if (!inFile)
    {
        ofstream outFile("Reservation details.dat", ios::binary);
        outFile.close();
    }
    else
    {
        Reservation temp;
        inFile.seekg(0, ios::end);
        int end = inFile.tellg();
        int times = end / sizeof(temp);
        inFile.seekg(0, ios::beg);

        for (int i = 0; i < times; i++)
        {
            inFile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
            reservations.push_back(temp);
        }
           
    }
   
}

void ReservationDatabase::storeReservations()
{
    ofstream outFile("Reservation details.dat", ios::binary);

    for (int i = 0; i < reservations.size(); i++)
        outFile.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(reservations[i]));

}

bool ReservationDatabase::exist( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return true; // return true if match found

   return false; // if no matching reservation was found, return false
}

void ReservationDatabase::displayReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   it->displayReservationDetails();
}

void ReservationDatabase::cancelReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   reservations.erase( it );
   cout << "Reservation Cancelled.\n\n";
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
}

void ReservationDatabase::reduceSeats( string idNumber, string reservationNumber )
{
    vector< Reservation >::iterator it = searchReservation(idNumber, reservationNumber);
    int adultnumber = 0, concessnumber = 0,totaladult=0, totalconcess=0;
    cout << "\nHow many adult tickets to cancel¡H";
    cin >> adultnumber;
    cout << "How many concession tickets to cancel¡H";
    cin >> concessnumber;

    totaladult = it->getAdultTickets() - adultnumber;
    totalconcess = it->getConcessionTickets() - concessnumber;

    it->setAdultTickets(totaladult);
    it->setConcessionTickets(totalconcess);

    it->displayReservationDetails();

    cout << "\nYou have successfully reduced the number of tickets!";
}

vector< Reservation >::iterator ReservationDatabase::searchReservation( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return it; // return iterator to thecurrent reservation if match found

   return reservations.end();
}