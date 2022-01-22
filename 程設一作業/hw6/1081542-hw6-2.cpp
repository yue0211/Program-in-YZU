#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>

// returns true if and only if the specified huge integer is zero
bool isZero( int *hugeInt, int size );

void reset( int *&hugeInt, int &size );

// return true if and only if hugeInt1 == hugeInt2
bool equal( int *hugeInt1, int *hugeInt2, int size1, int size2 );

// a recursive function that returns true if and only if hugeInt1 == hugeInt2
// provided that size1 == size2
bool recursiveEqual( int *hugeInt1, int *hugeInt2, int last );

// returns true if and only if hugeInt1 < hugeInt2
bool less( int *hugeInt1, int *hugeInt2, int size1, int size2 );

// a recursive function that returns true if and only if hugeInt1 < hugeInt2
// provided that size1 == size2
bool recursiveLess( int *hugeInt1, int *hugeInt2, int last );

// minuend -= subtrahend
void subtractionAssignment( int *&minuend, int *subtrahend,
                            int &minuendSize, int subtrahendSize );

// product *= multiplicand
void multiplicationAssignment( int *multiplicand, int *&product,
                               int multiplicandSize, int &productSize );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int *dividend, int *divisor, int *&quotient, int *&remainder,
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize );

// hugeInt /= 10
void divideBy10( int *hugeInt, int &size );

const int arraySize = 200;

int main()
{
   int t, a, b;
   while( cin >> t >> a >> b )
   {
      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

      if( t == 1 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a == b )
         cout << "1\n";
      else if( a < b )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a % b != 0 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( ( a - b ) * static_cast< int >( log10( t ) ) > 99 )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         int *dividend = new int[ 1 ]();
         int *divisor = new int[ 1 ]();
         int *quotient = new int[ 1 ]();
         int *remainder = new int[ 1 ]();

         int dividendSize = 1;
         int divisorSize = 1;
         int quotientSize = 1;
         int remainderSize = 1;

         int temp = t;
         int *base = new int[ 10 ]();
         int baseSize = 0;
         while( temp > 0 )
         {
            base[ baseSize++ ] = temp % 10;
            temp /= 10;
         }

         dividend[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            multiplicationAssignment( base, dividend, baseSize, dividendSize );
            if( dividendSize > arraySize )
               break;
         }

         if( dividendSize > arraySize )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            divisor[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
               multiplicationAssignment( base, divisor, baseSize, divisorSize );

            int oneSize = 1;
            int *one = new int[ 1 ]();
            one[ 0 ] = 1;
            subtractionAssignment( dividend, one, dividendSize, oneSize );
            subtractionAssignment( divisor, one, divisorSize, oneSize );

            division( dividend, divisor, quotient, remainder,
                      dividendSize, divisorSize, quotientSize, remainderSize );

            if( quotientSize < 100 && isZero( remainder, remainderSize ) )
               for( int i = quotientSize - 1; i >= 0; i-- )
                  cout << quotient[ i ];
            else
               cout << "is not an integer with less than 100 digits.";
            cout << endl;
         }
      }
   }
}

// returns true if and only if the specified huge integer is zero
bool isZero( int *hugeInt, int size )
{
   if( size == 1 && hugeInt[ 0 ] == 0 )
      return true;
   return false;
}

