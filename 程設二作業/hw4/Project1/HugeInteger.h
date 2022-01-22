#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include "String.h" // include definition of class Vector

// HugeInteger class definition
class HugeInteger
{
   friend ostream& operator<<( ostream &output, const HugeInteger &hugeInteger );
public:
   HugeInteger(); // default constructor; construct a HugeInteger with size 0

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger& operator=( const HugeInteger &right ); // assignment operator

   bool operator==( const HugeInteger &right ) const; // equal to
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

   bool isZero(); // return true if and only if all digits are zero

   void convert( string &str );

//   void assign( string &str ); // assign a string of decimal digits into a HugeInteger
private:
   string integer;
   HugeInteger( unsigned int n ); // constructor; construct a zero HugeInteger with size n
   void divideByTen();            // HugeInteger /= 10
}; // end class HugeInteger

#endif