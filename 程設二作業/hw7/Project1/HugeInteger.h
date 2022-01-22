// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "Vector.h" // include definition of class template vector
#include "List.h"   // include definition of class template list


/*#include <vector> // include definition of class template vector
#include <list>   // include definition of class template list
using std::vector;
using std::list;*/


template< typename T >
class HugeInteger
{
   template< typename T >
   friend ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger );
public:
   HugeInteger( size_t n = 0 ); // constructor; construct a zero HugeInteger with mySize n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger& operator=( const HugeInteger &right ); // assignment operator

   bool operator==( HugeInteger &right ); // less than or equal to
   bool operator<( HugeInteger &right );  // less than
   bool operator<=( HugeInteger &right ); // less than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger operator+( HugeInteger &op2 );

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( HugeInteger &op2 );

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( HugeInteger &op2 );

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator/( HugeInteger &op2 );

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator%( HugeInteger &op2 );

   HugeInteger& operator++(); // prefix increment operator
     
   HugeInteger operator++( int ); // postfix increment operator

   HugeInteger& operator--(); // prefix decrement operator

   HugeInteger operator--( int ); // postfix decrement operator

   bool isZero(); // return true if and only if all digits are zero

   void convert( T &v ); // convert a vector of decimal digits into a HugeInteger

private:
   T integer;

   void divideByTen();            // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1
   void helpDecrement();          // decrements a HugeInteger by 1
}; // end class template HugeInteger

#endif


