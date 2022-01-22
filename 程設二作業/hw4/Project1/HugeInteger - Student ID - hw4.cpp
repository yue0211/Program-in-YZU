#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
    : integer(1, '0')
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger(unsigned int n)
    : integer((n > 0) ? n : 1, '0')
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger(const HugeInteger& integerToCopy)
    : integer(integerToCopy.integer)
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger& HugeInteger::operator=(const HugeInteger& right)
{
    if (&right != this) // avoid self-assignment
        integer = right.integer;

    return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::operator==(const HugeInteger& right) const
{
    //   return operator==( integer, right.integer );
    return (integer == right.integer);
} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::operator<(const HugeInteger& right) const
{
    string::const_iterator it1 = integer.end() - 1;
    string::const_iterator it2 = right.integer.end() - 1;
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

} // end function less

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::operator<=(const HugeInteger& right) const
{
    return (*this == right || *this < right);
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::operator+(HugeInteger& op2)
{
    unsigned int op1Size = integer.size();
    unsigned int op2Size = op2.integer.size();
    unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

    HugeInteger sum(sumSize);

    string::iterator it1 = integer.begin();
    string::iterator it3 = sum.integer.begin();
    for (; it1 != integer.end(); ++it1, ++it3)
        *it3 = *it1;

    string::iterator it2 = op2.integer.begin();
    for (it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
        *it3 = (*it3 - '0') + (*it2 - '0') + '0';

    for (it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3)
        if (*it3 > '9')
        {
            (*it3) = (*it3 - '0') - 10 + '0';
            (*(it3 + 1)) = (*(it3 + 1) - '0') + 1 + '0';
        }

    if (*it3 == '0')
        sum.integer.pop_back();

    return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::operator-(HugeInteger& op2)
{
    HugeInteger zero;

    if (*this == op2)
        return zero;

    HugeInteger difference(*this);
    string::iterator it1 = difference.integer.begin();
    string::iterator it2 = op2.integer.begin();

    for (; it2 != op2.integer.end(); it1++, it2++)  //先減掉0的ascii-code才能做計算
    {
        *it1 = (*it1 - '0') - (*it2 - '0') + '0';
    }

    for (it1 = difference.integer.begin(); it1 != (difference.integer.end() - 1); it1++)
    {
        if (*it1 < 48)  //減法借位
        {
            (*(it1 + 1)) = (*(it1 + 1) - '0') - 1 + '0';
            (*it1) = (*it1 - '0') + 10 + '0';
        }
    }


    for (it1 = difference.integer.end() - 1; difference.integer.size() > 1 && *it1 == 48; it1--) //如果第一個數字是0，就尺寸減一
    {
        difference.integer.pop_back();
    }


    return difference;
} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::operator*(HugeInteger& op2)
{
    HugeInteger zero;
    if (isZero() || op2.isZero())
        return zero;

    unsigned int productSize = integer.size() + op2.integer.size();
    HugeInteger product(productSize);
    string::iterator it1 = product.integer.begin();
    string::iterator it2 = integer.begin();
    string::iterator it3 = op2.integer.begin();
    int i = 0;
    for (; it3 != op2.integer.end(); it3++)   //乘法計算
    {
        for (it2 = integer.begin(); it2 != integer.end(); it2++, it1++)
        {    
            *(it1) = (*(it1)-'0')+(*(it2)-'0') * (*(it3)-'0'); //先減掉0的asciicode，再做計算以免超過string的ascii-code最大值
            (*(it1 + 1)) += (*(it1)) / 10;  //邊計算邊進位,以免超過string的ascii-code最大值
            *(it1) = (*(it1)) % 10 + '0';
        }
        i += 1;
        it1 = product.integer.begin() + i;
    }
    for (it1 = product.integer.end() - 1; product.integer.size() > 1 && *it1 == 48; it1--) //如果第一個數字是0，就尺寸減一
    {
        product.integer.pop_back();
    }
    return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::operator/(HugeInteger& op2)
{
    HugeInteger zero;
    if (*this < op2)
        return zero;

    HugeInteger remender(*this);

    HugeInteger buffer(op2);

    unsigned int quotientSize = integer.size() - op2.integer.size();

    string::iterator it1 = buffer.integer.end() - 1;
    string::iterator it2 = op2.integer.end() - 1;

    HugeInteger ten(2);    //將buffer的首位與被除數貼齊 多的位數補0
    *(ten.integer.begin()) = 48;
    *(ten.integer.begin() + 1) = '1';
    while (buffer.integer.size() < integer.size())
        buffer = buffer * ten;

    if (remender < buffer)  //如果buffer>remainder   ， buffer就退一位,否則quotientSize++
    {
        buffer.divideByTen();
    }
    else
    {
        quotientSize++;
    }

    HugeInteger quotient(quotientSize);

    string::iterator it3 = quotient.integer.begin();

    for (int k = quotientSize - 1; k >= 0; k--)
    {
        while (!(remender < buffer))
        {
            remender = remender - buffer;

            *(it3 + k) += 1;

            if (remender.isZero())  //如果被除數是0,就回傳quotient
                return quotient;
        }

        if (buffer.integer.size() > 0)  //如果buffer>remainder   ， buffer就退一位
            buffer.divideByTen();
    }

    return quotient;

} // end function divide

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::operator%(HugeInteger& op2)
{
    HugeInteger quotient = (*this) / op2;
    HugeInteger product = quotient * op2;
    HugeInteger remainder = (*this) - product;
    return remainder;
}

// convert a string of decimal digits into a HugeInteger
void HugeInteger::convert(string& str)
{
    integer.resize(str.size());
    string::iterator it1 = integer.end() - 1;
    string::iterator it2 = str.begin();
    for (; it2 != str.end(); --it1, ++it2)
        *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
    for (string::iterator it = integer.begin(); it != integer.end(); ++it)
        if (*it != '0')
            return false;

    return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
    string::iterator it = integer.begin();
    string::iterator it2 = it;
    for (++it2; it2 != integer.end(); ++it, ++it2)
        *it = *it2;
    integer.pop_back();
}

// overloaded output operator
ostream& operator<<(ostream& output, const HugeInteger& hugeInteger)
{
    string::const_iterator it = hugeInteger.integer.end() - 1;

    for (; it != hugeInteger.integer.begin() - 1; --it)
        if (*it <= '9')
            output << *it;

    return output; // enables cout << x << y;
} // end function output