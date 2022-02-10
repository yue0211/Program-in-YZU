#include<iostream>
#include<iomanip>
#include"BalanceInquiry.h"
using namespace std;

BalanceInquiry::BalanceInquiry(int userAccountNumber, vector< Account >& atmAccounts)// constructor
	:accounts(atmAccounts),accountNumber(userAccountNumber)
{
}
void BalanceInquiry::execute() // perform the balance inquiry transaction
{
	cout << "\nBalance Information:\n - Available balance: $";
	cout << fixed << setprecision(2) << getAccount(accountNumber, accounts)->getAvailableBalance();
	cout << "\n - Total balance:     $";
	cout << fixed << setprecision(2) << getAccount(accountNumber, accounts)->getTotalBalance()<<endl;
}
Account* BalanceInquiry::getAccount(int accountNumber, vector< Account >& accounts)
{
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accountNumber == accounts[i].getAccountNumber())
			return &accounts[i];
	}
	return NULL;
}