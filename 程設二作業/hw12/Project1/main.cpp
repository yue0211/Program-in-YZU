#include<iostream>
#include<vector>
#include<fstream>
#include"Booking.h"
#include"BookingHistory.h"
#include"ReservationRecord.h"


using namespace std;

void performTransactions();
void loadReservations(vector<ReservationRecord>& reservations);
int displayMainMenu();


int main()
{

		cout << "Taiwan High Speed Rail Booking System\n\n";

		performTransactions();

}
void performTransactions()
{
	vector<ReservationRecord>reservations;

	enum MenuOption { booking = 1, booking_History, end_Program };

	bool userExited = false;

	int mainMenuSelection = displayMainMenu();
	Booking* bookingPtr = nullptr;
	BookingHistory* bookinghistoryptr = nullptr;

	while (!userExited)
	{

		switch (mainMenuSelection)
		{
			case booking:
				bookingPtr = new Booking(reservations);  
				bookingPtr->execute();  
				break;
			case booking_History:  //要查詢訂單資料 就先引入檔案
				loadReservations(reservations);
				bookinghistoryptr = new BookingHistory(reservations);
				bookinghistoryptr->execute();
				break;
			case end_Program:
				cout << "\nThank you. Goodbye.\n\n";
				userExited = true;
		}
		if (userExited)
			break;
		mainMenuSelection = displayMainMenu();
	}


}
int displayMainMenu()
{
	int choice = 0;
	cout << "Enter your choice\n1. Booking\n2. Booking History\n3. End Program\n?";
	cin >> choice;
	return choice;
}
void loadReservations(vector<ReservationRecord>& reservations)
{
	ReservationRecord temp;
	temp.read(reservations);
}


																																							