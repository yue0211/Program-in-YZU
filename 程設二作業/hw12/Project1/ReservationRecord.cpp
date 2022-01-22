#include<iostream>
#include<fstream>
#include<cstring>
#include"ReservationRecord.h"
using namespace std;

void ReservationRecord::makeReservation(Reservation a,Train b)
{
	reservationlist.adultTickets = a.adultTickets;
	reservationlist.carClass = a.carClass;
	reservationlist.concessionTickets = a.concessionTickets;
	strcpy_s(reservationlist.date, a.date);
	reservationlist.destinationStation = a.destinationStation;
	strcpy_s(reservationlist.idNumber, a.idNumber);
	reservationlist.originStation = a.originStation;
	strcpy_s(reservationlist.phone, a.phone);
	strcpy_s(reservationlist.reservationNumber, a.reservationNumber);
	strcpy_s(reservationlist.trainNumber, a.trainNumber);
	Trainlist = b;
}
char* ReservationRecord::getIdnumber()
{
	return reservationlist.idNumber;
}
char* ReservationRecord::getReservationNumber()
{
	return reservationlist.reservationNumber;
}
char* ReservationRecord::getdate()
{
	return reservationlist.date;
}
int ReservationRecord::getOriginstation()
{
	return reservationlist.originStation;
}
int ReservationRecord::getDestination()
{
	return reservationlist.destinationStation;
}
int ReservationRecord::getCarclass()
{
	return reservationlist.carClass;
}
int ReservationRecord::getadult()
{
	return reservationlist.adultTickets;
}
int ReservationRecord::getconcession()
{
	return reservationlist.concessionTickets;
}
void  ReservationRecord::setadult(int number)
{
	reservationlist.adultTickets -= number;
}
void  ReservationRecord::setconcession(int number)
{
	reservationlist.concessionTickets -= number;
}
char* ReservationRecord::getTrainNumber()
{
	return Trainlist.trainNumber;
}
char* ReservationRecord::getStart(int originstation)
{
	return Trainlist.departureTimes[originstation];
}
char* ReservationRecord::getArrival(int destination)
{
	return Trainlist.departureTimes[destination];
}
void ReservationRecord::save()
{
	ofstream out("Reservation details.dat", ios::out | ios::binary);
	out.write(reinterpret_cast<const char*>(&reservationlist.idNumber), sizeof(reservationlist.idNumber));
	out.write(reinterpret_cast<const char*>(&reservationlist.reservationNumber), sizeof(reservationlist.reservationNumber));
	out.write(reinterpret_cast<const char*>(&reservationlist.trainNumber), sizeof(reservationlist.trainNumber));
	out.write(reinterpret_cast<const char*>(&reservationlist.phone), sizeof(reservationlist.phone));
	out.write(reinterpret_cast<const char*>(&reservationlist.date), sizeof(reservationlist.date));
	out.write(reinterpret_cast<const char*>(&reservationlist.originStation), sizeof(reservationlist.originStation));
	out.write(reinterpret_cast<const char*>(&reservationlist.destinationStation), sizeof(reservationlist.destinationStation));
	out.write(reinterpret_cast<const char*>(&reservationlist.carClass), sizeof(reservationlist.carClass));
	out.write(reinterpret_cast<const char*>(&reservationlist.adultTickets), sizeof(reservationlist.adultTickets));
	out.write(reinterpret_cast<const char*>(&reservationlist.concessionTickets), sizeof(reservationlist.concessionTickets));
	out.write(reinterpret_cast<const char*>(&Trainlist.departureTimes[reservationlist.originStation]), sizeof(Trainlist.departureTimes[reservationlist.originStation]));
	out.write(reinterpret_cast<const char*>(&Trainlist.departureTimes[reservationlist.destinationStation]), sizeof(Trainlist.departureTimes[reservationlist.destinationStation]));
	out.write(reinterpret_cast<const char*>(&Trainlist.trainNumber), sizeof(Trainlist.trainNumber));
	out.close();
}
void ReservationRecord::read(vector<ReservationRecord>& reservations)
{
	ifstream inFile("Reservation details.dat", ios::in | ios::binary);

	if (!inFile)  //如果 Reservations.txt.txt不存在則建檔  
	{
		ofstream outFile("Reservation details.dat", ios::out | ios::binary);
		outFile.close();
	}
	else
	{
		inFile.seekg(0, ios::end); 	//seekg的第一個參數是偏移量 ,第二個參數是起始地址 
		int end = inFile.tellg();

		int times = end / sizeof(ReservationRecord::Reservation);   //計算讀取所需花的時間 

		inFile.seekg(0, ios::beg);
		for (int i(1); i <= times; i++)
		{
			inFile.read(reinterpret_cast<char*>(&reservationlist.idNumber), sizeof(reservationlist.idNumber));
			inFile.read(reinterpret_cast<char*>(&reservationlist.reservationNumber), sizeof(reservationlist.reservationNumber));
			inFile.read(reinterpret_cast<char*>(&reservationlist.trainNumber), sizeof(reservationlist.trainNumber));
			inFile.read(reinterpret_cast<char*>(&reservationlist.phone), sizeof(reservationlist.phone));
			inFile.read(reinterpret_cast<char*>(&reservationlist.date), sizeof(reservationlist.date));
			inFile.read(reinterpret_cast<char*>(&reservationlist.originStation), sizeof(reservationlist.originStation));
			inFile.read(reinterpret_cast< char*>(&reservationlist.destinationStation), sizeof(reservationlist.destinationStation));
			inFile.read(reinterpret_cast<char*>(&reservationlist.carClass), sizeof(reservationlist.carClass));
			inFile.read(reinterpret_cast<char*>(&reservationlist.adultTickets), sizeof(reservationlist.adultTickets));
			inFile.read(reinterpret_cast< char*>(&reservationlist.concessionTickets), sizeof(reservationlist.concessionTickets));
			inFile.read(reinterpret_cast<char*>(&Trainlist.departureTimes[reservationlist.originStation]), sizeof(Trainlist.departureTimes[reservationlist.originStation]));
			inFile.read(reinterpret_cast<char*>(&Trainlist.departureTimes[reservationlist.destinationStation]), sizeof(Trainlist.departureTimes[reservationlist.destinationStation]));
			inFile.read(reinterpret_cast<char*>(&Trainlist.trainNumber), sizeof(Trainlist.trainNumber));
			reservations.push_back(*this);
		}
		inFile.close();
	}
}