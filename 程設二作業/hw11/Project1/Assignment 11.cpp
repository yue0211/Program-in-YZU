// Driver program for the ATM system
#include <iostream>
#include <iomanip>
using namespace std;
#include "BalanceInquiry.h" // BalanceInquiry class definition
#include "Withdrawal.h" // Withdrawal class definition
#include "Deposit.h" // Deposit class definition

// attempts to authenticate user
void authenticateUser( bool &userAuthenticated, int &currentAccountNumber, vector< Account > &accounts );

// retrieve Account object containing specified account number
Account * getAccount( int accountNumber, vector< Account > &accounts );

// display the main menu and perform transactions
void performTransactions( int &currentAccountNumber, vector< Account > &accounts );

int displayMainMenu(); // display the main menu and return an input selection

// start ATM 
int main()
{
   bool userAuthenticated = false; // whether user is authenticated
   int currentAccountNumber = 0; // current user's account number

   // create two Account objects for testing
   Account account1( 12345, 54321, 1000.0, 1200.0 );
   Account account2( 98765, 56789, 200.0, 200.0 );

   vector< Account > accounts; // vector of the bank's Accounts
   // add the Account objects to the vector accounts
   accounts.push_back( account1 ); // add account1 to end of vector
   accounts.push_back( account2 ); // add account2 to end of vector

   // welcome and authenticate user; perform transactions
   while ( true )
   {
      // loop while user is not yet authenticated
      while ( !userAuthenticated ) 
      {
         cout << "\nWelcome!" << endl;
         authenticateUser( userAuthenticated, currentAccountNumber, accounts ); // authenticate user
      } // end while
      
      // display the main menu and perform transactions
      performTransactions( currentAccountNumber, accounts );

      userAuthenticated = false; // reset before next ATM session
      currentAccountNumber = 0; // reset before next ATM session 
      cout << "\nThank you! Goodbye!" << endl;
   } // end while   
} // end function main

// attempt to authenticate user against database
void authenticateUser( bool &userAuthenticated, int &currentAccountNumber,
                       vector< Account > &accounts )
{
   cout << "\nPlease enter your account number: ";
   int accountNumber;
   cin >> accountNumber; // input account number
   cout << "\nEnter your PIN: ";
   int pin;
   cin >> pin; // input PIN

   Account * const userAccountPtr = getAccount( accountNumber, accounts );

   // if account exists, return result of Account function validatePIN
   if ( userAccountPtr != NULL )
      userAuthenticated = userAccountPtr->validatePIN( pin );
   else
      userAuthenticated = false; // account number not found, so return false

   // check whether authentication succeeded
   if ( userAuthenticated )
      currentAccountNumber = accountNumber; // save user's account #
   else
      cout << "Invalid account number or PIN. Please try again.\n";
} // end function authenticateUser

// retrieve Account object containing specified account number
Account * getAccount( int accountNumber, vector< Account > &accounts )
{
   // loop through accounts searching for matching account number
   for ( size_t i = 0; i < accounts.size(); i++ )
   {
      // return current account if match found
      if ( accounts[ i ].getAccountNumber() == accountNumber )
         return &accounts[ i ];
   } // end for

   return NULL; // if no matching account was found, return NULL
} // end function getAccount

// display the main menu and perform transactions
void performTransactions( int &currentAccountNumber, vector< Account > &accounts ) 
{
   // enumeration constants represent main menu options
   enum MenuOption { BALANCE_INQUIRY = 1, WITHDRAWAL, DEPOSIT, EXIT };
   // local pointer to store transaction currently being processed
   BalanceInquiry *balanceInquiryPtr;
   Withdrawal *withdrawalPtr;
   Deposit *depositPtr;
   static const int INITIAL_REMAINING_BILLS = 500;
   int remainingBills = INITIAL_REMAINING_BILLS;

   bool userExited = false; // user has not chosen to exit

   // loop while user has not chosen option to exit system
   while ( !userExited )
   {     
      // show main menu and get user selection
      int mainMenuSelection = displayMainMenu();

      // decide how to proceed based on user's menu selection
      switch ( mainMenuSelection )
      {
         // user chose to perform one of three transaction types
         case BALANCE_INQUIRY: 
            // create new BalanceInquiry transaction
            balanceInquiryPtr = new BalanceInquiry( currentAccountNumber, accounts );
            balanceInquiryPtr->execute(); // execute transaction
            delete balanceInquiryPtr; // free the space for the dynamically allocated Transaction
            break;
         case WITHDRAWAL:
            // create new Withdrawal transaction
            withdrawalPtr = new Withdrawal( currentAccountNumber, accounts, remainingBills );
            withdrawalPtr->execute(); // execute transaction
            delete withdrawalPtr; // free the space for the dynamically allocated Transaction
            break; 
         case DEPOSIT:
            // create new Deposit transaction
            depositPtr = new Deposit( currentAccountNumber, accounts );
            depositPtr->execute(); // execute transaction
            delete depositPtr; // free the space for the dynamically allocated Transaction
            break; 
         case EXIT: // user chose to terminate session
            cout << "\nExiting the system..." << endl;
            userExited = true; // this ATM session should end
            break;
         default: // user did not enter an integer from 1-4
            cout << "\nYou did not enter a valid selection. Try again." << endl;
            break;
      } // end switch
   } // end while
} // end function performTransactions

// display the main menu and return an input selection
int displayMainMenu()
{
   cout << "\nMain menu:" << endl;
   cout << "1 - View my balance" << endl;
   cout << "2 - Withdraw cash" << endl;
   cout << "3 - Deposit funds" << endl;
   cout << "4 - Exit\n" << endl;
   cout << "Enter a choice: ";
   int choice;
   cin >> choice;
   return choice; // return user's selection
} // end function displayMainMenu