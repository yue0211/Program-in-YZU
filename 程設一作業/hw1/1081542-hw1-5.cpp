#include <iostream>
using namespace std;

int main()
{
   int a;
   cout << "Enter a year ( 1583-3000 ): ";
   cin >> a;
   if(a%4==0&&a%100!= 0 || a%400==0)
   cout<<"Year"<<" "<<a<<" "<<"is a leap year" ;
   else
   cout<<"Year"<<" "<<a<<" "<<"is a common year";
   system( "pause" );
}