// constructor; construct a zero HugeInteger with mySize n
template< typename T >
HugeInteger< T >::HugeInteger( size_t n )
   : integer( ( n > 0 ) ? n : 1 )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger< T > &integerToCopy )
   : integer( integerToCopy.integer )
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T >& HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
} // end function operator=

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( HugeInteger< T > &right )
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<( HugeInteger< T > &right )
{
    if (integer.size() > right.integer.size())
    {
        return false;
    }
    if (integer.size() < right.integer.size())
    {
        return true;
    }
    else if(integer.size() == right.integer.size())
    {
        /*typename T::reverse_iterator it1 = right.integer.rbegin();
        typename T::reverse_iterator it2 = integer.rbegin() ;
        for (; it1!= (right.integer.rend());)
        {
            if (*it1 < *it2)
            {
                return false;
            }
            if (*it1 > * it2)
            {
                return true;
            }
            else
            {
                it1++;
                it2++;
            }
        }
        return false;*/
        typename T::iterator it1 =-- integer.end() ;
        typename T::iterator it2 = --right.integer.end() ;
        for (;it1!=--integer.begin();)
        {
            if (*it1 > *it2)
            {
                return false;
            }
            if (*it1 < * it2)
            {
                return true;
            }
            else
            {
                it1--;
                it2--;
            }
        }
        return false;
    }

} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( HugeInteger< T > &right )
{
   return ( *this == right || *this < right );
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( HugeInteger< T > &op2 )
{
   size_t op1Size = integer.size();
   size_t op2Size = op2.integer.size();
   size_t sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger< T > sum( sumSize);
   typename T::iterator it1 = integer.begin();
   typename T::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   typename T::iterator it2 = op2.integer.begin();
   it3 = sum.integer.begin();
   for( ; it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   it3 = sum.integer.begin();
   typename T::iterator it4 = it3;
   for( ++it4; it4 != sum.integer.end(); ++it3, ++it4 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *it4 )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-( HugeInteger< T > &op2 )
{
   HugeInteger< T > zero;

   if( *this == op2 )
      return zero;

   HugeInteger< T > difference( *this );
   typename  T ::iterator it1 = difference.integer.begin();
   typename  T::iterator it2 = op2.integer.begin();
   for (; it1 != difference.integer.end(); ++it1) //為了非負整數的轉換，所以全部先加10避免減的過程出現負數
   {
       *it1 += 10;
   }
   for (it1 = difference.integer.begin(); it2 != op2.integer.end(); ++it1, ++it2)
   {
       *it1 -= *it2;
   }
   it1 = difference.integer.begin();
   typename T::iterator it4 = it1;
   for (it1 = difference.integer.begin(),++it4; it4 != (difference.integer.end() );++ it1,++it4)  //檢查difference是否小於10，小於10就借位
   {
       if (*it1 < 10)
       {
           *(it1) += 10;
           (*it4) -= 1;
       }
   }
   
   for (it1 = difference.integer.begin(); it1 != difference.integer.end(); ++it1) //做完計算再全部減10
   {
       *it1 -= 10;
   }
   it1 = --difference.integer.end();
   while (*(it1) == 0&& difference.integer.size()>1)
   {
        --it1;
       difference.integer.pop_back();
   }
   
   return difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*( HugeInteger< T > &op2 )
{
   HugeInteger zero;
   if( isZero() || op2.isZero() )
      return zero;

   size_t op1Size = integer.size();
   size_t op2Size = op2.integer.size();
   size_t productSize = op1Size + op2Size;

   HugeInteger< T > product( productSize );

   typename T ::iterator it1 = product.integer.begin();
   typename  T ::iterator it2 = integer.begin();
   typename T ::iterator it3 = op2.integer.begin();
   for (; it1 != product.integer.end();++ it1)
   {
       *it1 = 0;
   }
   it1 = product.integer.begin();
   typename T::iterator it5 = product.integer.begin();
   for (; it3 != op2.integer.end(); ++it3)   //乘法計算
   {
       for (it2 = integer.begin(); it2 != integer.end(); ++it2, ++it1)
       {
           *(it1) = *(it1)+*(it2) * *(it3);
       }
       ++it5;
       it1 = it5;
   }
   it1 = product.integer.begin();
   typename T::iterator it4 = ++it1;
   for (it1 = product.integer.begin(); it4 != product.integer.end(); ++it1,++it4)  //做完計算後的進位
   {
       (*(it4)) += *(it1) / 10;
       *(it1) %= 10;
   }
   it1 = --product.integer.end();
   while (*(it1) == 0 && product.integer.size() > 1)
   {
       --it1;
       product.integer.pop_back();
   }
   return product;

} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/( HugeInteger< T > &op2 )
{
   HugeInteger< T > zero;
   if( *this < op2 )
      return zero;
   HugeInteger remainder(*this);
   HugeInteger buffer(op2);
   HugeInteger ten(2);
   *(ten.integer.begin()) = 0;
   *(++ten.integer.begin()) = 1;

   while (buffer.integer.size() < integer.size())
       buffer = buffer * ten;

   HugeInteger quotient(integer.size() - op2.integer.size());

   if (remainder < buffer)
       buffer.divideByTen();
   else
       quotient.integer.resize(integer.size() - op2.integer.size() + 1);
   
   typename T::iterator it1 = --quotient.integer.end();
   typename T::iterator it2 = --remainder.integer.end();
   for (; it1 != (--quotient.integer.begin()); --it1)
   {
       while (!(remainder < buffer))
       {
           remainder = remainder - buffer;
           while ((*it2) == 0 && remainder.integer.size() > 1)
           {
               --it2;
               remainder.integer.pop_back();
           }
           ++(*it1);
       }
       buffer.divideByTen();
   }
   return  quotient;
   
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%( HugeInteger< T > &op2 )
{
   HugeInteger quotient = ( *this ) / op2;
   HugeInteger product = quotient * op2;
   HugeInteger remainder = ( *this ) - product;
   return remainder;
}

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator++()
{
   helpIncrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++( int )
{
   HugeInteger< T > temp = *this; // hold current state of object
   helpIncrement();

   // return unincremented, saved, temporary object
   return temp; // value return; not a reference return
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator--()
{
   helpDecrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--( int )
{
   HugeInteger temp = *this; // hold current state of object
   helpDecrement();

   // return unincremented, saved, temporary object
   return temp; // value return; not a reference return
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
   typename T::iterator it = integer.begin();
   for( ; it != integer.end(); ++it )
      if( *it != 0 )
         return false;

   return true;
}

// function that divides a HugeInteger by 10;
// shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   typename T::iterator it1 = integer.begin();
   typename T::iterator it2 = it1;
   for( ++it2; it2 != integer.end(); ++it1, ++it2 )
      *it1 = *it2;

   typename T::iterator it = integer.end();
   integer.pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
   typename T::iterator it = integer.begin();
   if( isZero() )
      ( *it )++;
   else
   {
      ( *it )++;
      typename T::iterator it2 = it;
      for( ++it2; it2 != integer.end(); ++it, ++it2 )
         if( *it == 10 )
         {
            *it = 0;
            ( *it2 )++;
         }

      if( ( *it ) == 10 )
      {
         *it = 0;
         integer.push_back( 1 );
      }
   }
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
   typename T::iterator it = integer.begin();
   for( ; *it == 0; ++it )
      *it = 9;

   ( *it )--;

   if( !isZero() && *it == 0 && it == --( integer.end() ) )
      integer.pop_back();
}

// convert a container of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert( T &v )
{
   integer.resize( v.size() );
   typename T::reverse_iterator it1 = integer.rbegin();
   typename T::iterator it2 = v.begin();
   for( ; it2 != v.end(); ++it1, ++it2 )
      *it1 = *it2;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   if( hugeInteger.isZero() )
      output << 0;
   else
   {
      typename T::reverse_iterator it = hugeInteger.integer.rbegin();
      for( ; it != hugeInteger.integer.rend(); ++it )
         if( *it < 10 )
            output << *it;
   }

   return output; // enables cout << x << y;
}