#include"ATM.h"
#include<iostream>
#include<iomanip>
using namespace std;

ATM::ATM()
{
}
void ATM::start()
{
	cout << "Welcome!\n\n";
	string numberAc,numberPin;
	cout << "Please Enter your account number: ";
	cin >> numberAc;
	if (numberAc == accountnumberFirst)
		track = 1;
	if (numberAc == accountnumberSecond)
		track = 0;
	while((numberAc!= accountnumberFirst) || (numberAc != accountnumberSecond))
	{
		if (numberAc == accountnumberFirst || numberAc == accountnumberSecond)
			break;
		cout << "\nPlease Enter your account number again: ";
		cin >> numberAc;
		if (numberAc == accountnumberFirst)
			track = 1;
		if (numberAc == accountnumberSecond)
			track = 0;
	}
	cout << "\nEnter your Pin: ";
	cin >> numberPin;
	while (numberAc == accountnumberFirst && numberPin != pinFirst || numberAc == accountnumberSecond && numberPin != pinSecond)
	{
		if (numberAc == accountnumberFirst && numberPin == pinFirst || numberAc == accountnumberSecond && numberPin == pinSecond)
			break;
		cout << "\nEnter your Pin again: ";
		cin >> numberPin;
	}
	cout << endl;
	Menu();
}
void ATM::Menu()
{
	int choice = 0;
	cout << "Main menu:\n1 - View my balance\n2 - Withdraw cash"
		<< "\n3 - Deposit funds\n4 - Exit\n";
	cout << "\nEnter a choice: ";
	cin >> choice;
	while (choice>4 || choice==0)
	{
		cout << "\nEnter a choice again: ";
		cin >> choice;
	}
	if (choice == 1)
	{
		cout << endl;
		Viewmybalance();
	}
	else if (choice == 2)
	{
		cout << endl;
		Withdrawcash();
	}
	else if (choice == 3)
	{
		cout << endl;
		Depositfunds();
	}
	else if (choice == 4)
	{
		cout << "\nExiting the system.\nThank you! Goodbye!\n\n";
		start();
	}
}
void ATM::Viewmybalance()
{
	cout << "Balance Information:\n - Available balance: $";
	if (track == 1)
		cout << fixed<<setprecision(2)<<availableBalanceFirst;
	else if(track == 0)
		cout << fixed << setprecision(2)<<availableBalanceSecond;
	cout << "\n - Total balance:     $";
	if (track == 1)
		cout << fixed << setprecision(2)<<totalBalanceFirst;
	else if (track == 0)
		cout << fixed << setprecision(2)<< totalBalanceSecond;
	cout << endl<<endl;
	Menu();
}
void ATM::Withdrawcash()
{
	int option = 0;
	double money[6] = { 0,20,40,60,100,200 };
	cout << "Withdrawal options:\n1 - $20\n2 - $40\n"
		<< "3 - $60\n4 - $100\n5 - $200\n6 - Cancel transaction\n\n";
		
	cout << "Choose a withdrawal option (1-6): ";
	cin >> option;
	while (option == 0 || option > 6)
	{
		cout << "\nChoose a withdrawal option (1-6)again: ";
		cin >> option;
	}
	for (int i=1;i<=5;i++)
	{   
		if (option == i && track == 1 )
		{
			if (i == 4 && times >= 5)
				times -= 5;
			else  if(i == 4 && times<5)
			{
				cout << "ATM doesn't have enough money.\n";
				Withdrawcash();
			}
			if (i == 5 && times >= 10)
				times -= 10;
			else if(i == 5 && times<10)
			{
				cout << "ATM doesn't have enough money.\n";
				Withdrawcash();
			}
			if(times>=i&&i!=4 &&i!=5)
				times -= i;
			else if(i != 4 && i != 5&&times<i)
			{
				cout << "ATM doesn't have enough money.\n";
				Withdrawcash();
			}
			if ((availableBalanceFirst - money[i]) < 0)
			{
				cout << "need to choice less money beacause account doesn't have enough money\n\n";
				Withdrawcash();
			}
			availableBalanceFirst -= money[i];
			totalBalanceFirst-= money[i];
		}
		else if (option == i && track == 0 )
		{
			if (i == 4 && times >= 5)
				times -= 5;
			else if (i == 4 && times < 5)
			{
				cout << "ATM doesn't have enough money.\n";
				Withdrawcash();
			}
			if (i == 5 && times >= 10)
				times -= 10;
			else if (i == 5 && times < 10)
			{
				cout << "ATM doesn't have enough money.\n";
				Withdrawcash();
			}
			if (times >= i && i != 4 && i != 5)
				times -= i;
			else   if (i != 4 && i != 5 && times < i)
			{
				cout << "ATM doesn't have enough money.\n";
				Withdrawcash();
			}
			if((availableBalanceSecond-money[i])<0)
			{
				cout << "need to choice less money beacause account doesn't have enough money\n\n";
				Withdrawcash();
			}
			availableBalanceSecond-= money[i];
			totalBalanceSecond -= money[i];
		}
		
	}
	if (option == 6)
	{
		cout << endl;
		Menu();
	}
	cout << "\nPlease take your cash from the cash dispenser.\n\n";
	Menu();
}
void ATM::Depositfunds()
{
	double amount;
	cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
	cin >> amount;
	if(amount==0)
		Menu();
	amount /= 100;
	if (track == 1)
		totalBalanceFirst += amount;
	else
		totalBalanceSecond += amount;
	cout << "\nPlease insert a deposit envelope containing $10.00 in the deposit slot.\n"
		<< "Your envelope has been received.\nNOTE: The money deposited will not be available until we"
		<< "\nverify the amount of any enclosed cash, and any enclosed checks clear.\n\n";
	Menu();
}