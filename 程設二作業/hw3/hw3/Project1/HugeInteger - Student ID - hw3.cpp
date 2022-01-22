// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
   : integer( 1 )
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1 )
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::assign( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer.assign( right.integer );

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::equal( const HugeInteger &right ) const
{
    vector::const_iterator it1 = integer.begin();
    vector::const_iterator it2 = right.integer.begin();
    unsigned int op1Size = integer.size();
    unsigned int op2Size = right.integer.size();
    if (op1Size > op2Size)    //如果位數不同，回傳false
    {
        return false;
    }
    else if (op1Size < op2Size)
    {
        return false;
    }
    else if (op1Size == op2Size)    //如果位數相同，比較每個位數的值是否相同
    {
        for (; it1 != integer.end();)
        {
            if (*(it1) != *(it2))
            {
                return false;
            }
            else
            {
                it1++;
                it2++;
            }
        }
        return true;
    }

} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::less( const HugeInteger &right ) const
{
    vector::const_iterator it1 = integer.end()-1;
    vector::const_iterator it2 = right.integer.end()-1;
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
        for (; it2 != (right.integer.begin()-1) && *(it2)>= *(it1);)
        {
            if (*(it1) < *(it2))
            {
                return true;
            }
            else if (*(it1) > *(it2))
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
  
} // end function less

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual( const HugeInteger &right ) const
{
   return ( less( right ) || equal( right ) );
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add( HugeInteger &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   vector::iterator it1 = integer.begin();
   vector::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   vector::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::subtract( HugeInteger &op2 )
{
   HugeInteger zero;

   if( equal( op2 ) )
      return zero;
   HugeInteger difference(*this);  //將物件的資料，傳到difference
   vector::iterator it1 = difference.integer.begin();
   vector::iterator it2= op2.integer.begin();
  
   for (;it2 != op2.integer.end(); it1++, it2++)
   {
       *it1 -= *it2;
   }

   for (it1 = difference.integer.begin(); it1!=(difference.integer.end()-1);it1++)  //檢查difference是否小於0，小於0就借位
   {
       if (*it1 < 0)
       {
           (*(it1 + 1)) -= 1;
           *(it1) += 10;
       }
   }

   for (  it1 = difference.integer.end()-1;difference.integer.size() > 1 && *it1 == 0; it1--) //如果第一個數字是0，就尺寸減一
   {
       difference.integer.pop_back();
   }
  
    return difference;
} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::multiply( HugeInteger &op2 )
{
   HugeInteger zero;
   if( isZero() || op2.isZero() )
      return zero;

   unsigned int productSize = integer.size() + op2.integer.size();
   unsigned int op2Size = integer.size();
   unsigned int op3Size = op2.integer.size();
   HugeInteger product( productSize );
   vector::iterator it1 = product.integer.begin();
   vector::iterator it2 = integer.begin();
   vector::iterator it3 = op2.integer.begin();
   for (; it1 != product.integer.end();it1++)
   {
       *it1 = 0;
   }
   it1= product.integer.begin();
   int i = 0;
   for (; it3!= op2.integer.end();it3++)   //乘法計算
   {
       for ( it2= integer.begin();it2!= integer.end();it2++,it1++)
       {
           *(it1) = *(it1) + *(it2) * *(it3);
       }
       i += 1;
       it1= product.integer.begin()+i;
   }
   it1 = product.integer.begin();
   for (;it1!= product.integer.end();it1++)  //做完計算後的進位
   {
       (*(it1 + 1)) += *(it1) / 10;
       *(it1) %= 10;
   }
   for (it1 = product.integer.end() - 1; product.integer.size() > 1 && *it1 == 0; it1--) //如果第一個數字是0，就尺寸減一
   {
       product.integer.pop_back();
   }
   
   return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::divide( HugeInteger &op2 )
{
   HugeInteger zero;
   if( less( op2 ) )
      return zero;

   HugeInteger remainder(integer.size());
   HugeInteger buffer(integer.size());


   vector::iterator it1 = remainder.integer.end()-1;
   vector::iterator it2 = integer.end() - 1;
   vector::iterator it3 = op2.integer.end()-1;
   vector::iterator it5 = buffer.integer.end()-1;

   
   for (it1 = remainder.integer.end() - 1;it2!= (integer.begin() - 1);it1--,it2--)   //將被除數存到remainder
   {
       *it1 = *it2;
   }
   
   for (it5 = buffer.integer.end() - 1;it3!= (op2.integer.begin()-1);it5--,it3--)  //將除數存到buffer，而且和remainder對齊
   {
       *it5 = *it3;
   }
   HugeInteger quotient(integer.size() - op2.integer.size());

   
   vector::iterator it6 = quotient.integer.end() - 1;
  
   if (remainder.less(buffer)) //如果buffer>remainder   ， buffer就退一位
   {
       buffer.divideByTen();
   }
   else   //如果buffer<=remainder，就調整quotient的尺寸
   {
       quotient.integer.resize(integer.size()- op2.integer.size()+1);
   }
   cout << "*-----------*\n" << quotient.integer.size() << endl;
   for (it6 = quotient.integer.end() - 1; it6!=(quotient.integer.begin()-1); it6--)  //做除法的計算
   {
       while (!remainder.less(buffer))    //當buffer<=remainder
       {
           remainder.assign(remainder.subtract(buffer));  //做減法並將值指派給remainder

           (*it6)++; //quotient的值
           for (it1= remainder.integer.end()-1; remainder.integer.size() > 1 && *it1 == 0; it1--) //如果第一個數字是0，就尺寸減一
           {
               remainder.integer.pop_back();
           }

       }
       if (remainder.less(buffer)) //如果buffer>remainder   ， buffer就退一位
       {
           buffer.divideByTen();
       }
   } 
   return  quotient;
} // end function divide

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::modulus( HugeInteger &op2 )
{
   HugeInteger quotient = divide( op2 );
   HugeInteger product = quotient.multiply( op2 );
   HugeInteger remainder = subtract( product );
   return remainder;
}

// convert a vector of decimal digits into a HugeInteger
void HugeInteger::convert( vector &v )
{
   integer.resize( v.size() );
   vector::iterator it1 = integer.end() - 1;
   vector::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
   for( vector::iterator it = integer.begin(); it != integer.end(); ++it )
      if ( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   vector::iterator it = integer.begin();
   vector::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.pop_back();
}

// overloaded output operator
void HugeInteger::output( ostream &outFile )
{
   vector::iterator it = integer.end() - 1;
   for( ; it != integer.begin() - 1; --it )
      if( *it < 10 )
         outFile << *it;
   outFile << endl;
} // end function output