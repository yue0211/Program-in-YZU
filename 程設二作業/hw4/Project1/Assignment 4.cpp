// HugeInteger test program.
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::ios;

#include "HugeInteger.h" // include definition of class HugeInteger

void input( HugeInteger n1[], HugeInteger n2[] );
void print( ostream &outFile, HugeInteger n1, HugeInteger n2 );

const int numTestCases = 22;

int main()
{
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
      string string1, string2;

      while( ( digit = inFile.get() ) != '\n' )
         string1.push_back( digit );
      // the leftmost digit (i.e., the most significant digit) will be put into vector1[ 0 ]

      while( ( digit = inFile.get() ) != '\n' )
         string2.push_back( digit );
      // the leftmost digit (i.e., the most significant digit) will be put into vector2[ 0 ]
      inFile.get();

      n1[ i ].convert( string1 );
      n2[ i ].convert( string2 );
   }

   inFile.close();
}

void print( ostream &outFile, HugeInteger n1, HugeInteger n2 )
{
   outFile << n1 << endl;
   outFile << n2 << endl;

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