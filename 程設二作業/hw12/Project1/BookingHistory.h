#ifndef  BOOKINGHISTORY_H
#define BOOKINGHISTORY_H
#include<iostream>
#include"ReservationRecord.h"
using namespace std;

class BookingHistory
{
	public:
		BookingHistory(vector<ReservationRecord>& reservations);
		void execute();
		void reduce(ReservationRecord &a);
		void ouput(ReservationRecord &a);
		int displayTransectionMenu();
	private:
		static int adultTicketPrice[13][13];
		static char place[13][13];
		vector<ReservationRecord>& reservation;
};

#endif 