// vector standard header

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
using namespace std;
//#include "XUtility.h" // include definition of class template ReverseIterator

// CLASS TEMPLATE VectorConstIterator
template< typename MyVec >
class VectorConstIterator
{
public:
   using value_type = typename MyVec::value_type;
   using difference_type = typename MyVec::difference_type;
   using pointer = typename MyVec::const_pointer;
   using reference = const value_type &;
   using TPtr = typename MyVec::pointer;

   VectorConstIterator()
      : ptr()
   {
   }

   VectorConstIterator( TPtr parg )
      : ptr( parg )
   {
   }

   reference operator*() const
   {
      return *ptr;
   }

   pointer operator->() const
   {
      return ptr;
   }

   VectorConstIterator& operator++()
   {
      ++ptr;
      return *this;
   }

   VectorConstIterator operator++( int )
   {
      VectorConstIterator temp = *this;
      ++ *this;
      return temp;
   }

   VectorConstIterator& operator--()
   {
      --ptr;
      return *this;
   }

   VectorConstIterator operator--( int )
   {
      VectorConstIterator temp = *this;
      -- *this;
      return temp;
   }

   VectorConstIterator& operator+=( const difference_type off )
   {
      ptr += off;
      return *this;
   }

   VectorConstIterator operator+( const difference_type off ) const
   {
      VectorConstIterator temp = *this;
      return temp += off;
   }

   VectorConstIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   VectorConstIterator operator-( const difference_type off ) const
   {
      VectorConstIterator temp = *this;
      return temp -= off;
   }

   difference_type operator-( const VectorConstIterator &right ) const
   {
      return ptr - right.ptr;
   }

   reference operator[]( const difference_type off ) const
   {
      return *( *this + off );
   }

   bool operator==( const VectorConstIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const VectorConstIterator &right ) const
   {
      return !( *this == right );
   }

   bool operator<( const VectorConstIterator &right ) const
   {
      return ptr < right.ptr;
   }

   bool operator>( const VectorConstIterator &right ) const
   {
      return right < *this;
   }

   bool operator<=( const VectorConstIterator &right ) const
   {
      return !( right < *this );
   }

   bool operator>=( const VectorConstIterator &right ) const
   {
      return !( *this < right );
   }

   TPtr ptr; // pointer to element in vector
};


// CLASS TEMPLATE VectorIterator
template< typename MyVec >
class VectorIterator : public VectorConstIterator< MyVec >
{
public:
   using MyBase = VectorConstIterator< MyVec >;

   using value_type      = typename MyVec::value_type;
   using difference_type = typename MyVec::difference_type;
   using pointer         = typename MyVec::pointer;
   using reference       = value_type &;

   using MyBase::MyBase;

   reference operator*() const
   {
      return const_cast< reference >( MyBase::operator*() );
   }

   pointer operator->() const
   {
      return const_cast< pointer >( MyBase::operator->() );
   }

   VectorIterator& operator++()
   {
      MyBase::operator++();
      return *this;
   }

   VectorIterator operator++( int )
   {
      VectorIterator temp = *this;
      MyBase::operator++();
      return temp;
   }

   VectorIterator& operator--()
   {
      MyBase::operator--();
      return *this;
   }

   VectorIterator operator--( int )
   {
      VectorIterator temp = *this;
      MyBase::operator--();
      return temp;
   }

   VectorIterator& operator+=( const difference_type off )
   {
      MyBase::operator+=( off );
      return *this;
   }

   VectorIterator operator+( const difference_type off ) const
   {
      VectorIterator temp = *this;
      return temp += off;
   }

   VectorIterator& operator-=( const difference_type off )
   {
      MyBase::operator-=( off );
      return *this;
   }

   using MyBase::operator-;

   VectorIterator operator-( const difference_type off ) const
   {
      VectorIterator temp = *this;
      return temp -= off;
   }

   reference operator[]( const difference_type off ) const
   {
      return const_cast< reference >( MyBase::operator[]( off ) );
   }
};


// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
   using value_type = ValueType;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   VectorVal()
      : myFirst(),
        myLast(),
        myEnd()
   {
   }

   pointer myFirst; // pointer to beginning of array
   pointer myLast;  // pointer to current end of sequence
   pointer myEnd;   // pointer to end of array
};


