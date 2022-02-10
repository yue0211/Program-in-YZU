// Determine whether a number is a palindrome.
#include <iostream>
using namespace std; 

int main()
{
   int a,b,c,d,e,f,g,h,i; // integer read from user
   cout << "Enter a 5-digit number: "; // prompt for a number
   cin >> a; // get number
   b = a % 10000;
   c = b % 1000;
   d = c % 100;
   e = d % 10;
   f = (a-b)/10000;
   g = (b-c)/1000;
   h = (c-d)/100;
   i = (d-e)/10; 
   if(f==e && g==i ) 
   cout <<a<<" is a palindrome";
   else
   cout <<a<<"is not a palindrome";
   system( "pause" );
} // end main
