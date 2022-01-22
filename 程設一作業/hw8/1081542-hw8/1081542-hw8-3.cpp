#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace::std;

// reads in a C++ program from a cpp file, and put it to the vector program
void load(vector< string >& program);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(string& sourceLine);

// deletes all string constants from sourceLine
void delStrConsts(string& sourceLine);

// deletes all character constants from sourceLine
void delCharConsts(string& sourceLine);

// deletes the first identifier from sourceLine, and returns it
string delFirstIdentifier(string& sourceLine);

// stores all non-keyword strings in the vector identifiers into a text file
void store(vector< string >& identifiers);

// return true if and only if "str" is a C++ keyword
bool keyword(string str);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(vector< string >& identifiers, int pos);

const string keywords[] = { "auto", "break", "case", "char", "const",
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
	vector< string > program;

	// reads in a C++ program from a cpp file, and put it to the vector program
	load(program);

	vector< string > identifiers;
	string firstIdentifier;
	string null;

	for (unsigned int i = 0; i < program.size(); i++)
	{
		delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
		delStrConsts(program[i]); // deletes all string constants from program[ i ]
		delCharConsts(program[i]); // deletes all character constants from program[ i ]

		//extracts all identifiers from program[ i ], and put them into the vector identifiers
		while ((firstIdentifier = delFirstIdentifier(program[i])) != null)
			identifiers.push_back(firstIdentifier);
	}

	// stores all non-keyword strings in the vector identifiers into a text file
	store(identifiers);

	system("pause");
}

// reads in a C++ program from a cpp file, and put it to the vector program
void load(vector< string >& program)
{
	ifstream a("test.cpp", ios::in);          //讀取TEST的檔案  

	string temp;

	while (getline(a, temp) && !a.eof())
	{
		program.push_back(temp);
	}
}

// deletes the comment beginning with "//" from sourceLine if any
void delComment(string& sourceLine)
{
	for ( unsigned int i(0); i < sourceLine.size(); i++)              //刪註解 
	{
		if (sourceLine.at(i) == 47 && sourceLine.at(i + 1) == 47)
		{
			sourceLine.erase(i, sourceLine.size() - i);              //從i刪到最後 

			break;
		}
	}
}

// deletes all string constants from sourceLine
void delStrConsts(string& sourceLine)
{
	int c(2);

	for (unsigned int i(0); i < sourceLine.size(); i++)
	{
		if (sourceLine.at(i) == 34)                                 //刪字串 
		{
			for (int j(i + 1); sourceLine.at(j) != 34; c++, j++)
			{
			}

			sourceLine.erase(i, c);

			c = 2;       //兩個雙引號 

			i--;
		}
	}
}

// deletes all character constants from sourceLine
void delCharConsts(string& sourceLine)
{
	for (unsigned int i(0); i < sourceLine.size(); i++)          //刪字元 
	{
		if (sourceLine.at(i) == 39 && sourceLine.at(i + 2) == 39)
		{
			sourceLine.erase(i, 3);

			i--;
		}
	}
}

// deletes the first identifier from sourceLine, and returns it
string delFirstIdentifier(string& sourceLine)
{
	string temp;

	int c(1);

	for ( int i(0); sourceLine[i] != 0; i++ )
	{
		if ((sourceLine[i] == 95) || (sourceLine[i] >= 65 && sourceLine[i] <= 90) || (sourceLine[i] >= 97 && sourceLine[i] <= 122) || (sourceLine[i] >= 48 && sourceLine[i] <= 57))
		{
			int j(i);

			temp += sourceLine[i];

			i++;

			for (; (sourceLine[i] >= 48 && sourceLine[i] <= 57) || (sourceLine[i] >= 65 && sourceLine[i] <= 90) || (sourceLine[i] >= 97 && sourceLine[i] <= 122) || (sourceLine[i] == 95); i++, c++)
			{
				temp += sourceLine[i];
			}

			sourceLine.erase(j, c);

			if (temp[0] >= 48 && temp[0] <= 57)       //如果第一個是數字的話就清空  
			{
				temp.clear();                   

				return temp;
			}
			else
			{
				return temp;
			}
		}
	}

	return temp;
}

// stores all non-keyword strings in the vector identifiers into a text file
void store(vector< string >& identifiers)
{
	for (unsigned int i(0); i < identifiers.size(); i++)
	{
		if (keyword(identifiers[i]))                  //如果為關鍵字 就清空 
		{
			identifiers.erase(identifiers.begin() + i);

			i--;
		}
	}

	for (unsigned int i(0); i < identifiers.size(); i++)       //如果標示符重複出現 就清空 
	{
		if (duplicate(identifiers, i))
		{
			identifiers.erase(identifiers.begin() + i);

			i--;
		}
	}

	ofstream b;

	b.open("file.txt");

	for (unsigned int i(0); i < identifiers.size(); i++)
	{
		b << identifiers.at(i);

		b << endl;
	}

	b.close();
}

// return true if and only if "str" is a C++ keyword
bool keyword(string str)
{
	bool tf = false;

	for (int i(0); i < 62; i++)          //檢查是否為keyword  
	{
		if (str == keywords[i])
		{
			tf = true;

			break;
		}
	}

	return tf;
}

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(vector< string >& identifiers, int pos)
{
	bool tf = false;

	for (int i(0); i < pos; i++)
	{
		if (identifiers[pos] == identifiers[i])         //檢查標示符是否重複出現  
		{
			tf = true;

			break;
		}
	}

	return tf;
}
