// Deposit.h
// Deposit class definition. Represents a deposit transaction.
#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class Deposit
{
public:
   Deposit( int userAccountNumber, vector< Account > &atmAccounts );
   void execute(); // perform the deposit transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts
   double amount; // amount to deposit

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts ); 
   double promptForDepositAmount() const; // prompt user to enter a deposit amount in cents 
}; // end class Deposit

#endif // DEPOSIT_H