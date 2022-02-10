// HugeInteger test program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include "HugeInteger 9-1.h"

int enterChoice();

template< typename T >
void testHugeIntegers( HugeInteger< T > n1[], HugeInteger< T > n2[] );

template< typename T >
void input( HugeInteger< T > n1[], HugeInteger< T > n2[] );

template< typename T >
void print( ostream &outFile, HugeInteger< T > &n1, HugeInteger< T > &n2 );

const int numTestCases = 22;

int main()
{
   HugeInteger< int > n1[ numTestCases ];
   HugeInteger< int > n2[ numTestCases ];
   HugeInteger< unsigned int > n3[ numTestCases ];
   HugeInteger< unsigned int > n4[ numTestCases ];
   HugeInteger< short int > n5[ numTestCases ];
   HugeInteger< short int > n6[ numTestCases ];
   HugeInteger< unsigned short int > n7[ numTestCases ];
   HugeInteger< unsigned short int > n8[ numTestCases ];

   int choice = enterChoice();

   switch( choice )
   {
   case 1:
      testHugeIntegers( n1, n2 );
      break;
   case 2:
      testHugeIntegers( n3, n4 );
      break;
   case 3:
      testHugeIntegers( n5, n6 );
      break;
   case 4:
      testHugeIntegers( n7, n8 );
      break;
   default:
      cout << "Program should never get here!";
   }

   system( "pause" );
}

int enterChoice()
{
   cout << "Enter your choice\n"
      << " 1 - test int\n"
      << " 2 - test unsigned int\n"
      << " 3 - test short int\n"
      << " 4 - test unsigned short int\n";

   int menuChoice;
   do
   {
      cout << "? ";
      cin >> menuChoice;
   } while( ( menuChoice < 1 ) || ( menuChoice > 4 ) );
   cout << endl;

   return menuChoice;
} // end function enterChoice1

template< typename T >
void testHugeIntegers( HugeInteger< T > n1[], HugeInteger< T > n2[] )
{
   input( n1, n2 );

   for( int i = 0; i < numTestCases; i++ )
      print( cout, n1[ i ], n2[ i ] );

   ofstream outFile( "Result.txt", ios::out );

   // exit program if ofstream could not open file
   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   for( int i = 0; i < numTestCases; i++ )
      print( outFile, n1[ i ], n2[ i ] );

   outFile.close();
}

template< typename T >
void input( HugeInteger< T > n1[], HugeInteger< T > n2[] )
{
   ifstream inFile( "Test cases.txt", ios::in );

   // exit program if ofstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   char digit;
   for( int i = 0; i < numTestCases; i++ )
   {
      deque< T > deque1, deque2;

      while( ( digit = inFile.get() ) != '\n' )
         deque1.push_front( digit - '0' );

      while( ( digit = inFile.get() ) != '\n' )
         deque2.push_front( digit - '0' );
      inFile.get();

      n1[ i ] = deque1;
      n2[ i ] = deque2;
   }

   inFile.close();
}

template< typename T >
void print( ostream &outFile, HugeInteger< T > &n1, HugeInteger< T > &n2 )
{
   if( n1.isZero() )
      outFile << n1 << endl;
   else
   {
      --n1;
      outFile << ++n1 << endl;
   }

   outFile << n2++ << endl;
   n2--;

   outFile << n1 + n2 << endl;

   if( n1 < n2 )
      outFile << '-' << n2 - n1 << endl;
   else
      outFile << n1 - n2 << endl;

   outFile << n1 * n2 << endl;

   if( n2.isZero() )
      outFile << "DivideByZero!\n";
   else
      outFile << n1 / n2 << endl;

   if( n2.isZero() )
      outFile << "DivideByZero!\n";
   else
      outFile << n1 % n2 << endl;

   outFile << endl;
}