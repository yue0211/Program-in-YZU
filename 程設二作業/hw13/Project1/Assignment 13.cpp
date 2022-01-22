#include <iostream>
#include "ReservationHistory.h"
#include "MakingReservation.h"

string departureTimes[ 37 ] = { "",
   "06:00", "06:30", "07:00", "07:30", "08:00", "08:30", "09:00", "09:30",
   "10:00", "10:30", "11:00", "11:30", "12:00", "12:30", "13:00", "13:30",
   "14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30",
   "18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30",
   "22:00", "22:30", "23:00", "23:30" };


// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

int main()
{
   cout << "Taiwan High Speed Rail Booking System\n";

   SouthboundTimetable southboundTimetable;
   NorthboundTimetable northboundTimetable;
   ReservationDatabase reservationDatabase;
   MakingReservation makingReservation( reservationDatabase, southboundTimetable, northboundTimetable );
   ReservationHistory reservationHistory( reservationDatabase, southboundTimetable, northboundTimetable );

   int choice;
   while ( true )
   {
      cout << "\nEnter Your Choice\n"
           << "1. Booking\n"
           << "2. Booking History\n"
           << "3. End Program";

      do cout << "\n? ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch ( choice )
      {
      case 1:
         makingReservation.execute();
         break;
      case 2:
         reservationHistory.execute();
         break;
      case 3:
         cout << "Thank you. Goodbye.\n\n";
         system( "pause" );
         return 0;
      default:
         cerr << "Incorrect Choice!\n";
         break;
      }
   }

   system( "pause" );
}

int inputAnInteger( int begin, int end )
{
   char string[ 80 ];
   cin.getline( string, 80, '\n' );

   /*if( strlen( string ) == 0 )
      exit( 0 );*/

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );

   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}