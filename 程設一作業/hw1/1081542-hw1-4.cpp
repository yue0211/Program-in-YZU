// Determine whether three values represent the sides of a right triangle.
#include <iostream>
using namespace std; 

int main()
{
   int side1; // length of side 1
   int side2; // length of side 2
   int side3; // length of side 3
  
   // get values of three sides
   cout << "Enter side 1: ";
   cin >> side1;

   cout << "Enter side 2: ";
   cin >> side2;

   cout << "Enter side 3: ";
   cin >> side3;
       int a,b,c;
    a = side1*side1;
    b = side2*side2;
    c = side3*side3;
   if(a+b==c || a+c==b || b+c==a)
   cout<<"These are the sides of a right triangle";
   else
   cout<<"These do not form a right triangle"; 

   system( "pause" );
} // end main
