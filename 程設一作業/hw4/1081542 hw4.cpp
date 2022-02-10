// Huge integer addition, subtraction, multiplication and division
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ios;
#include<cstring>
// enable user to input a positive huge integer
void input( istream &inFile, int hugeInt[], int &size );

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, int hugeInt1[], int hugeInt2[], int hugeInt3[],
              int hugeInt4[], int size1, int size2, int size3, int size4 );

// output the specified huge integer
void output( ostream &outFile, int hugeInt[], int size );

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size );

// return true if and only if hugeInt1 == hugeInt2
bool equal( int hugeInt1[], int hugeInt2[], int size1, int size2 );

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 );

// sum = addend + adder
void addition( int addend[], int adder[], int sum[], int addendSize, int adderSize, int &sumSize );

// difference = minuend - subtrahend
void subtraction( int minuend[], int subtrahend[], int difference[],
                  int minuendSize, int subtrahendSize, int &differenceSize );

// product = multiplicand * multiplier
void multiplication( int multiplicand[], int multiplier[], int product[],
                     int multiplicandSize, int multiplierSize, int &productSize );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize );
bool aa( int  buffer[], int remainder[], int  bufferSize, int remainderSize );



const int numTestCases = 22; // the number of test cases
const int arraySize = 200;

int main()
{
   system( "mode con cols=122" );

   ifstream inFile( "Test cases.txt", ios::in );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   ofstream outFile( "Result.txt", ios::out );

   // exit program if ofstream could not open file
   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }
   
   for( int i = 0; i < numTestCases; i++ )
   {
      int hugeInt1[ arraySize ] = {};
      int hugeInt2[ arraySize ] = {};
      int hugeInt3[ arraySize ] = {};
      int hugeInt4[ arraySize ] = {};
      int size1 = 1;
      int size2 = 1;
      int size3 = 1;
      int size4 = 1;

      input(inFile, hugeInt1, size1);
      input( inFile, hugeInt2, size2 );
      perform( cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3, size4 );
      perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3, size4 );
   }

   inFile.close();
   outFile.close();

   system( "pause" );
}

// enable user to input a positive huge integer
void input( istream &inFile, int hugeInt[], int &size )
{
   char numericString[ arraySize ];

   inFile >> numericString;

   size = strlen( numericString );
   for( int i = 0; i < size; ++i )
      hugeInt[ i ] = numericString[ size - i - 1 ] - '0';
}

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, int hugeInt1[], int hugeInt2[], int hugeInt3[],
              int hugeInt4[], int size1, int size2, int size3, int size4 )
{
   output( outFile, hugeInt1, size1 );
   output( outFile, hugeInt2, size2 );

   // hugeInt3 = hugeInt1 + hugeInt2
   addition( hugeInt1, hugeInt2, hugeInt3, size1, size2, size3 );
   output( outFile, hugeInt3, size3 );

   // if hugeInt1 < hugeInt2
   if( less( hugeInt1, hugeInt2, size1, size2 ) )
   {
      outFile << '-';
      // hugeInt3 = hugeInt2 - hugeInt1
      subtraction( hugeInt2, hugeInt1, hugeInt3, size2, size1, size3 );
      output( outFile, hugeInt3, size3 ); // outputs n2 - n1
   }
   else
   {
      // hugeInt3 = hugeInt1 - hugeInt2
      subtraction( hugeInt1, hugeInt2, hugeInt3, size1, size2, size3 );
      output( outFile, hugeInt3, size3 ); // outputs n1 - n2
   }

   // hugeInt3 = hugeInt1 * hugeInt2
   multiplication( hugeInt1, hugeInt2, hugeInt3, size1, size2, size3 );
   output( outFile, hugeInt3, size3 ); // outputs n1 * n2

   if( isZero( hugeInt2, size2 ) )
   {
      outFile << "DivideByZero!\n";
      outFile << "DivideByZero!\n";
   }
   else
   {
      division( hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3, size4 );
      output( outFile, hugeInt3, size3 );         // outputs n1 / n2
      output( outFile, hugeInt4, size4 );         // outputs n1 % n2
   }

   outFile << endl;
}

