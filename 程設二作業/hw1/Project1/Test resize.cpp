#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main()
{
   vector< int > v;
   for( unsigned int length = 0; length < 16; ++length )
   {
      v.resize( length );
      cout << setw( 4 ) << length << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
   }
   cout << endl;

   {
      vector< int > v( 5 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
      v.resize( 4 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl << endl;
   }

   {
      vector< int > v( 5 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
      v.resize( 6 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl << endl;
   }

   {
      vector< int > v( 5 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
      v.resize( 8 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl << endl;
   }

   {
      vector< int > v( 9 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
      v.resize( 8 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl << endl;
   }

   {
      vector< int > v( 9 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
      v.resize( 12 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl << endl;
   }

   {
      vector< int > v( 9 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
      v.resize( 16 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl << endl;
   }

   {
      vector< int > v( 10 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
      v.resize( 8 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl << endl;
   }

   {
      vector< int > v( 10 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
      v.resize( 12 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl << endl;
   }

   {
      vector< int > v( 10 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
      v.resize( 16 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl << endl;
   }

   {
      vector< int > v( 10 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
      v.resize( 12 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
      v.resize( 14 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl;
      v.resize( 16 );
      cout << setw( 4 ) << v.size() << setw( 4 ) << v.capacity() << endl << endl;
   }

   {
      vector< int > v1( 10, 3 );
      vector< int > v2( 8, 5 );
      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl;
      cout << setw( 4 ) << v2.size() << setw( 4 ) << v2.capacity() << endl;
      v1 = v2;
      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl << endl;
   }

   {
      vector< int > v1( 10, 3 );
      vector< int > v2( 12, 5 );
      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl;
      cout << setw( 4 ) << v2.size() << setw( 4 ) << v2.capacity() << endl;
      v1 = v2;
      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl << endl;
   }

   {
      vector< int > v1( 10, 3 );
      vector< int > v2( 16, 5 );
      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl;
      cout << setw( 4 ) << v2.size() << setw( 4 ) << v2.capacity() << endl;
      v1 = v2;
      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl << endl;
   }

   {
      vector< int > v1( 6, 3 );
      vector< int > v2( 5, 5 );
      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl;
      cout << setw( 4 ) << v2.size() << setw( 4 ) << v2.capacity() << endl;
      v1 = v2;
      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl << endl;
   }

   system( "pause" );
}