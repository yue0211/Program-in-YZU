#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
   int a,b,c,d,e,f,g,h,i; // integer read from user

   cout << "Enter a five-digit integer: "; // prompt
   cin >>a; // read integer from user
   b = a % 10000;
   c = b % 1000;
   d = c % 100;
   e = d % 10;
   f = (a-b)/10000;
   g = (b-c)/1000;
   h = (c-d)/100;
   i = (d-e)/10;
   cout<<f<<" "<<g<<" "<<h<<" "<<i<<" "<<e;
     system( "pause" );
} // end main