// output the specified huge integer
void output( ostream &outFile, int hugeInt[], int size )
{
   if( isZero( hugeInt, size ) )
      outFile << 0;
   else
      for( int i = size - 1; i >= 0; i-- )
         if( hugeInt[ i ] < 10 )
            outFile << hugeInt[ i ];

   outFile << endl;
}

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size )
{
   for( int i = 0; i < size; i++ )
      if( hugeInt[ i ] != 0 )
         return false;
   return true;
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( int hugeInt1[], int hugeInt2[], int size1, int size2 )
{
	
	if(size1==size2)
	{
		for(int i=size1-1;i>=0;)
		{
			if(hugeInt1[i]!=hugeInt2[i])
				return false;
			if(hugeInt1[i]==hugeInt2[i])
				i--;
		}
		return true;
	}
	return false;	
   
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 )
{
	if(size2>size1)                                   //size是位數長度 
  {
	return true;		
  }
	if(size1==size2)
	{
		for(int i=size1-1;i>=0&&hugeInt2[i]>=hugeInt1[i];i--)	
		{
			if(hugeInt2[i]>hugeInt1[i])
			return true;                                
		}                                          //位數相同時從第一個位數開始比 
	}
	return false;
	
}

// sum = addend + adder
void addition( int addend[], int adder[], int sum[], int addendSize, int adderSize, int &sumSize )
{
   sumSize = ( addendSize >= adderSize ) ? addendSize + 1 : adderSize + 1;

   for( int i = 0; i < addendSize; i++ )
      sum[ i ] = addend[ i ];

   for( int i = addendSize; i < sumSize; i++ )
      sum[ i ] = 0;

   for( int i = 0; i < adderSize; i++ )
      sum[ i ] += adder[ i ];

   for( int i = 0; i < sumSize - 1; i++ )
      if( sum[ i ] > 9 ) // carrying
      {
         sum[ i ] -= 10;
         sum[ i + 1 ]++;
      }

   if( sum[ sumSize - 1 ] == 0 )
      sumSize--;
}

// difference = minuend - subtrahend
void subtraction( int minuend[], int subtrahend[], int difference[],
                  int minuendSize, int subtrahendSize, int &differenceSize )
{
	differenceSize= minuendSize;
	for(int i =0;i<minuendSize;i++)
	{
		difference[i]=minuend[i];
	}
	for(int i =subtrahendSize;i<minuendSize;i++)
	{
		subtrahend[i]=0;
	}
	for(int i=0;i<differenceSize;i++)
	{
		difference[i]-=subtrahend[i];
	}
	for(int i=0;i<differenceSize-1;i++)
	{
		if(difference[i]<0)
		{
			difference[i+1]-=1;
			difference[i]+=10;
		}
	}
	for(int i=differenceSize-1;difference[i]==0;)
	{
			differenceSize--;
			i--;
	}
}
// product = multiplicand * multiplier
void multiplication( int multiplicand[], int multiplier[], int product[],
                     int multiplicandSize, int multiplierSize, int &productSize )
{
	productSize=multiplicandSize+multiplierSize;
	for(int i =0;i<productSize;i++)
	{
		product[i]=0;
	}
	int i=0,b=0;
	for(;i<multiplierSize;)
  {
	
	for(int a=0;a<multiplicandSize;)
	{
		product[b]=product[b]+multiplicand[a]*multiplier[i];
		a++;
		b++;
	}
		i++;
	    b=i;
  }
  	for(int i =0;i<productSize;i++)
	{
		product[i+1]=product[i+1]+product[i]/10;
		product[i]=product[i]%10;
	} 
	for(int i=productSize-1;product[i]==0;)
	{
		productSize--;
		i--;
	}
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize )
{
	
	// buffer 用來存放每個步驟所更新的除數 buffer的所有元素初始化為0， bufferSize 用來表示陣列buffer裡面真實存放的數值總位數 
	int i, n, k, buffer[ 200 ]={}, bufferSize, c = 0;
	
	// 先將餘數總位數與會使用到的每個元素設為與被除數相同 因為餘數是被除數除不盡的結果 
	remainderSize = dividendSize;
	
	for( i = 0; i < dividendSize; i++ )
	{
		remainder[ i ] = dividend[ i ];
	}
	
	// 如果被除數為0 則餘數和商都為0  
	if( dividendSize == 1 && dividend[ 0 ] == 0 )
	{
		quotientSize = 1;
		quotient[0] = 0;
		
		remainderSize = 1;
		remainder[0] = 0;
		
		return;
	}
	
	// 如果除數位數大於被除數 則商為0 
	if( dividendSize < divisorSize )
	{
		quotientSize = 1;
		
		quotient[ 0 ] = 0;
	}
	
	// 如果除數位數小於等於於被除數
	else
	{
		// n 用來將除數的位數補到和被除數一樣 方便相減的計算 
		n = dividendSize - divisorSize;
		
		// 先將 bufferSize 設為除數的總位數加補上的0的個數 
		bufferSize = n + divisorSize;
		
		// 將除數後面到和被除數位數一樣為止補0(因為buffer每個元素初始值都是0)  方便相減的計算 
		for( i = divisorSize - 1; i >= 0 ; i-- )
		{
			buffer[ n + i ] = divisor[ i ]; 
		}
		
		// 商的位數最少是補0的個數 
		quotientSize = n;
		
		// 如果補0後的除數大於被除數 則將除數項右移一位(除以10) 並且將除數的位數變小一位 
		for( i = dividendSize - 1; i >= n && dividend[ i ] <=buffer[ i ] && c == 0; i-- )
		{
			if( dividend[ i ] < buffer[ i ] )
			{
				for( int j = 0; j <= 198; j++ )
				{
					buffer[ j ] = buffer[ j + 1 ];
				}
				
				c++;
				
				if( c == 1 )
				{
					bufferSize --;
				}
				
			}
			
		}
		
		// 如果補0後的除數小於等於被除數 則將商的位數加上一位 
		if( c == 0 )
		{
			quotientSize ++;
		}
		
		//  將商數陣列會使用到的元素初始化為0 
		for( i = 0; i < quotientSize; i++ )
		{
			quotient[ i ] = 0;
		}
		
		//  k 代表商的每個位數的值(也就是每次移位前 暫時被除數可以減掉幾次暫時除數而不為負) 
		for( k = quotientSize - 1; k >= 0; k-- )
		{
			// 當暫時除數小於等於暫時被除數時  時被除數減掉一次暫時除數
			while( aa( buffer, remainder, bufferSize, remainderSize) == 0 )
			{
				for( i = 0; i < dividendSize; i++ )
				{
					remainder[ i ] = remainder[ i ] - buffer[ i ];
					
					// 果因為相減而影響暫時被除數的元素值為負時 讓為負元素跟大一位元素借位 
					if( remainder[ i ] < 0 )
					{
						remainder[ i + 1 ] --;
						remainder[ i ] = remainder[ i ] + 10;
						
						// 如果因為相減而影響暫時被除數的總位數時 調整暫時被除數的總位數 
						for( ; remainderSize > 1 && remainder[ remainderSize - 1 ] == 0; )
						{
							remainderSize --;
						}
						
					}
					
				}
				
				// 暫時被除數與暫時除數每相減完一次 k值(該位數的商值)增加1 
				quotient[ k ]++;
				
//				// 如果暫時被除數的總位數不為真時(前面有0) 調整暫時被除數的總位數
				for( ; remainderSize > 1 && remainder[ remainderSize - 1 ] == 0; )
				{
					remainderSize --;
				}
				
			}
			
			//  如果暫時被除數不夠減暫時除數 則將暫時除數變小一位(除以10 位數減1) 計算下一位的商值 
			if( aa( buffer, remainder, bufferSize, remainderSize) == 1 )
			{
				for( c = 0; c <= 198; c++ )
				{
					buffer[ c ] = buffer[ c + 1 ];
				}
				
				bufferSize --;
				
			}
			
		}
		
	}
	
}

// aa 用來檢查暫時除數和暫時被除數的大小， 當暫時除數大於暫時被除數時 回傳值為真， 當暫時除數小於等於暫時被除數時 回傳值為假 
bool aa( int  buffer[], int remainder[], int  bufferSize, int remainderSize )
{
	int i;
	
	// 如果暫時除數的位數比暫時被除數的位數多 則代表暫時除數大於暫時被除數 回傳值為真  
	if(  remainderSize < bufferSize )
	{
		return true;
	}
		
	// 如果兩數位數相同 則比較每個位數的大小
	if(  remainderSize == bufferSize )
	{
		for( i =  remainderSize - 1; i >= 0 && remainder[ i ] <= buffer[ i ]; i-- )
		{
			if( remainder[ i ] < buffer[ i ] )
			{
				return true;
			}
		}
			
	}
	
	return false;
}
