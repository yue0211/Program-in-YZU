#include<iostream>
#include<fstream>
#include<iomanip>
#include"BookingHistory.h"
using namespace std;
int BookingHistory::adultTicketPrice[13][13] = {
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
char BookingHistory::place[13][13] = { "",
		"Nangang","Taipei","Banqiao","Taoyuan","Hsinchu",
		"Miaoli","Taichung","Changhua","Yunlin","Chiayi","Tainan","Zuoying"
};

BookingHistory::BookingHistory(vector<ReservationRecord>& reservations)
	:reservation(reservations)
{
}
void BookingHistory::execute()
{

	char IDnumber[8] = {};
	char Reservationnumber[12] = {};
	cout << "\nEnter ID Number:  ";
	cin >> IDnumber;
	cout << "\nEnter Reservation Number: ";
	cin >> Reservationnumber;


	for (int i = 0; i< reservation.size(); i++)
	{
		if (!strcmp(reservation[i].getIdnumber(), IDnumber))
		{
			if (!strcmp(reservation[i].getReservationNumber(), Reservationnumber))
			{
				cout << "\nReservation Details\n\n";
				ouput(reservation[i]);
				break;
			}
		}
	}
	return;
}
void BookingHistory::ouput(ReservationRecord &a)
{
	
	cout << "      Date  Train No.     From        To  Departure  Arrival   Adult  Concession  Fare     Class\n"
		<< setw(10) << a.getdate() << setw(11) << a.getTrainNumber() << setw(9)
		<< place[a.getOriginstation()] << setw(10) << place[a.getDestination()]
		<< setw(11) << a.getStart(a.getOriginstation()) << setw(9) << a.getArrival(a.getDestination()) << setw(6);

	int total = 0;
	if (a.getCarclass() == 2)
	{
		if (a.getOriginstation() > a.getDestination())
		{
			total = adultTicketPrice[a.getDestination()][a.getOriginstation()] * a.getadult() + (adultTicketPrice[a.getDestination()][a.getOriginstation()] / 2) * a.getconcession();
			cout << adultTicketPrice[a.getDestination()][a.getOriginstation()] << "*" << a.getadult()
				<< setw(10) << (adultTicketPrice[a.getDestination()][a.getOriginstation()] / 2) << "*" << a.getconcession()
				<< setw(6) << total << setw(10) << "Business";
		}
		else
		{
			total = adultTicketPrice[a.getOriginstation()][a.getDestination()] * a.getadult() + (adultTicketPrice[a.getOriginstation()][a.getDestination()] / 2) * a.getconcession();
			cout << adultTicketPrice[a.getOriginstation()][a.getDestination()] << "*" << a.getadult()
				<< setw(10) << (adultTicketPrice[a.getOriginstation()][a.getDestination()] / 2) << "*" << a.getconcession()
				<< setw(6) << total << setw(10) << "Business";
		}
	}
	else if (a.getCarclass() == 1)
	{
		if (a.getOriginstation() < a.getDestination())
		{
			total = adultTicketPrice[a.getDestination()][a.getOriginstation()] * a.getadult() + (adultTicketPrice[a.getDestination()][a.getOriginstation()] / 2) * a.getconcession();
			cout << adultTicketPrice[a.getDestination()][a.getOriginstation()] << "*" << a.getadult()
				<< setw(10) << (adultTicketPrice[a.getDestination()][a.getOriginstation()] / 2) << "*" << a.getconcession()
				<< setw(6) << total << setw(10) << "Standard";
		}
		else
		{
			total = adultTicketPrice[a.getOriginstation()][a.getDestination()] * a.getadult() + (adultTicketPrice[a.getOriginstation()][a.getDestination()] / 2) * a.getconcession();
			cout << adultTicketPrice[a.getOriginstation()][a.getDestination()] << "*" << a.getadult()
				<< setw(10) << (adultTicketPrice[a.getOriginstation()][a.getDestination()] / 2) << "*" << a.getconcession()
				<< setw(6) << total << setw(10) << "Standard";
		}
	}
	enum MenuOption { Cancellation = 1, Reduce, End};
	int transectionmenu = displayTransectionMenu();

		switch (transectionmenu)
		{
			case Cancellation:
				cout << "\nReservation Cancelled.\n\n";
				break;
			case Reduce:
				reduce(a);
				break;
			case End:
				cout << endl;
				break;
		}
		return;
		
		
}
void BookingHistory::reduce(ReservationRecord &a)
{
	int adultnumber = 0,concessnumber=0;
	cout << "\nHow many adult tickets to cancel¡H";
	cin >> adultnumber;
	cout << "How many concession tickets to cancel¡H";
	cin >> concessnumber;
	a.setadult(adultnumber);
	a.setconcession(concessnumber);
	
	cout << "\n      Date  Train No.     From        To  Departure  Arrival   Adult  Concession  Fare     Class\n"
		<< setw(10) << a.getdate() << setw(11) << a.getTrainNumber() << setw(9)
		<< place[a.getOriginstation()] << setw(10) << place[a.getDestination()]
		<< setw(11) << a.getStart(a.getOriginstation()) << setw(9) << a.getArrival(a.getDestination()) << setw(6);

	int total = 0;
	if (a.getCarclass() == 2)
	{
		if (a.getOriginstation() > a.getDestination())
		{
			total = adultTicketPrice[a.getDestination()][a.getOriginstation()] * a.getadult() + (adultTicketPrice[a.getDestination()][a.getOriginstation()] / 2) * a.getconcession();
			cout << adultTicketPrice[a.getDestination()][a.getOriginstation()] << "*" << a.getadult()
				<< setw(10) << (adultTicketPrice[a.getDestination()][a.getOriginstation()] / 2) << "*" << a.getconcession()
				<< setw(6) << total << setw(10) << "Business";
		}
		else
		{
			total = adultTicketPrice[a.getOriginstation()][a.getDestination()] * a.getadult() + (adultTicketPrice[a.getOriginstation()][a.getDestination()] / 2) * a.getconcession();
			cout << adultTicketPrice[a.getOriginstation()][a.getDestination()] << "*" << a.getadult()
				<< setw(10) << (adultTicketPrice[a.getOriginstation()][a.getDestination()] / 2) << "*" << a.getconcession()
				<< setw(6) << total << setw(10) << "Business";
		}
	}
	else if (a.getCarclass() == 1)
	{
		if (a.getOriginstation() < a.getDestination())
		{
			total = adultTicketPrice[a.getDestination()][a.getOriginstation()] * a.getadult() + (adultTicketPrice[a.getDestination()][a.getOriginstation()] / 2) * a.getconcession();
			cout << adultTicketPrice[a.getDestination()][a.getOriginstation()] << "*" << a.getadult()
				<< setw(10) << (adultTicketPrice[a.getDestination()][a.getOriginstation()] / 2) << "*" << a.getconcession()
				<< setw(6) << total << setw(10) << "Standard";
		}
		else
		{
			total = adultTicketPrice[a.getOriginstation()][a.getDestination()] * a.getadult() + (adultTicketPrice[a.getOriginstation()][a.getDestination()] / 2) * a.getconcession();
			cout << adultTicketPrice[a.getOriginstation()][a.getDestination()] << "*" << a.getadult()
				<< setw(10) << (adultTicketPrice[a.getOriginstation()][a.getDestination()] / 2) << "*" << a.getconcession()
				<< setw(6) << total << setw(10) << "Standard";
		}
	}
	cout << "\n\nYou have successfully reduced the number of tickets!\n\n";

	for (int i = 0; i < reservation.size(); i++)
	{
		reservation[i].save();
	}

}

int BookingHistory::displayTransectionMenu()
{
	int choice = 0;
	cout << "\n\nEnter your choice\n1. Cancellation\n2. Reduce\n3. End\n?";
	cin >> choice;
	return choice;
}