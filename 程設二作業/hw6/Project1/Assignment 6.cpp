// HugeInteger test program.
#include <iostream>
using std::cout;
using std::endl;

#include <list>
#include "List.h" // include definition of class template list

void testPushFront();
void testPushBack();
void testResize();
void testList();
void testCopyConstructor();
void testAssignment1();
void testAssignment2();

// return true iff the addresses of nodes in list1[0 .. minSize]
// keep unchanged after assignment
bool efficientAssignment( list< int > &list1, list< int > &list2 );

// return true iff left == right
bool equal( list< int > &left, std::list< int > &right );

const unsigned int number = 500;

int main()
{
  for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testPushFront();
   }

  for (unsigned int seed = 1; seed <= 5; seed++)
  {
      srand(seed);
      testPushBack();
  }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testResize();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testList();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testCopyConstructor();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testAssignment1();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testAssignment2();
   }

   cout << endl;

   system( "pause" );
}

void testPushFront()
{
   list< int > list1;
   std::list< int > list2;

   unsigned int numErrors = number;
   int value;
   for( unsigned int i = 0; i < number; i++ )
   {
      value = 1 + rand() % 99;
      list1.push_front( value );
      list2.push_front( value );

      if( equal( list1, list2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors\n";
}

void testPushBack()
{
   list< int > list1;
   std::list< int > list2;

   unsigned int numErrors = number;
   int value;
   for( unsigned int i = 0; i < number; i++ )
   {
      value = 1 + rand() % 99;
      list1.push_back( value );
      list2.push_back( value );

      if( equal( list1, list2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors\n";
}

void testResize()
{
   list< int > list1;
   std::list< int > list2;

   unsigned int numErrors = number;
   unsigned int length;
   for( unsigned int i = 0; i < number; i++ )
   {
      length = rand() % 200;
      list1.resize( length );
      list2.resize( length );

      if( equal( list1, list2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors\n";
}

void testList()
{
   list< int > list1;
   std::list< int > list2;

   unsigned int numErrors = number; // number of errors
   unsigned int length;
   int value;
   unsigned int choice;
   for( unsigned int i = 0; i < number; i++ )
   {
      choice = rand() % 5;
      switch( choice )
      {
      case 0:
         value = 1 + rand() % 99;
         list1.push_front( value );
         list2.push_front( value );
         break;
      case 1:
         value = 1 + rand() % 99;
         list1.push_back( value );
         list2.push_back( value );
         break;
      case 2:
         if( !list1.empty() )
         {
            list1.pop_front();
            list2.pop_front();
         }
         break;
      case 3:
         if( !list1.empty() )
         {
            list1.pop_back();
            list2.pop_back();
         }
         break;
      case 4:
         length = rand() % 200;
         list1.resize( length );
         list2.resize( length );
         break;
      default:
         break;
      }

      if( equal( list1, list2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors\n";
}

void testCopyConstructor()
{
   unsigned int numErrors = number;
   unsigned int length;
   int value;
   for( unsigned int i = 0; i < number; i++ )
   {
      list< int > list1;
      std::list< int > list2;
      length = rand() % 200;
      for( unsigned int j = 0; j < length; j++ )
      {
         value = 1 + rand() % 99;
         list1.push_back( value );
         list2.push_back( value );
      }

      list< int > list3( list1 );
      std::list< int > list4( list2 );

      if( equal( list3, list4 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors\n";
}

void testAssignment1()
{
   list< int > list3;
   std::list< int > list4;

   unsigned int numErrors = number;
   unsigned int length;
   int value;
   for( unsigned int i = 0; i < number; i++ )
   {
      list< int > list1;
      std::list< int > list2;
      length = rand() % 200;
      for( unsigned int j = 0; j < length; j++ )
      {
         value = 1 + rand() % 99;
         list1.push_back( value );
         list2.push_back( value );
      }

      list3 = list1;
      list4 = list2;

      if( equal( list3, list4 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors\n";
}

void testAssignment2()
{
   unsigned int numErrors = number;
   unsigned int length;
   for( unsigned int i = 0; i < number; i++ )
   {
      list< int > list1;
      length = rand() % 100;
      for( unsigned int j = 0; j < length; j++ )
         list1.push_back( 1 + rand() % 99 );

      list< int > list2;
      length = rand() % 100;
      for( unsigned int j = 0; j < length; j++ )
         list2.push_back( 1 + rand() % 99 );

      if( efficientAssignment( list1, list2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors\n";
}

// return true iff the addresses of nodes in list1[0 .. minSize]
// keep unchanged after assignment
bool efficientAssignment( list< int > &list1, list< int > &list2 )
{
   size_t minSize = ( list1.size() < list2.size() ) ? list1.size() : list2.size();
   // let n = minSize, and node 1, node 2, ..., node n be the first n nodes of list1.

   list< int >::iterator *addresses = new list< int >::iterator[ minSize + 1 ];

   // p = list1.myData.myHead->next i.e., the address of the first node of list1
   list< int >::iterator p = list1.begin();
   for( size_t i = 1; i <= minSize; ++i, p = p->next )
      addresses[ i ] = p; // save the address of node i

   // addresses[ i ] is the address of node i before the excution of list1 = list2.

   list1 = list2;

   // p = list1.myData.myHead->next i.e., the address of the first node of list1
   p = list1.begin();
   for( size_t i = 1; i <= minSize; ++i, p = p->next )
      // p is the address of node i after the excution of list1 = list2
      if( addresses[ i ] != p )
         return false;

   // addresses[ i ] == p if and only if
   // node i of list1 before the excution of list1 = list2 is the same node as
   // node i of list1 after the excution of list1 = list2
   // i.e., there is no memory allocation during the excution of
   // list1 = list2

   return true;
}

// return true iff left == right
bool equal( list< int > &left, std::list< int > &right )
{
   if( left.size() != right.size() ) // different number of elements
      return false;

   list< int >::iterator it1 = left.begin();
   std::list< int >::iterator it2 = right.begin();
   for( ; it1 != left.end() && it2 != right.end(); it1 = it1->next, ++it2 )
      if( it1->myVal != *it2 )
         return false;

   return true;
}