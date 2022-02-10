#ifndef DEQUE_H
#define DEQUE_H

#include "XUtility.h"

// CLASS TEMPLATE DequeConstIterator
template< typename MyDeque >
class DequeConstIterator
{
private:
   using size_type = typename MyDeque::size_type;

public:
   using value_type      = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer         = typename MyDeque::const_pointer;
   using reference       = const value_type &;

   // construct with null pointer
   DequeConstIterator()
      : myOff( 0 ),
        myCont( nullptr )
   {
   }

   // construct with offset off in *pDeque
   DequeConstIterator( size_type off, const MyDeque *pDeque )
      : myOff( off ),
        myCont( pDeque )
   {
   }

   DequeConstIterator( const DequeConstIterator &right ) // copy constructor
      : myOff( right.myOff ),
        myCont( right.myCont )
   {
   }

   ~DequeConstIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const DequeConstIterator& operator=( const DequeConstIterator &right )
   {
      if( &right != this ) // avoid self-assignment
      {
         myCont = right.myCont;
         myOff = right.myOff;
      }
      return *this; // enables x = y = z, for example
   }

   reference operator*() const
   {
//      size_type block = myOff % ( 4 * myCont->mapSize ) / 4;
      size_type block = myCont->getBlock( myOff );
      size_type off = myOff % 4;
      return myCont->map[ block ][ off ];
   }

   DequeConstIterator& operator++() // preincrement
   {
      ++myOff;
      return *this;
   }

   DequeConstIterator operator++( int ) // postincrement
   {
      DequeConstIterator tmp = *this;
      ++*this;
      return tmp;
   }

   DequeConstIterator& operator--() // predecrement
   {
      --myOff;
      return *this;
   }

   DequeConstIterator operator--( int ) // postdecrement
   {
      DequeConstIterator tmp = *this;
      --*this;
      return tmp;
   }

   // increment by integer
   DequeConstIterator& operator+=( const difference_type off )
   {
      myOff += off;
      return *this;
   }

   // return this + integer
   DequeConstIterator operator+( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeConstIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   // return this - integer
   DequeConstIterator operator-( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp -= off;
   }

   // return difference of iterators
   difference_type operator-( const DequeConstIterator &right ) const
   {
      return ( static_cast< difference_type >( this->myOff - right.myOff ) );
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return *( *this + off );
   }

   // test for iterator equality
   bool operator==( const DequeConstIterator &right ) const
   {
      return this ->myCont == right.myCont && this -> myOff == right.myOff;
   }

   // test for iterator inequality
   bool operator!=( const DequeConstIterator &right ) const
   {
      return !( *this == right );
   }

   // test if this < right
   bool operator<( const DequeConstIterator &right ) const
   {
      return this->myOff < right.myOff;
   }

   // test if this > right
   bool operator>( const DequeConstIterator &right ) const
   {
      return right < *this;
   }

   // test if this <= right
   bool operator<=( const DequeConstIterator &right ) const
   {
      return !( right < *this );
   }

   // test if this >= right
   bool operator>=( const DequeConstIterator &right ) const
   {
      return !( *this < right );
   }

   const MyDeque *myCont; // keep a pointer to deque
   size_type myOff;       // offset of element in deque
};


// CLASS TEMPLATE DequeIterator
template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{ // iterator for mutable deque
private:
   using size_type = typename MyDeque::size_type;
   using MyBase = DequeConstIterator< MyDeque >;

public:
   using value_type      = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer         = typename MyDeque::pointer;
   using reference       = value_type &;

   DequeIterator() // construct with null deque pointer
   {
   }

   DequeIterator( size_type off, const MyDeque *pDeque )
      : MyBase( off, pDeque ) // construct with offset off in *pDeque
   {
   }

   reference operator*() const // return designated object
   {
      return const_cast< reference >( MyBase::operator*() );
   }

   DequeIterator& operator++() // preincrement
   {
      MyBase::operator++();
      return *this;
   }

   DequeIterator operator++( int ) // postincrement
   {
      DequeIterator tmp = *this;
      MyBase::operator++();
      return tmp;
   }

   DequeIterator& operator--() // predecrement
   {
      MyBase::operator--();
      return *this;
   }

   DequeIterator operator--( int ) // postdecrement
   {
      DequeIterator tmp = *this;
      MyBase::operator--();
      return tmp;
   }

   // increment by integer
   DequeIterator& operator+=( const difference_type off )
   {
      MyBase::operator+=( off );
      return *this;
   }

   // return this + integer
   DequeIterator operator+( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeIterator& operator-=( const difference_type off )
   {
      MyBase::operator-=( off );
      return *this;
   }

   using MyBase::operator-; // return difference of iterators

   // return this - integer
   DequeIterator operator-( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp -= off;
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return const_cast< reference >( MyBase::operator[]( off ) );
   }
};

// CLASS TEMPLATE DequeVal
template< typename Ty >
class DequeVal // base class for deque to hold data
{
public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference       = value_type &;
   using const_reference = const value_type &;
   using MapPtr = Ty **;

   DequeVal() // initialize values
      : map(),
        mapSize( 0 ),
        myOff( 0 ),
        mySize( 0 )
   {
   }

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      return off % ( 4 * mapSize ) / 4;
//      return ( off / 4 ) & ( mapSize - 1 );
   }

   MapPtr map;        // pointer to array of pointers to blocks
   size_type mapSize; // size of map array, zero or 2^N
   size_type myOff;   // offset of initial element
   size_type mySize;  // current length of sequence
};


// CLASS TEMPLATE deque
template< typename Ty >
class deque // circular queue of pointers to blocks
{
private:
   using MapPtr = Ty **;
   using ScaryVal = DequeVal< Ty >;

public:
   using value_type      = Ty;
   using size_type       = size_t;
   using difference_type = ptrdiff_t;
   using pointer         = value_type *;
   using const_pointer   = const value_type *;
   using reference       = value_type &;
   using const_reference = const value_type &;

