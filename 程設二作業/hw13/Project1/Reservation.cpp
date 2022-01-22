// Reservation.cpp
// Member-function definitions for class Reservation.
#include <iostream>
#include <iomanip>
#include "SouthboundTimetable.h"
#include "NorthboundTimetable.h"
#include "Reservation.h"

int adultTicketPrice[ 13 ][ 13 ] = {
   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   0,    0,    0,    0,  500,  700,  920, 1330, 1510, 1660, 1880, 2290, 2500,
   0,   40,    0,    0,  440,  640,  850, 1250, 1430, 1600, 1820, 2230, 2440,
   0,   70,   40,    0,  400,  590,  800, 1210, 1390, 1550, 1780, 2180, 2390,
   0,  200,  160,  130,    0,  400,  620, 1010, 1210, 1370, 1580, 1990, 2200,
   0,  330,  290,  260,  130,    0,  410,  820, 1010, 1160, 1390, 1790, 2000,
   0,  480,  430,  400,  280,  140,    0,  610,  790,  950, 1160, 1580, 1790,
   0,  750,  700,  670,  540,  410,  270,    0,  400,  550,  770, 1180, 1390,
   0,  870,  820,  790,  670,  540,  390,  130,    0,  370,  580, 1000, 1210,
   0,  970,  930,  900,  780,  640,  500,  230,  110,    0,  430,  830, 1040,
   0, 1120, 1080, 1050,  920,  790,  640,  380,  250,  150,    0,  620,  820,
   0, 1390, 1350, 1320, 1190, 1060,  920,  650,  530,  420,  280,    0,  410,
   0, 1530, 1490, 1460, 1330, 1200, 1060,  790,  670,  560,  410,  140,    0 };

char place[13][13] = { "",
        "Nangang","Taipei","Banqiao","Taoyuan","Hsinchu",
        "Miaoli","Taichung","Changhua","Yunlin","Chiayi","Tainan","Zuoying"
};


Reservation::Reservation( string theReservationNumber, string theTrainNumber,
                          string theIdNumber, string thePhone, string theDate,
                          int theOriginStation, int theDestinationStation,
                          int theCarClass, int theAdultTickets , int theConcessionTickets )
{
   setReservationNumber( theReservationNumber );
   setTrainNumber( theTrainNumber );
   setIdNumber( theIdNumber );
   setPhone( thePhone );
   setDate( theDate );
   setOriginStation( theOriginStation );
   setDestinationStation( theDestinationStation );
   setCarClass( theCarClass );
   setAdultTickets( theAdultTickets );
   setConcessionTickets( theConcessionTickets );
}

void Reservation::setReservationNumber( string theReservationNumber )
{
   int length = theReservationNumber.size();
   length = ( length < 12 ? length : 11 );
   for( int i = 0; i < length; i++ )
      reservationNumber[ i ] = theReservationNumber[ i ];
   reservationNumber[ length ] = '\0';
}

string Reservation::getReservationNumber()
{
   string buffer( reservationNumber );
   return buffer;
}

void Reservation::setTrainNumber( string theTrainNumber )
{
   int length = theTrainNumber.size();
   length = ( length < 8 ? length : 7 );
   for( int i = 0; i < length; i++ )
      trainNumber[ i ] = theTrainNumber[ i ];
   trainNumber[ length ] = '\0';
}

void Reservation::setIdNumber( string theIdNumber )
{
   int length = theIdNumber.size();
   length = ( length < 12 ? length : 11 );
   for( int i = 0; i < length; i++ )
      idNumber[ i ] = theIdNumber[ i ];
   idNumber[ length ] = '\0';
}

string Reservation::getIdNumber()
{
   string buffer( idNumber );
   return buffer;
}

void Reservation::setPhone( string thePhone )
{
   int length = thePhone.size();
   length = ( length < 12 ? length : 11 );
   for( int i = 0; i < length; i++ )
      phone[ i ] = thePhone[ i ];
   phone[ length ] = '\0';
}

