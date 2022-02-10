#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H
#include "Vector.h" // include definition of class vector 

// HugeInteger class definition
class HugeInteger
{
public:
   HugeInteger(); // default constructor; construct a HugeInteger with size 0

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger &assign( const HugeInteger &right ); // assignment operator
   bool equal( const HugeInteger &right ) const;          // equal to
//   bool notEqual( const HugeInteger &right ) const;       // not equal to
   bool less( const HugeInteger &right ) const;           // less than
   bool lessEqual( const HugeInteger &right ) const;      // less than or equal to
//   bool greater( const HugeInteger &right ) const;        // greater than
//   bool greaterEqual( const HugeInteger &right ) const;   // greater than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger add( HugeInteger &op2 );

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger subtract( HugeInteger &op2 );

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger multiply( HugeInteger &op2 );

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger divide( HugeInteger &op2 );

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger modulus( HugeInteger &op2 );

   void convert( vector &v ); // convert a vector of decimal digits into a HugeInteger
   bool isZero();           // return true if and only if all digits are zero
   void output( ostream &outFile );                 // output a HugeInteger
private:
   vector integer;
   HugeInteger( unsigned int n ); // constructor; construct a zero HugeInteger with size n
   void divideByTen();            // HugeInteger /= 10
}; // end class HugeInteger

#endif