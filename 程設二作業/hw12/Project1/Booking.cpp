#include"Booking.h"
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
int Booking::adultTicketPrice[13][13] = {
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

char Booking::departureTimes[37][8] = { "",
   "06:00", "06:30", "07:00", "07:30", "08:00", "08:30", "09:00", "09:30",
   "10:00", "10:30", "11:00", "11:30", "12:00", "12:30", "13:00", "13:30",
   "14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30",
   "18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30",
   "22:00", "22:30", "23:00", "23:30" };
char Booking::place[13][13] = { "",
		"Nangang","Taipei","Banqiao","Taoyuan","Hsinchu",
		"Miaoli","Taichung","Changhua","Yunlin","Chiayi","Tainan","Zuoying"
};

Booking::Booking(vector<ReservationRecord>& reservations)
	:reservation(reservations)
{
}

void Booking::execute()
{
	char reservationNumber[12] = {}, idNumber[12], phone[12], date[12], trainNumber[8], departureTimesTrain[13][8];
	int originStation = 0, destinationStation = 0, carClass = 0, adultTickets = 0, concessionTickets = 0, choiceTime = 0;

	cout << "\nOrigin Station\n1. Nangang\n2. Taipei\n3. Banqiao\n4. Taoyuan\n5. Hsinchu\n"
		<< "6. Miaoli\n7. Taichung\n8. Changhua\n9. Yunlin\n10. Chiayi\n11. Tainan\n12. Zuoying\n?";
	cin >> originStation;

	cout << "\nDestination Station\n1. Nangang\n2. Taipei\n3. Banqiao\n4. Taoyuan\n5. Hsinchu\n"
		<< "6. Miaoli\n7. Taichung\n8. Changhua\n9. Yunlin\n10. Chiayi\n11. Tainan\n12. Zuoying\n?";
	cin >> destinationStation;

	cout << "\nCar Class\n1. Standard Car\n2. Business Car\n?";
	cin >> carClass;

	cout << "\nDeparture Date: ";
	cin >> date;

	cout << "\nDeparture Time\n";

	for (int i = 1; i < 35; i++)
	{
		cout << i << ". " << departureTimes[i] << endl;
	}
	cout << "?";
	cin >> choiceTime;

	cout << "\nHow many adult tickets? ";
	cin >> adultTickets;
	cout << "\nHow many concession tickets? ";
	cin >> concessionTickets;

	vector<ReservationRecord::Train> a;
	int temp=0, temp2 = 0, count = 0;
	if (destinationStation > originStation)  //向南
	{
		southTimetable(a);   
		temp = originStation;
		temp2 = destinationStation;
	}
	else if (destinationStation < originStation)  //向北
	{
		northTimetable(a);
		temp = destinationStation;
		temp2 = originStation;
	}
	cout << "\nTrain No.  Departure  Arrival\n";
	for (int k = 0; k < a.size() && count != 10;k++ )
	{
		if ((a[k].departureTimes[temp][0] * 10 + a[k].departureTimes[temp][1]) * 60 + (a[k].departureTimes[temp][3] * 10 + a[k].departureTimes[temp][4]) >=//modify
			(departureTimes[choiceTime][0] * 10 + departureTimes[choiceTime][1]) * 60 + (departureTimes[choiceTime][3] * 10 + departureTimes[choiceTime][4]) && a[k].departureTimes[temp2][0] >= 48)//modify
		{
			count += 1;
			cout << setw(9) << a[k].trainNumber << setw(11) << a[k].departureTimes[temp] << setw(9) << a[k].departureTimes[temp2] << endl;
		}
	}
	
	cout << "\nEnter Train Number: ";
	cin >> trainNumber;
	cout << "\nTrip Details\n\n      Date  Train No.     From        To  Departure  Arrival   Adult  Concession  Fare     Class\n"
		<< setw(10) << date << setw(11) << trainNumber << setw(9) << place[originStation] << setw(10) << place[destinationStation]
		<< setw(11);

	int k = 0;
	for (; k < a.size(); k++)
	{
		if (!strcmp(trainNumber, a[k].trainNumber))
		{
			cout << a[k].departureTimes[temp] << setw(9) << a[k].departureTimes[temp2] << setw(6);
			break;
		}
	}
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
	srand(time(0));
	cout << "\n\nEnter Contact Person Information\n\nID Number: ";
	cin >> idNumber;
	cout << "\nPhone: ";
	cin >> phone;
	cout << "\nReservation Number: ";
	for (int i = 0; i < 8; i++)
		reservationNumber[i] = 48 + rand() % 10;
	cout << reservationNumber;

	cout << "\n\nReservation Completed!\n\n\n";
	ReservationRecord::Reservation m;
	m.adultTickets = adultTickets;
	m.carClass=carClass;
	m.concessionTickets = concessionTickets;
	strcpy_s(m.date, date);
	m.destinationStation = destinationStation;
	strcpy_s(m.idNumber, idNumber);
	m.originStation = originStation;
	strcpy_s(m.phone, phone);
	strcpy_s(m.reservationNumber, reservationNumber);
	strcpy_s(m.trainNumber, trainNumber);
	ReservationRecord mm;
	mm.makeReservation(m, a[k]);
	reservation.push_back(mm);
	ofstream out("Reservation details.dat", ios::app|ios::binary);

	out.write(reinterpret_cast<const char*>(&m.idNumber), sizeof(m.idNumber));
	out.write(reinterpret_cast<const char*>(&m.reservationNumber), sizeof(m.reservationNumber));
	out.write(reinterpret_cast<const char*>(&m.trainNumber), sizeof(m.trainNumber));
	out.write(reinterpret_cast<const char*>(&m.phone), sizeof(m.phone));
	out.write(reinterpret_cast<const char*>(&m.date), sizeof(m.date));
	out.write(reinterpret_cast<const char*>(&m.originStation), sizeof(m.originStation));
	out.write(reinterpret_cast<const char*>(&m.destinationStation), sizeof(m.destinationStation));
	out.write(reinterpret_cast<const char*>(&m.carClass), sizeof(m.carClass));
	out.write(reinterpret_cast<const char*>(&m.adultTickets), sizeof(m.adultTickets));
	out.write(reinterpret_cast<const char*>(&m.concessionTickets), sizeof(m.concessionTickets));
	out.write(reinterpret_cast<const char*>(&a[k].departureTimes[temp]), sizeof(a[k].departureTimes[temp]));
	out.write(reinterpret_cast<const char*>(&a[k].departureTimes[temp2]), sizeof(a[k].departureTimes[temp2]));
	out.write(reinterpret_cast<const char*>(&a[k].trainNumber), sizeof(a[k].trainNumber));
	out.close();
}
void Booking::southTimetable(vector<ReservationRecord::Train> &a)
{
	ifstream inFile("Southbound timetable.dat", ios::binary);

	ReservationRecord::Train replace;

	while (inFile.read(reinterpret_cast<char*>(&replace.trainNumber), sizeof(replace.trainNumber)))
	{
		for (int i = 0; i < 13; i++)
			inFile.read(reinterpret_cast<char*>(&replace.departureTimes[i]), sizeof(replace.departureTimes[i]));
		a.push_back(replace);
	}
	
}
void Booking::northTimetable(vector<ReservationRecord::Train> &a)
{
	ifstream inFile("Northbound timetable.dat", ios::binary);

	ReservationRecord::Train replace;

	while (inFile.read(reinterpret_cast<char*>(&replace.trainNumber), sizeof(replace.trainNumber)))
	{
		for (int i = 0; i < 13; i++)
			inFile.read(reinterpret_cast<char*>(&replace.departureTimes[i]), sizeof(replace.departureTimes[i]));
		a.push_back(replace);
	}
}