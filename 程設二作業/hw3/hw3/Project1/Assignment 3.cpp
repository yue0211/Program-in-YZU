// HugeInteger test program.
#include <iostream>
#include <fstream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

void input( HugeInteger n1[], HugeInteger n2[] );
void print( ostream &outFile, HugeInteger n1, HugeInteger n2 );

const int numTestCases = 22;

int main()
{
   //   system( "mode con cols=122 lines=12" );

   HugeInteger n1[ numTestCases ];
   HugeInteger n2[ numTestCases ];

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

   system( "pause" );
}

void input( HugeInteger n1[], HugeInteger n2[] )
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
      vector vector1, vector2;

      while( ( digit = inFile.get() ) != '\n' )
         vector1.push_back( digit - '0' );
      // the leftmost digit (i.e., the most significant digit) will be put into vector1[ 0 ]

      while( ( digit = inFile.get() ) != '\n' )
         vector2.push_back( digit - '0' );
      // the leftmost digit (i.e., the most significant digit) will be put into vector2[ 0 ]
      inFile.get();

      n1[ i ].convert( vector1 );
      n2[ i ].convert( vector2 );
   }

   inFile.close();
}

void print( ostream &outFile, HugeInteger n1, HugeInteger n2 )
{
   n1.output( outFile );
   n2.output( outFile );

   n1.add( n2 ).output( outFile );         // outputs n1 + n2

   if( n1.less( n2 ) )
   {
      outFile << '-';
      n2.subtract( n1 ).output( outFile ); // outputs n2 - n1
   }
   else
      n1.subtract( n2 ).output( outFile ); // outputs n1 - n2

   n1.multiply( n2 ).output( outFile );    // outputs n1 * n2

   if( n2.isZero() )
      outFile << "DivideByZero!\n";
   else
      n1.divide( n2 ).output( outFile );   // outputs n1 / n2

   if( n2.isZero() )
      outFile << "DivideByZero!\n";
   else
      n1.modulus( n2 ).output( outFile );  // outputs n1 % n2

   outFile << endl;
}