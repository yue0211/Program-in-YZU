#include<iostream>
#include"Deposit.h"
using namespace std;

Deposit::Deposit(int userAccountNumber, vector< Account >& atmAccounts)
	:accountNumber(userAccountNumber), accounts(atmAccounts)
{
}
void Deposit::execute() // perform the deposit transaction
{
	cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
	cin >> amount;
	if (amount == 0)
		return;
	amount /= 100;
	getAccount(accountNumber, accounts)->credit(amount);
	cout << "\nPlease insert a deposit envelope containing $10.00 in the deposit slot.\n"
		<< "Your envelope has been received.\nNOTE: The money deposited will not be available until we"
		<< "\nverify the amount of any enclosed cash, and any enclosed checks clear.\n\n";
}
Account* Deposit::getAccount(int accountNumber, vector< Account >& accounts)
{
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accountNumber == accounts[i].getAccountNumber())
			return &accounts[i];
	}
	return NULL;
}