void reset( int *&hugeInt, int &size )
{
   size = 1;
   delete[] hugeInt;
   hugeInt = new int[ 1 ]();
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( int *hugeInt1, int *hugeInt2, int size1, int size2 )
{
   if( size1 != size2 )
      return false;

   return recursiveEqual( hugeInt1, hugeInt2, size1 - 1 );
}

// a recursive function that returns true if and only if hugeInt1 == hugeInt2
// provided that size1 == size2
bool recursiveEqual( int *hugeInt1, int *hugeInt2, int last )
{
	if(hugeInt1[last]!=hugeInt2[last])
	{
		return false;
	}
	if(hugeInt1[last]==hugeInt2[last])
	{
		if(last==0)
		{
			return true;
		}
		else
		return recursiveEqual(hugeInt1,hugeInt2,last-1);
	}
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( int *hugeInt1, int *hugeInt2, int size1, int size2 )
{
   if( size1 < size2 )
      return true;
   if( size1 > size2 )
      return false;

   return recursiveLess( hugeInt1, hugeInt2, size1 - 1 );
}

// a recursive function that returns true if and only if hugeInt1 < hugeInt2
// provided that size1 == size2
bool recursiveLess( int *hugeInt1, int *hugeInt2, int last )
{
	if(hugeInt2[last]>hugeInt1[last])
	{
		return true;
	}
	if(hugeInt2[last]<hugeInt1[last])
	{
		return false;
	}
	if(hugeInt2[last]==hugeInt1[last])
	{
		if(last==0)
		{
			return false;
		}
		return recursiveLess(hugeInt1,hugeInt2,last-1 );
	}	
}

// minuend -= subtrahend
void subtractionAssignment( int *&minuend, int *subtrahend, int &minuendSize, int subtrahendSize )
{	
	int differenceSize=minuendSize;
	int *difference=new int[200]();
	for(int i=0;i<minuendSize;i++)
	{
		difference[i]=minuend[i];
	}
	for(int i=0;i<subtrahendSize;i++)
	{
		difference[i]-=subtrahend[i];
	}
	for(int i=0;i<differenceSize-1;i++)
	{
		if(difference[i]<0)
		{
			difference[i]+=10;
			difference[i+1]-=1;
		}
	}
	for(;differenceSize>1&&difference[differenceSize-1]==0;)
	{
		differenceSize--;
	}
	minuendSize=differenceSize;
	delete[] minuend;
	minuend=new int[200]();	
	for(int i=0;i<differenceSize;i++)
	{
		minuend[i]=difference[i];
	}
	delete[] difference;
}

// product *= multiplicand
void multiplicationAssignment( int *multiplicand, int *&product, int multiplicandSize, int &productSize )
{
	int moneySize;
	int *money=new int[200]();
	moneySize=multiplicandSize+productSize;
	int b=0,h=0;
	for(;h<productSize;)
	{ 
		for(int a=0;a<multiplicandSize;)
		{
			money[b]= money[b]+multiplicand[a]*product[h];
			a++;
			b++;
		}
		h++;
		b=h;
	} 
	for(int i=0;i<moneySize;i++)
	{
		money[i+1]=money[i+1]+money[i]/10;
		money[i]=money[i]%10;
	}
	for(;moneySize>1&&money[moneySize-1]==0;)
	{
		moneySize--;
	}
	productSize=moneySize;
	delete[] product;
	product=new int[200]();
	for(int i=0;i<moneySize;i++)
	{
		product[i]=money[i];
	}
	delete[] money;
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int *dividend, int *divisor, int *&quotient, int *&remainder,
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize )
{
   if( isZero( dividend, dividendSize ) )
   {
      reset( quotient, quotientSize );
      reset( remainder, remainderSize );
      return;
   }
   
	int i, n, k, bufferSize;

	remainderSize = dividendSize;


	int *buffer = new int[200]();

	delete[] quotient;

	quotient= new int[200]();

	delete[] remainder;

	remainder= new int[200]();

	for (i = 0; i < dividendSize; i++)
	{
		remainder[i] = dividend[i];
	}

	if (less(dividend, divisor,dividendSize,divisorSize))
	{
		quotientSize = 1;

		quotient[0] = 0;

		return;
	}

	n = dividendSize - divisorSize;

	for (i = divisorSize - 1; i >= 0; i--)
	{
		buffer[i + n] = divisor[i];
	}

	bufferSize = dividendSize;

	quotientSize = n;

	if (less(remainder, buffer,remainderSize,bufferSize))
	{
		divideBy10(buffer,bufferSize);
	}
	else
	{
		quotientSize++;
	}

	for (k = quotientSize - 1; k >= 0; k--)
	{
		while (!less(remainder, buffer,remainderSize,bufferSize))
		{
			subtractionAssignment(remainder,buffer,remainderSize,bufferSize);
			quotient[k]++;
			for (; remainderSize > 1 && remainder[remainderSize - 1] == 0; )
			{
				remainderSize--;
			}
		}

		if (less(remainder, buffer,remainderSize,bufferSize))
		{
			divideBy10(buffer,bufferSize);
		}
	}
	delete[] buffer; 
}

// hugeInt /= 10
void divideBy10( int *hugeInt, int &size )
{
   if( size == 1 )
      hugeInt[ 0 ] = 0;
   else
   {
      for( int i = 1; i < size; i++ )
         hugeInt[ i - 1 ] = hugeInt[ i ];

      size--;
      hugeInt[ size ] = 0;
   }
}