   using iterator               = DequeIterator< ScaryVal >;
   using const_iterator         = DequeConstIterator< ScaryVal >;

   using reverse_iterator       = ReverseIterator< iterator >;
   using const_reverse_iterator = ReverseIterator< const_iterator >;

   // construct empty deque
   deque()
      : myData()
   {
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   explicit deque( size_type count )
      : myData()
   {
      resize( count );
   }

   // construct by copying right
   deque( const deque &right )
      : myData()
   {
       if (myData.mySize == 0)
           myData.myOff = 0;

       *this = right;
   }

   // destroy the deque
   ~deque()
   {
      clear();
   }

   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   deque& operator=( const deque &right )
   {
      if( &right != this ) // avoid self-assignment
      {
          myData.myOff = right.myData.myOff;

          for (int i = 0; i < myData.mapSize; i++)  //刪除二維陣列
              if (myData.map[i] != nullptr)
                  delete[] myData.map[i];
          delete[] myData.map;

          myData.mapSize = right.myData.mapSize;
          myData.map = new Ty * [myData.mapSize]();

          for (int i=0;i< myData.mapSize;i++)
          {
              if (right.myData.map[i] != nullptr)
                  myData.map[i] = new Ty[4]();
          }
          typename deque<Ty>::iterator it1 = begin();
          typename deque<Ty>::const_iterator it2 = right.begin();
          myData.mySize = right.myData.mySize;
          for (;it2!= right.end();it1++,it2++)
          {
              *it1 = *it2;
          }
      } // end outer if

      return *this; // enables right = y = z, for example
   } // end function operator=

   // return iterator for beginning of mutable sequence
   iterator begin()
   {
      return iterator( myData.myOff, &myData );
   }

   // return iterator for beginning of nonmutable sequence
   const_iterator begin() const
   {
      return const_iterator( myData.myOff, &myData );
   }

   // return iterator for end of mutable sequence
   iterator end()
   {
      return iterator( myData.myOff + myData.mySize, &myData );
   }

   // return iterator for end of nonmutable sequence
   const_iterator end() const
   {
      return const_iterator( myData.myOff + myData.mySize, &myData );
   }

   // return iterator for beginning of reversed mutable sequence
   reverse_iterator rbegin()
   {
      return reverse_iterator( end() );
   }

   // return iterator for beginning of reversed nonmutable sequence
   const_reverse_iterator rbegin() const
   {
      return const_reverse_iterator( end() );
   }

   // return iterator for end of reversed mutable sequence
   reverse_iterator rend()
   {
      return reverse_iterator( begin() );
   }

   // return iterator for end of reversed nonmutable sequence
   const_reverse_iterator rend() const
   {
      return const_reverse_iterator( begin() );
   }

   // return iterator for beginning of nonmutable sequence
   const_iterator cbegin() const
   {
      return begin();
   }

   // return iterator for end of nonmutable sequence
   const_iterator cend() const
   {
      return end();
   }

   // return iterator for beginning of reversed nonmutable sequence
   const_reverse_iterator crbegin() const
   {
      return rbegin();
   }

   // return iterator for end of reversed nonmutable sequence
   const_reverse_iterator crend() const
   {
      return rend();
   }

   void resize( size_type newSize )
   {
      while( myData.mySize < newSize )
         push_back( value_type() );

      while( newSize < myData.mySize )
         pop_back();
   }

   // return length of sequence
   size_type size() const
   {
      return myData.mySize;
   }

   // test if sequence is empty
   bool empty() const
   {
      return myData.mySize == 0;
   }

   const_reference operator[]( size_type pos ) const
   {
      return *( begin() + static_cast< difference_type >( pos ) );
   }

   reference operator[]( size_type pos )
   {
      return *( begin() + static_cast< difference_type >( pos ) );
   }

   reference front()
   {
      return *begin();
   }

   const_reference front() const
   {
      return *begin();
   }

   reference back()
   {
      return *( end() - 1 );
   }

   const_reference back() const
   {
      return *( end() - 1 );
   }

   // insert element at beginning
   void push_front( const value_type &val )
   {

		if( myData.mySize == 0 )
      {
         if( myData.mapSize == 0 )
		 {
		 	myData.mapSize = 8;  
            myData.map = new Ty*[ myData.mapSize ]();
		 }  //新增8個的1格陣列
         
         if(myData.map[ myData.mapSize - 1 ] == nullptr)
         	myData.map[ myData.mapSize - 1 ] = new Ty[ 4 ]();  //先在最後一個 新增4格陣列
         myData.map[ myData.mapSize - 1 ][ 3 ] = val;
         myData.myOff = 4 * myData.mapSize - 1;
      }
      else
      {
         size_type newFront = ( myData.myOff - 1 ) % ( 4 * myData.mapSize );
         if( newFront % 4 == 3 && 4 * myData.mapSize - myData.mySize <= 4 ) //要換行的時候且 只剩還有一行還沒塞滿時要擴充格數
         {
            doubleMapSize();  //擴充格子
            newFront = ( myData.myOff - 1 ) % ( 4 * myData.mapSize );  //擴充完後 調整位置
         }
         myData.myOff %= (4 * myData.mapSize);  //保證myData.myOff 是正確的值

         if( newFront % 4 == 3 )//當每行的數字塞滿時，新增行數
		 	 if( myData.map[ newFront / 4 ] == nullptr )
            	myData.map[ newFront / 4 ] = new Ty[ 4 ]();

         myData.map[ newFront / 4 ][ newFront % 4 ] = val;   //除以4是算位於第幾列，%4 是算位於第幾個
         myData.myOff = newFront;
      }

      ++myData.mySize;

   }

   // erase element at beginning
   void pop_front()
   {
      if( --myData.mySize == 0 )
         myData.myOff = 0;
      else
         ++myData.myOff;
   }

   // insert element at end
   void push_back( const value_type &val )
   {
		if( myData.mySize == 0 )
      {
         if( myData.mapSize == 0 )
         {
         	myData.mapSize = 8;
         	myData.map = new Ty*[ myData.mapSize ]();    //新增8個的1格陣列
		 }
		 if(myData.map[ 0 ]==nullptr)
         	myData.map[ 0 ] = new Ty[ 4 ]();      //先在第一個 新增4格陣列
         myData.map[ 0 ][ 0 ] = val;
      }
      else
      {
         size_type newBack = ( myData.myOff + myData.mySize ) % ( 4 * myData.mapSize );
         if( newBack % 4 == 0 && 4 * myData.mapSize - myData.mySize <= 4) //要換行的時候且 只剩還有一行還沒塞滿時要擴充格數
         {
            doubleMapSize(); //擴充格子
            newBack = myData.myOff + myData.mySize;   //擴充完後 調整位置
         }
        myData.myOff %= ( 4 * myData.mapSize );  //保證myData.myOff 是正確的值

         if( newBack % 4 == 0 )   //當每行的數字塞滿時，新增行數
         	if( myData.map[ newBack / 4 ] == nullptr )
            	myData.map[ newBack / 4 ] = new Ty[ 4 ]();

         myData.map[ newBack / 4 ][ newBack % 4 ] = val;
      }

      ++myData.mySize;
   }

   // erase element at end
   void pop_back()
   {
      if( --myData.mySize == 0 )
         myData.myOff = 0;
   }

   // erase all
   void clear()
   {
      if( myData.mapSize > 0 )
      {
         for( size_type i = 0; i < myData.mapSize; i++ )
            if( myData.map[ i ] != nullptr )
               delete[] myData.map[ i ];
         delete[] myData.map;

         myData.mapSize = 0;
         myData.mySize = 0;
         myData.myOff = 0;
         myData.map = MapPtr();
      }
   }

private:

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      return myData.getBlock( off );
//      return ( ( myData.off / 4 ) & ( myData.mapSize - 1 ) );
   }

   void doubleMapSize()
   {
      if( myData.mapSize > 0 )
      {
          Ty** newMap = new Ty * [2 * myData.mapSize]();
          for (int i = getBlock(myData.myOff), j = getBlock(myData.myOff), k = 0; k < myData.mapSize; j++, k++)
          {
              newMap[j] = myData.map[i];
              if ((i+1) == myData.mapSize)
                  i = 0;
              else
                  i++;
          }
          delete [] myData.map;
          myData.map = newMap;
          myData.mapSize = 2 * myData.mapSize;
      }
   }

   ScaryVal myData;
};

// test for deque equality
template< typename Ty >
bool operator==( const deque< Ty > &left, const deque< Ty > &right )
{
	int op1Size=left.size();
	int op2Size=right.size();
	typename deque<Ty>::const_iterator it1=left.begin();
	typename deque<Ty>::const_iterator it2=right.begin();
	if(op1Size!=op2Size)
		return false;
	else
	{
		for(;it1!=left.end();)
		{
			if(*it1!=*it2)
			  return false;
			else
			{
				it1++;
				it2++;
			}
		}
		return true;
	}
}

#endif
