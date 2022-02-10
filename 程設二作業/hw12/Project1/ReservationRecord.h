#ifndef RESERVATIONRECORD_H
#define RESERVATIONRECORD_H
#include<vector>
#include<iostream>
using namespace std;
class ReservationRecord
{
    public:
        struct Reservation
        {
            char idNumber[12] = {}; // the id number of the contact person  取票人的身分證字號
            char reservationNumber[12] = {}; // used to identify a reservation  訂位代號
            char trainNumber[8] = {}; // used to identify a train  車次號碼         
            char phone[12] = {}; // the (local or mobile) phone number of the contact person  取票人的聯絡電話
            char date[12] = {}; // outbound date  搭乘日期
            int originStation = 0; // the origin station code  起程站代碼
            int destinationStation=0; // the destination station code  到達站代碼
            int carClass=0; // the car class code; 1:standard car, 2:business car  車廂種類; 1:標準車廂, 2:商務車廂
            int adultTickets=0; // the number of adult tickets  全票張數
            int concessionTickets=0; // the number of concession tickets  優待票張數
        };
        struct Train
        {
            char trainNumber[8] = {}; // used to identify a train  車次號碼
            char departureTimes[13][8] = {}; // the departure time of a train for each station  火車在各站的離站時間
                                                                    // departureTimes[0] is not used   departureTimes[0]未使用
        };                                      
        void makeReservation(Reservation a, Train b);
        char* getIdnumber();
        char* getReservationNumber();
        char* getdate();
        int getOriginstation();
        int getDestination();
        int getCarclass();
        int getadult();
        int getconcession();
        void setadult(int number);
        void setconcession(int number);
        char* getTrainNumber();
        char* getStart(int originstation);
        char* getArrival(int destination);
        void save();
        void read(vector<ReservationRecord>& reservations);
    private:
        Reservation reservationlist;
        Train Trainlist;
};

#endif