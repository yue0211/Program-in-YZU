#include<iostream>
#include<iomanip>
#include"Withdrawal.h"
using namespace std;

Withdrawal::Withdrawal(int userAccountNumber, vector< Account >& atmAccounts, int& atmRemainingBills)
    :accounts(atmAccounts), accountNumber(userAccountNumber), remainingBills(atmRemainingBills)
{
}
void Withdrawal::execute() // perform the withdrawal transaction
{
	cout << "Withdrawal options:\n1 - $20\n2 - $40\n"
		<< "3 - $60\n4 - $100\n5 - $200\n6 - Cancel transaction\n\n";
	cout << "Choose a withdrawal option (1-6): ";
	int option = 0;
	cin >> option;
	for (int i = 1; i <= 5; i++)
	{
		if (option == i)
		{
			if (i == 4)
				amount = 100;
			else if (i == 5)
				amount = 200;
			else
				amount = 20 * i;
			if (i == 4 && remainingBills >= 5)
				remainingBills -= 5;
			else  if (i == 4 && remainingBills < 5)
			{
				cout << "ATM doesn't have enough money.\n";
				execute();
			}
			if (i == 5 && remainingBills >= 10)
				remainingBills -= 10;
			else if (i == 5 && remainingBills < 10)
			{
				cout << "ATM doesn't have enough money.\n";
				execute();
			}
			if (remainingBills >= i && i != 4 && i != 5)
				remainingBills -= i;
			else if (i != 4 && i != 5 && remainingBills < i)
			{
				cout << "ATM doesn't have enough money.\n";
				execute();
			}
			if ((getAccount(accountNumber, accounts)->getAvailableBalance() - amount) < 0)
			{
				cout << "need to choice less money beacause account doesn't have enough money\n\n";
				execute();
			}
			else
			  getAccount(accountNumber, accounts)->debit(amount);
		}
	}
	if (option == 6)
	{
		cout << endl;
		return;
	}
	cout << "\nPlease take your cash from the cash dispenser.\n\n";
}

Account* Withdrawal::getAccount(int accountNumber, vector< Account >& accounts)
{
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accountNumber == accounts[i].getAccountNumber())
			return &accounts[i];
	}
	return NULL;
}