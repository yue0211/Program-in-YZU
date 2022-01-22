#include<iostream>
#include"Account.h"
using namespace std;

Account::Account(int theAccountNumber, int thePIN, double theAvailableBalance,
    double theTotalBalance)// constructor sets attributes
{
    accountNumber = theAccountNumber;
    pin = thePIN;
    availableBalance = theAvailableBalance;
    totalBalance = theTotalBalance;
}
bool Account::validatePIN(int userPIN) const // is user-specified PIN correct?
{
    if (userPIN == pin)
        return true;
    else
        return false;
}
double Account::getAvailableBalance() const // returns available balance
{
    return availableBalance;
}
double Account::getTotalBalance() const // returns total balance
{
    return totalBalance;
}
void Account::credit(double amount) // adds an amount to the Account balance
{
    totalBalance += amount;
}
void Account::debit(double amount) // subtracts an amount from the Account balance
{
    availableBalance -= amount;
    totalBalance -= amount;
}
int Account::getAccountNumber() const // returns account number
{
    return accountNumber;
}