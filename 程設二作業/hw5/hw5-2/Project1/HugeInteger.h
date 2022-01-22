// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "Vector.h" // include definition of class vector 

template< typename T >
class HugeInteger
{
   template< typename T >
   friend ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger );
public:
   HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with size n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger& operator=( const HugeInteger &right ); // assignment operator

   bool operator==( const HugeInteger &right ) const; // less than or equal to

   bool operator<( const HugeInteger &right ) const;  // less than

   bool operator<=( const HugeInteger &right ) const; // less than or equal to

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

   void convert( T &v ); // convert a vector of decimal digits into a HugeInteger
   bool isZero() const;           // return true if and only if all digits are zero
private:
   T integer;

   void divideByTen();            // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1
   void helpDecrement();          // decrements a HugeInteger by 1
}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n == 0 ) ? 1 : n )
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
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( const HugeInteger< T > &right ) const
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<( const HugeInteger< T > &right ) const
{
    typename  T ::const_iterator it1 = integer.end() - 1;
    typename  T ::const_iterator it2 = right.integer.end() - 1;
    unsigned int op1Size = integer.size();
    unsigned int op2Size = right.integer.size();

    if (op1Size > op2Size)     //right的尺寸大於物件的尺寸，回傳true
    {
        return false;
    }
    else if (op1Size < op2Size)
    {
        return true;
    }
    else if (op1Size == op2Size)    //如果尺寸相同，比較每個位數的值，從最大的位數比到最小位
    {
        for (; it2 != (right.integer.begin() - 1) && *(it2) >= *(it1);)
        {
            if (*(it1) < *(it2))
            {
                return true;
            }
            else if (*(it1) > * (it2))
            {
                return false;
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
bool HugeInteger< T >::operator<=( const HugeInteger< T > &right ) const
{
   return ( *this == right || *this < right );
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( HugeInteger< T > &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   typename T::iterator it1 = integer.begin();
   typename T::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   typename T::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         *it3 -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-( HugeInteger< T > &op2 )
{
   HugeInteger zero;

   if( *this == op2 )
      return zero;

   HugeInteger difference( *this );

   typename  T ::iterator it1 = difference.integer.begin();
   typename  T ::iterator it2 = op2.integer.begin();
   for (; it1 != difference.integer.end(); it1++)  //為了非負整數的轉換，所以全部先加10避免減的過程出現負數
   {
       *it1 += 10;
   }
   for (it1 = difference.integer.begin(); it2 != op2.integer.end(); it1++, it2++)
   {
       *it1 -= *it2;
   }

   for (it1 = difference.integer.begin(); it1 != (difference.integer.end() - 1); it1++)  //檢查difference是否小於10，小於10就借位
   {
       if (*it1 < 10)
       {
           *(it1) += 10;
           (*(it1 + 1)) -= 1;

       }
   }

   for (it1 = difference.integer.begin(); it1 != difference.integer.end(); it1++)  //做完計算再全部減10
   {
       *it1 -= 10;
   }

   for (it1 = difference.integer.end() - 1; difference.integer.size() > 1 && *it1 == 0; it1--) //如果第一個數字是0，就尺寸減一
   {
       difference.integer.pop_back();
   }

   return difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*( HugeInteger< T > &op2 )
{
   HugeInteger< T > zero;
   if( isZero() || op2.isZero() )
      return zero;

   unsigned int productSize = integer.size() + op2.integer.size();
   unsigned int op2Size = integer.size();
   unsigned int op3Size = op2.integer.size();
   HugeInteger<T>product(productSize);
   typename  T ::iterator it1 = product.integer.begin();
   typename  T ::iterator it2 = integer.begin();
   typename T ::iterator it3 = op2.integer.begin();
   for (; it1 != product.integer.end(); it1++)
   {
       *it1 = 0;
   }
   it1 = product.integer.begin();
   int i = 0;
   for (; it3 != op2.integer.end(); it3++)   //乘法計算
   {
       for (it2 = integer.begin(); it2 != integer.end(); it2++, it1++)
       {
           *(it1) = *(it1)+*(it2) * *(it3);
       }
       i += 1;
       it1 = product.integer.begin() + i;
   }
   it1 = product.integer.begin();
   for (; it1 != product.integer.end(); it1++)  //做完計算後的進位
   {
       (*(it1 + 1)) += *(it1) / 10;
       *(it1) %= 10;
   }
   for (it1 = product.integer.end() - 1; product.integer.size() > 1 && *it1 == 0; it1--) //如果第一個數字是0，就尺寸減一
   {
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

   HugeInteger  remainder(integer.size());
   HugeInteger  buffer(integer.size());


   typename  T ::iterator it1 = remainder.integer.end() - 1;
   typename  T ::iterator it2 = integer.end() - 1;
   typename  T ::iterator it3 = op2.integer.end() - 1;
   typename T ::iterator it5 = buffer.integer.end() - 1;


   for (it1 = remainder.integer.end() - 1; it2 != (integer.begin() - 1); it1--, it2--)   //將被除數存到remainder
   {
       *it1 = *it2;
   }

   for (it5 = buffer.integer.end() - 1; it3 != (op2.integer.begin() - 1); it5--, it3--)  //將除數存到buffer，而且和remainder對齊
   {
       *it5 = *it3;
   }
   HugeInteger  quotient(integer.size() - op2.integer.size());
   typename  T ::iterator it6 = quotient.integer.end() - 1;

   if (op2.integer.size() == 1 && op2.integer.front() == 1) //當除數是1的情況下，quotient=被除數
   {
       HugeInteger  quotient(integer.size());

       for (it2 = integer.end() - 1, it6 = quotient.integer.end() - 1; it2 != (integer.begin() - 1); it6--, it2--)
       {
           *it6 = *it2;
       }
       return quotient;
   }

   if (remainder < buffer) //如果buffer>remainder   ， buffer就退一位
   {
       buffer.divideByTen();
   }
   else   //如果buffer<=remainder，就調整quotient的尺寸
   {
       quotient.integer.resize(integer.size() - op2.integer.size() + 1);
   }

   for (it6 = quotient.integer.end() - 1; it6 != (quotient.integer.begin() - 1); it6--)  //做除法的計算
   {
       while (!(remainder < buffer))    //當buffer<=remainder
       {
           remainder = remainder - buffer;  //做減法並將值指派給remainder

           (*it6)++; //quotient的值
           for (it1 = remainder.integer.end() - 1; remainder.integer.size() > 1 && *it1 == 0; it1--) //如果第一個數字是0，就尺寸減一
           {
               remainder.integer.pop_back();
           }

       }
       if (remainder < buffer) //如果buffer>remainder   ， buffer就退一位
       {
           buffer.divideByTen();
       }
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
   HugeInteger temp = *this; // hold current state of object
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

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert( T &v )
{
   integer.resize( v.size() );
   typename T::iterator it1 = integer.end() - 1;
   typename T::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
   typename T::const_iterator it = integer.begin();
   for( ; it != integer.end(); ++it )
      if( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   typename T::iterator it = integer.begin() + 1;
   for( ; it != integer.end(); ++it )
      *( it - 1 ) = *it;
   integer.pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
   typename T::iterator it = integer.begin();
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
      *( it ) = 0;
      integer.resize( integer.size() + 1 );
      it = integer.end();
      --it;
      *it = 1;
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
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::iterator it = hugeInteger.integer.end() - 1;
   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}

#endif