// CLASS TEMPLATE vector
template< typename Ty >
class vector // varying size array of values
{
public:
   using value_type = Ty;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = Ty &;
   using const_reference = const Ty &;
   using size_type = size_t;
   using difference_type = ptrdiff_t;

private:
   using ScaryVal = VectorVal< Ty >;

public:
   using iterator = VectorIterator< ScaryVal >;
   using const_iterator = VectorConstIterator< ScaryVal >;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   vector()
      : myData()
   {
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   vector( const size_type count )
      : myData()
   {
      if( count != 0 )
      {
         myData.myFirst = new value_type[ count ]();
         myData.myLast = myData.myFirst + count;
         myData.myEnd = myData.myFirst + count;
      }
   }

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   vector( const vector &right )
      : myData()
   {
       Ty* temPtr = new Ty[right.size()];

       int i = 0;

       for (; i < right.size(); i++)
           temPtr[i] = right.myData.myFirst[i];

       myData.myFirst = temPtr;
       myData.myLast = temPtr + i;
       myData.myEnd = temPtr + i;

   }

   // Vector destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the vector.
   ~vector()
   {
      if( myData.myFirst != nullptr )
         delete[] myData.myFirst;
   }

   // Adds a new element at the end of the vector, after its current last element.
   // The content of val is copied (or moved) to the new element.
   // This effectively increases the container size by one,
   // which causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   void push_back( const value_type &val )
   {
      size_type originalSize = size();
      resize( originalSize + 1 );
      myData.myFirst[ originalSize ] = val;
   }

   // overloaded assignment operator
   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
   vector& operator=( const vector &right )
   {
       if (this != &right) // avoid self-assignment
       {
           int rightSize = right.size();

           if (rightSize > capacity())
           {
               if (size() > 0)
                   delete[] myData.myFirst; // release space

               int newcapacity = capacity() * 1.5;

               if (rightSize > newcapacity)
                   newcapacity = rightSize;

               myData.myFirst = new Ty[newcapacity];
               myData.myEnd = myData.myFirst + newcapacity;
           }
           myData.myLast = myData.myFirst + rightSize;

           for (int i = 0; i < rightSize; i++)
               myData.myFirst[i] = right.myData.myFirst[i];

       }

       return *this;
   }

   // Resizes the container so that it contains "newSize" elements.
   // If "newSize" is smaller than the current container size,
   // the content is reduced to its first "newSize" elements, removing those beyond.
   // If "newSize" is greater than the current container size,
   // the content is expanded by inserting at the end as many elements as needed
   // to reach a size of "newSize".
   // The new elements are initialized as 0.
   // If "newSize" is also greater than the current container capacity,
   // an automatic reallocation of the allocated storage space takes place.
   void resize( const size_type newSize )
   {
       int originalSize = size();
       if (newSize > originalSize)
       {
           if (newSize > capacity())
           {
               int newCapacity = capacity() * 3 / 2;
               if (newCapacity < newSize)
                   newCapacity = newSize;

               Ty* tempPtr = myData.myFirst;
               myData.myFirst = new Ty[newCapacity]();
               for (int i = 0; i < originalSize; ++i)
                   myData.myFirst[i] = tempPtr[i];

               delete[] tempPtr;

               myData.myEnd = myData.myFirst + newCapacity;
           }

           for (int i = originalSize; i < newSize; ++i)
               myData.myFirst[i] = Ty();
       }

       myData.myLast = myData.myFirst + newSize;
   }

   // Removes the last element in the vector,
   // effectively reducing the container size by one.
   void pop_back()
   {
      if( size() > 0 )
         --myData.myLast;
   }

   // Removes from the vector either a single element (where).
   // This effectively reduces the container size by one, which is destroyed.
   // Relocates all the elements after the element erased to their new positions.
   iterator erase( const_iterator where )
   {
       if (where >= myData.myFirst && where < myData.myLast)
       {
           Ty* p = new Ty[size() - 1];
           int news = capacity();
           iterator it1 = myData.myFirst;  
           iterator it2 = myData.myFirst + 1;
           iterator it3 = myData.myLast; 
           int i = 0;
           if (it1 == where)
           {
               for (; it2 != it3; it1++, it2++) 
               {
                   *(it1) = *(it2); 
               }
               myData.myLast--; 
           }
           else
           {
               int i = 0;
               for (it1 = myData.myFirst; it1 != where; it1++, i++)
               {
                   *it1 = *it1; 
               }
               it2 = it1;
               for (it1++; it1 != it3; it2++, it1++) 
               {
                   *it2 = *it1; 
               }
               myData.myLast--; 
           }
           return myData.myFirst;  
       }
       else
           return nullptr;
   }

   // Removes all elements from the vector (which are destroyed),
   // leaving the container with a size of 0.
   // A reallocation is not guaranteed to happen,
   // and the vector capacity is not guaranteed to change due to calling this function.
   void clear()
   {
      myData.myLast = myData.myFirst;
   }

   // Returns an iterator pointing to the first element in the vector.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return iterator( myData.myFirst );
   }

   // Returns an iterator pointing to the first element in the vector.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myFirst );
   }

   // Returns an iterator referring to the past-the-end element in the vector container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as vector::begin.
   iterator end()
   {
      return iterator( myData.myLast );
   }

   // Returns an iterator referring to the past-the-end element in the vector container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as vector::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myLast );
   }

   // Returns whether the vector is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.myFirst == myData.myLast;
   }

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   size_type size() const
   {
      return static_cast< size_type >( myData.myLast - myData.myFirst );
   }

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   // This capacity is not necessarily equal to the vector size.
   // It can be equal or greater, with the extra space allowing to accommodate
   // for growth without the need to reallocate on each insertion.
   size_type capacity() const
   {
      return static_cast< size_type >( myData.myEnd - myData.myFirst );
   }

   // Returns a reference to the element at position "pos" in the vector container.
   value_type& operator[]( const size_type pos )
   {
      if( pos >= static_cast< size_type >( myData.myLast - myData.myFirst ) )
      {
         cout << "vector subscript out of range\n";
         exit( 1 );
      }

      return myData.myFirst[ pos ];
   }

   // Returns a reference to the element at position "pos" in the vector container.
   const value_type& operator[]( const size_type pos ) const
   {
      if( pos >= static_cast< size_type >( myData.myLast - myData.myFirst ) )
      {
         cout << "vector subscript out of range\n";
         exit( 1 );
      }

      return myData.myFirst[ pos ];
   }

private:
   ScaryVal myData;
};

#endif // VECTOR_H