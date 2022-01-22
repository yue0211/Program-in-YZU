#pragma once
#ifndef ATM_H
#define ATM_H
#include<cstring>
#include<iostream>
using namespace std;
class ATM
{
	public:
		ATM();
		void start();
		void Menu();
		void Viewmybalance();
		void Withdrawcash();
		void Depositfunds();
	private:
		string accountnumberFirst = "12345";
		string accountnumberSecond = "98765";
		string pinFirst = "54321";
		string pinSecond = "56789";
		double availableBalanceFirst=1000.0;
		double totalBalanceFirst =1200.0;
		double availableBalanceSecond = 200.0;
		double totalBalanceSecond =200.0;
		int track = 0;
		int times = 500;
};

#endif 
