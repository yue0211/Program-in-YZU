#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( char( *program )[ 100 ], int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( char sourceLine[] );

// deletes all string constants from sourceLine
void delStrConsts( char sourceLine[] );

// deletes all character constants from sourceLine
void delCharConsts( char sourceLine[] );

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers );

// stores all non-keyword strings in the array identifiers into a text file
void store( char ( *identifiers )[ 32 ], int numIdentifiers );

// returns true if and only if str is a C++ keyword
bool keyword( char str[] );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( char ( *identifiers )[ 32 ], int pos );

const char keywords[][ 20 ] = { "auto", "break", "case", "char", "const",
								"continue", "default", "define","do", "double",
								"else", "enum", "extern", "float", "for",
								"goto", "if", "int", "long", "register",
								"return", "short", "signed", "sizeof",
								"static", "struct", "switch", "typedef",
								"union", "unsigned", "void", "volatile",
								"while", "bool", "catch", "class",
								"const_cast", "delete", "dynamic_cast",
								"explicit", "false", "friend", "inline",
								"mutable", "namespace", "new", "operator",
								"private", "protected", "public",
								"reinterpret_cast", "static_cast", "template",
								"this", "throw", "true", "try", "typeid",
								"typename", "using", "virtual", "include" };

int main()
{
	char ( *program )[ 100 ] = new char[ 500 ][ 100 ]();
	int numLines = 0;

	// reads in a C++ program from a cpp file, and put it to the array program
	load( program, numLines );

	char ( *identifiers )[ 32 ] = new char[ 500 ][ 32 ]();
	int numIdentifiers = 0;

	for( int i = 0; i < numLines; i++ )
	{
		delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
		delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
		delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

		if( strcmp( program[ i ], "" ) != 0 )
		extractIdentifiers( program[ i ], identifiers, numIdentifiers );
		// extracts all identifiers from program[ i ], and put them into the array identifiers
	}

	// stores all non-keyword strings in the array identifiers into a text file
	store( identifiers, numIdentifiers );
	
	delete[] program;
	
	delete[] identifiers;
	
	system( "pause" );
}

// reads in a C++ program from a cpp file, and put it to the array program
void load( char( *program )[ 100 ], int &numLines )
{                                                             //讀取TEST的檔案 
		ifstream a("test.cpp", ios::in);
	
		while( a.getline(*(program+numLines), 100) )
		{
			numLines++;
		}
} 

// deletes the comment beginning with "//" from sourceLine if any
void delComment( char *sourceLine )
{
	for( int i = 0 ; i < 100 ; i++ )                        //刪註解 
	{
		if( sourceLine[i] == 47 && sourceLine[i+1] == 47 )
		{
			sourceLine[i] = 0;
			break;
		}
	} 
} 

// deletes all string constants from sourceLine
void delStrConsts( char sourceLine[] )
{
	int c(0);
	
	for( int i = 0 ; i < 100 ; i++ )                   //刪字串 
	{
		if( sourceLine[i] == 34 )
		{	
			for( int j = i+1; sourceLine[j] != 34; c++, j++ )
			{}
			
			for( ; i < 100; i++ )                        //將後面非字串的符號往前移，蓋掉字串 
			{
				sourceLine[i] = sourceLine[i+c+2];
			}
			
			for( int j(0); j < 100 ; j++ )        //將後面的字串搬到前面後  保險起見把後面變成空字元 
			{
				if( sourceLine[j] == 0 )                
				{
					for( j++; j < 100; j++ )            
					{
						sourceLine[j] = 0;
					}
					
					break;
				}
			}			
		}
	} 
} 

// deletes all character constants from sourceLine
void delCharConsts( char sourceLine[] )
{                                                              //刪字元 
	for( int i = 0 ; i < 100 ; i++ )                           //將後面非字串的符號往前移，蓋掉字串 
	{
		if( sourceLine[i] == 39 && sourceLine[i + 2] == 39 )
		{	
			for( int j = i; j < 100; j++ )
			{
				sourceLine[j] = sourceLine[j+3];
			}			
		}
	} 
} 

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers )
{                
	for( int i(0) ; sourceLine[i] != 0; i++ )          //將識別字(A~Z a~z 0~9 _)放到identifiers 
	{		
		if( (sourceLine[i] == 95) || (sourceLine[i] >= 65 && sourceLine[i] <= 90) || (sourceLine[i] >= 97 && sourceLine[i] <= 122) || (sourceLine[i] >= 48 && sourceLine[i] <= 57) ) 
		{
			identifiers[numIdentifiers][ 0 ] = sourceLine[i];
			
			i++;
			
			for( int j(1); (sourceLine[i] >= 48 && sourceLine[i] <= 57) || (sourceLine[i] >= 65 && sourceLine[i] <= 90) || (sourceLine[i] >= 97 && sourceLine[i] <= 122) || (sourceLine[i] == 95); i++, j++)
			{
				identifiers[numIdentifiers][ j ] = sourceLine[i];
				
			}			
		
			if( identifiers[numIdentifiers][ 0 ] >= 48 && identifiers[numIdentifiers][ 0 ] <= 57 ) //標示符第一個不能是數字 
			{
				for( int m(0); m < 32; m++ )
				{
					identifiers[numIdentifiers][m] = 0;
				}
			}						
			else
			{
				numIdentifiers++;
			}
		}	
	} 
} 

// stores all non-keyword strings in the array identifiers into a text file
void store( char ( *identifiers )[ 32 ], int numIdentifiers )
{	
	for( int i(0); i < numIdentifiers; i++ )
	{	
		if( keyword( identifiers[i] ) )     //如果為關鍵字 放空字元 
		{
			identifiers[i][0] = '\0';
		}
	}
	
	for( int i(0); i < numIdentifiers; i++ )    //如果標示符重複出現 放空字元
	{	
		if( duplicate( identifiers, i ) ) 
		{
			identifiers[i][0] = '\0';
		}
	}
	
	ofstream b;
 
	b.open("file.txt");
	
	for( int i(0); i < numIdentifiers; i++ )
	{
		if( identifiers[i][0] != '\0' )
		{
			b << identifiers[i] ;
	
			b << endl;
		}
	}
	 
	b.close();
} 

// returns true if and only if str is a C++ keyword
bool keyword( char str[] )
{	
	bool tf = true;
	
	for( int i(0); i < 62; i++ )
	{
		if( !strcmp( str, keywords[i]))    //檢查標示符是否為關鍵字 
		{
			tf = false;
			
			break;
		}
	}
	
	if( tf == 1 )
	{
		tf = 0;
	}
	else
	{
		tf = 1;
	}
				
	return tf;
} 

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( char ( *identifiers )[ 32 ], int pos )
{
	bool tf = true;
	
	for( int i(0); i < pos; i++ )
	{
		if( !strcmp( identifiers[pos], identifiers[i]) )  //檢查標示符是否重複出現 
		{
			tf = false;
			
			break;
		}
	}
	
	if( tf == 1 )
	{
		tf = 0;
	}
	else
	{
		tf = 1;
	}
		
	return tf;
} 