void Reservation::setDate( string theDate )
{
   int length = theDate.size();
   length = ( length < 12 ? length : 11 );
   for( int i = 0; i < length; i++ )
      date[ i ] = theDate[ i ];
   date[ length ] = '\0';
}

void Reservation::setOriginStation( int theOriginStation )
{
   if( theOriginStation >= 1 && theOriginStation <= 12 )
      originStation = theOriginStation;
   else
      originStation = 1;
}

int Reservation::getOriginStation()
{
    return originStation;
}

void Reservation::setDestinationStation( int theDestinationStation )
{
   if( theDestinationStation >= 1 && theDestinationStation <= 12 )
      destinationStation = theDestinationStation;
   else
      destinationStation = 1;
}

int Reservation::getDestinationStation()
{
   return destinationStation;
}

void Reservation::setCarClass( int theCarClass )
{
   carClass = ( ( theCarClass == 1 || theCarClass == 2 ) ? theCarClass : 0 );
}

void Reservation::setAdultTickets( int theAdultTickets )
{
   adultTickets = ( theAdultTickets > 0 ? theAdultTickets : 0 );
}

int Reservation::getAdultTickets()
{
   return adultTickets;
}

void Reservation::setConcessionTickets( int theConcessionTickets )
{
   concessionTickets = ( theConcessionTickets > 0 ? theConcessionTickets : 0 );
}

int Reservation::getConcessionTickets()
{
   return concessionTickets;
}

void Reservation::displayReservationDetails()
{
    SouthboundTimetable southboundTimetable;
    NorthboundTimetable northboundTimetable;
    cout<<"\n      Date  Train No.     From        To  Departure  Arrival   Adult  Concession  Fare     Class\n"
        << setw(10) << date << setw(11) << trainNumber << setw(9) << place[originStation] << setw(10) << place[destinationStation]
        << setw(11);

    if(originStation< destinationStation)
      cout << southboundTimetable.getDepartureTimes(trainNumber, originStation) << setw(9) << southboundTimetable.getDepartureTimes(trainNumber, destinationStation) << setw(6);
    else
        cout << northboundTimetable.getDepartureTimes(trainNumber, (13- originStation)) << setw(9) << northboundTimetable.getDepartureTimes(trainNumber, (13 - destinationStation)) << setw(6);

    int total = 0;
    if (carClass == 2)
    {
        if (originStation > destinationStation)
        {
            total = adultTicketPrice[destinationStation][originStation] * adultTickets + (adultTicketPrice[destinationStation][originStation] / 2) * concessionTickets;
            cout << adultTicketPrice[destinationStation][originStation] << "*" << adultTickets
                << setw(10) << (adultTicketPrice[destinationStation][originStation] / 2) << "*" << concessionTickets
                << setw(6) << total << setw(10) << "Business";
        }
        else
        {
            total = adultTicketPrice[originStation][destinationStation] * adultTickets + (adultTicketPrice[originStation][destinationStation] / 2) * concessionTickets;
            cout << adultTicketPrice[originStation][destinationStation] << "*" << adultTickets
                << setw(10) << (adultTicketPrice[originStation][destinationStation] / 2) << "*" << concessionTickets
                << setw(6) << total << setw(10) << "Business";
        }
    }
    else if (carClass == 1)
    {
        if (originStation < destinationStation)
        {
            total = adultTicketPrice[destinationStation][originStation] * adultTickets + (adultTicketPrice[destinationStation][originStation] / 2) * concessionTickets;
            cout << adultTicketPrice[destinationStation][originStation] << "*" << adultTickets
                << setw(10) << (adultTicketPrice[destinationStation][originStation] / 2) << "*" << concessionTickets
                << setw(6) << total << setw(10) << "Standard";
        }
        else
        {
            total = adultTicketPrice[originStation][destinationStation] * adultTickets + (adultTicketPrice[originStation][destinationStation] / 2) * concessionTickets;
            cout << adultTicketPrice[originStation][destinationStation] << "*" << adultTickets
                << setw(10) << (adultTicketPrice[originStation][destinationStation] / 2) << "*" << concessionTickets
                << setw(6) << total << setw(10) << "Standard";
        }
    }

}