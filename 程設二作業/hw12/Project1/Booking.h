#ifndef BOOKING_H
#define BOOKING_H
#include<iostream>
#include<vector>
#include"ReservationRecord.h"
using namespace std;
class Booking
{
		public:
			Booking(vector<ReservationRecord>& reservations);
			void execute();
			void southTimetable(vector<ReservationRecord::Train>&a);
			void northTimetable(vector<ReservationRecord::Train>&a);
		private:
			static int adultTicketPrice[13][13];
			static char departureTimes[37][8];
			static char place[13][13];
			vector<ReservationRecord>& reservation;
};


#endif