#include"Pokemon.h"
#include"rlutil.h"
#include<iostream>
#include<random>
#include<time.h>
#include<fstream>
#include<string>
using namespace std;
using namespace rlutil;
#define waitkey rlutil::anykey("Press any key to clean picture...\n")

Pokemon::WrongFail::WrongFail()
	:exception("\n捕捉失敗")
{
}
Pokemon ::Pokemon()
{
	track = 0;
}
int Pokemon::getTrack()
{
	return track;
}
void Pokemon::BeforeCatch()
{
	string choice;
	setColor(10);
	locate(3, 26);
	cout << "\n是否要捕捉此隻寶可夢? ( y or n):";
	while (cin >> choice)
	{
		if (choice == "n")
		{
			track = 0;
			return;
		}
		else if (choice == "y")
		{
			srand(time(0));
			int number = 1 + rand() % 2;
			if (number == 1)
			{
				cout << "\n捕捉成功\n";
				track = 1;
			}
			else if (number == 2)
			{
				track = 0;
				for (int i = 0; i < 24; i++)
					for (int j = 0; j < 600; j++)
						pokemon[i][j] = {};
				throw WrongFail();   //例外處理
			}
			break;
		}
		else
			cout << "\n輸入錯誤,請重新輸入:";
	}

}
string Pokemon::getname()
{
	return name;
}
int Pokemon::getSpeed()
{
	return Speed;
}
int Pokemon::getAttack()
{
	return ATK;
}
int Pokemon::getAbility()
{
	return Ability ;
}
string Pokemon::getType()
{
	return type;
}
int Pokemon::getDefence()
{
	return DEF;
}
int Pokemon::getHp()
{
	return Hp;
}
int Pokemon::getMaxHp()
{
	return MaxHp;
}
void Pokemon::originalStatus()
{
	Hp = MaxHp;
	ATK = MaxAtk;
	DEF = MaxDef;
	Speed = MaxSpeed;
}
void Pokemon::setHp(int attack)
{
	Hp -= attack;
}
void Pokemon::setHp2(int rise)
{
	Hp += rise;
}
void Pokemon::printpicture()   //印寶可夢圖像
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 600; j++)
			cout << pokemon[i][j];
		cout << endl;
	}
}
void Pokemon::printpicture2()  //印寶可夢圖像
{
	int x=55, y=0;
	
	for (int i = 0; i < 24; i++)
	{
			locate(x, ++y);
			cout << pokemon[i];
	}
}
void Pokemon::printpicture3()  //印寶可夢能力+圖像
{
	int x = 110,y=0;
	for (int i = 0; i < 24; i++)
	{
		locate(x, ++y);
		cout << pokemon[i];
	}
	setColor(10);
	locate(x,y+2);
	cout << "屬性( Type ):" << type;
	locate(x, y+4);
	cout << "名稱( Name ):" << name;
	locate(x, y+6); cout << "血量:" << Hp;
	locate(x, y+8); cout << "攻擊力:" << ATK;
	locate(x, y+10); cout << "防守力:" << DEF;
	locate(x, y+12); cout << "速度值:" << Speed;
	locate(x, y + 14);
	waitkey;
	x = 110, y = 0;
	for (int i = 0; i < 40; i++)
	{
		locate(x, ++y);
		cout << "                                                        ";
	}

}
void Pokemon::cleanpicture()  // 將存寶可夢圖片的地方歸0
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 600; j++)
			pokemon[i][j] = {};
	}
}
void Pokemon::printability()    //印寶可夢的屬性
{
	setColor(14); locate(45, 6);
	cout << "屬性( Type ):" << type;
	locate(45, 9); cout << "名稱( Name ):" << name;
	locate(45, 12); cout << "血量:" << Hp;
	locate(45, 15); cout << "攻擊力:" << ATK;
	locate(45, 18); cout << "防守力:" << DEF;
	locate(45, 21); cout << "速度值:" << Speed;
}
void Pokemon::printability2()  //印寶可夢能力
{
	setColor(14);
	cout << "\n\n屬性( Type ):" << type
	 << "\n名稱( Name ):"<<name
	 << "\n血量:"<< Hp<< "\n攻擊力:"<<ATK
	<< "\n防守力:"<<DEF<< "\n速度值:"<<Speed;
}
void Pokemon::printability3()//印寶可夢能力
{
	setColor(14); locate(55, 26);
	cout << "屬性( Type ):" << type; locate(55, 27);
	cout << "名稱( Name ):" << name; locate(55, 28);
	cout << "血量:" << Hp;locate(55, 29);
	cout<< "攻擊力:" << ATK;  locate(55, 30);
	cout << "防守力:" << DEF; locate(55, 31);
	cout<< "速度值:" << Speed; locate(55, 32);
}

void GrassPokemon::setData()  //設定寶可夢數值
{
	Hp1.push_back(50);Hp1.push_back(65);Hp1.push_back(80);
	ATK1.push_back(16); ATK1.push_back(19); ATK1.push_back(22);
	DEF1.push_back(7); DEF1.push_back(9); DEF1.push_back(11);
	Speed1.push_back(4); Speed1.push_back(6); Speed1.push_back(8);
	Ability1.push_back(1); Ability1.push_back(1); Ability1.push_back(1);
}
void FirePokemon::setData()
{
	Hp1.push_back(48); Hp1.push_back(62); Hp1.push_back(78);
	ATK1.push_back(17); ATK1.push_back(20); ATK1.push_back(23);
	DEF1.push_back(6); DEF1.push_back(8); DEF1.push_back(10);
	Speed1.push_back(6); Speed1.push_back(8); Speed1.push_back(10);
	Ability1.push_back(2); Ability1.push_back(2); Ability1.push_back(2);
}

void WaterPokemon::setData()
{
	Hp1.push_back(46); Hp1.push_back(60); Hp1.push_back(76);
	ATK1.push_back(16); ATK1.push_back(18); ATK1.push_back(20);
	DEF1.push_back(7); DEF1.push_back(9); DEF1.push_back(11);
	Speed1.push_back(4); Speed1.push_back(6); Speed1.push_back(8);
	Ability1.push_back(3); Ability1.push_back(3); Ability1.push_back(3);
}
void BugPokemon1::setData()
{
	Hp1.push_back(46); Hp1.push_back(58); Hp1.push_back(70);
	ATK1.push_back(16); ATK1.push_back(16); ATK1.push_back(20);
	DEF1.push_back(4); DEF1.push_back(7); DEF1.push_back(10);
	Speed1.push_back(5); Speed1.push_back(3); Speed1.push_back(7);
	Ability1.push_back(4); Ability1.push_back(4); Ability1.push_back(4);
}
void BugPokemon2::setData()
{
	Hp1.push_back(47); Hp1.push_back(60); Hp1.push_back(72);
	ATK1.push_back(16); ATK1.push_back(18); ATK1.push_back(19);
	DEF1.push_back(4); DEF1.push_back(6); DEF1.push_back(8);
	Speed1.push_back(5); Speed1.push_back(4); Speed1.push_back(7);
	Ability1.push_back(5); Ability1.push_back(5); Ability1.push_back(5);
}
void FlyingPokemon1::setData()
{
	Hp1.push_back(53); Hp1.push_back(69); Hp1.push_back(76);
	ATK1.push_back(15); ATK1.push_back(18); ATK1.push_back(21);
	DEF1.push_back(5); DEF1.push_back(7); DEF1.push_back(9);
	Speed1.push_back(6); Speed1.push_back(7); Speed1.push_back(10);
	Ability1.push_back(6); Ability1.push_back(6); Ability1.push_back(6);
}
void NormalPokemon::setData()
{
	Hp1.push_back(53); Hp1.push_back(72); 
	ATK1.push_back(16); ATK1.push_back(20); 
	DEF1.push_back(8); DEF1.push_back(10); 
	Speed1.push_back(7); Speed1.push_back(10); 
	Ability1.push_back(0); Ability1.push_back(0); 
}
void FlyingPokemon2::setData()
{
	Hp1.push_back(52); Hp1.push_back(74); 
	ATK1.push_back(17); ATK1.push_back(21); 
	DEF1.push_back(5); DEF1.push_back(8); 
	Speed1.push_back(7); Speed1.push_back(10); 
	Ability1.push_back(7); Ability1.push_back(7); 
}
void PoisonPokemon1::setData()
{
	Hp1.push_back(53); Hp1.push_back(73); 
	ATK1.push_back(16); ATK1.push_back(21); 
	DEF1.push_back(6); DEF1.push_back(9); 
	Speed1.push_back(5); Speed1.push_back(8); 
	Ability1.push_back(8); Ability1.push_back(8); 
}
void ElectricPokemon::setData()
{
	Hp1.push_back(52); Hp1.push_back(68); 
	ATK1.push_back(17); ATK1.push_back(20); 
	DEF1.push_back(5); DEF1.push_back(9); 
	Speed1.push_back(9); Speed1.push_back(11); 
	Ability1.push_back(9); Ability1.push_back(9); 
}
void GroundPokemon::setData()
{
	Hp1.push_back(56); Hp1.push_back(76); 
	ATK1.push_back(16); ATK1.push_back(19); 
	DEF1.push_back(7); DEF1.push_back(10); 
	Speed1.push_back(4); Speed1.push_back(6);
	Ability1.push_back(10); Ability1.push_back(10);
}
void PoisonPokemon2::setData()
{
	Hp1.push_back(55); Hp1.push_back(70); Hp1.push_back(85);
	ATK1.push_back(16); ATK1.push_back(19); ATK1.push_back(21);
	DEF1.push_back(7); DEF1.push_back(9); DEF1.push_back(11);
	Speed1.push_back(4); Speed1.push_back(6); Speed1.push_back(8);
	Ability1.push_back(11); Ability1.push_back(11); Ability1.push_back(11);
}
void PoisonPokemon3::setData()
{
	Hp1.push_back(52); 
	ATK1.push_back(17); 
	DEF1.push_back(6);
	Speed1.push_back(5); 
	Ability1.push_back(12); 
}
void GrassPokemon::choice()   //決定寶可夢種類
{
	srand(time(0));
	int choice = 1 + rand() % 3;
	string picture;
	int i = 0;
	if (choice == 1)
	{
		ifstream inFile("001.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name1);
		Hp = Hp1[0];
		ATK = ATK1[0];
		DEF = DEF1[0];
		Speed = Speed1[0];
		Ability = Ability1[0];
	}
	else if (choice == 2)
	{
		ifstream inFile("002.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name2);
		Hp = Hp1[1];
		ATK = ATK1[1];
		DEF = DEF1[1];
		Speed = Speed1[1];
		Ability = Ability1[1];
	}
	else
	{
		ifstream inFile("003.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name3);
		Hp = Hp1[2];
		ATK = ATK1[2];
		DEF = DEF1[2];
		Speed = Speed1[2];
		Ability = Ability1[2];
	}
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}

void FirePokemon::choice()
{
	srand(time(0));
	int choice = 1 + rand() % 3;
	string picture;
	int i = 0;
	if (choice == 1)
	{
		ifstream inFile("004.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name1);
		Hp = Hp1[0];
		ATK = ATK1[0];
		DEF = DEF1[0];
		Speed = Speed1[0];
		Ability = Ability1[0];
	}
	else if (choice == 2)
	{
		ifstream inFile("005.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name2);
		Hp = Hp1[1];
		ATK = ATK1[1];
		DEF = DEF1[1];
		Speed = Speed1[1];
		Ability = Ability1[1];
	}
	else
	{
		ifstream inFile("006.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name3);
		Hp = Hp1[2];
		ATK = ATK1[2];
		DEF = DEF1[2];
		Speed = Speed1[2];
		Ability = Ability1[2];
	}
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}
void WaterPokemon::choice()
{
	srand(time(0));
	int choice = 1 + rand() % 3;
	string picture;
	int i = 0;
	if (choice == 1)
	{
		ifstream inFile("007.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name1);
		Hp = Hp1[0];
		ATK = ATK1[0];
		DEF = DEF1[0];
		Speed = Speed1[0];
		Ability = Ability1[0];
	}
	else if (choice == 2)
	{
		ifstream inFile("008.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name2);
		Hp = Hp1[1];
		ATK = ATK1[1];
		DEF = DEF1[1];
		Speed = Speed1[1];
		Ability = Ability1[1];
	}
	else
	{
		ifstream inFile("009.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name3);
		Hp = Hp1[2];
		ATK = ATK1[2];
		DEF = DEF1[2];
		Speed = Speed1[2];
		Ability = Ability1[2];
	}
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}
void BugPokemon1::choice()
{
	srand(time(0));
	int choice = 1 + rand() % 3;
	string picture;
	int i = 0;
	if (choice == 1)
	{
		ifstream inFile("010.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name1);
		Hp = Hp1[0];
		ATK = ATK1[0];
		DEF = DEF1[0];
		Speed = Speed1[0];
		Ability = Ability1[0];
	}
	else if (choice == 2)
	{
		ifstream inFile("011.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name2);
		Hp = Hp1[1];
		ATK = ATK1[1];
		DEF = DEF1[1];
		Speed = Speed1[1];
		Ability = Ability1[1];
	}
	else
	{
		ifstream inFile("012.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name3);
		Hp = Hp1[2];
		ATK = ATK1[2];
		DEF = DEF1[2];
		Speed = Speed1[2];
		Ability = Ability1[2];
	}
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}
void BugPokemon2::choice()
{
	srand(time(0));
	int choice = 1 + rand() % 3;
	string picture;
	int i = 0;
	if (choice == 1)
	{
		ifstream inFile("013.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name1);
		Hp = Hp1[0];
		ATK = ATK1[0];
		DEF = DEF1[0];
		Speed = Speed1[0];
		Ability = Ability1[0];
	}
	else if (choice == 2)
	{
		ifstream inFile("014.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name2);
		Hp = Hp1[1];
		ATK = ATK1[1];
		DEF = DEF1[1];
		Speed = Speed1[1];
		Ability = Ability1[1];
	}
	else
	{
		ifstream inFile("015.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name3);
		Hp = Hp1[2];
		ATK = ATK1[2];
		DEF = DEF1[2];
		Speed = Speed1[2];
		Ability = Ability1[2];
	}
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}
void FlyingPokemon1::choice()
{
	srand(time(0));
	int choice = 1 + rand() % 3;
	string picture;
	int i = 0;
	if (choice == 1)
	{
		ifstream inFile("016.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name1);
		Hp = Hp1[0];
		ATK = ATK1[0];
		DEF = DEF1[0];
		Speed = Speed1[0];
		Ability = Ability1[0];
	}
	else if (choice == 2)
	{
		ifstream inFile("017.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name2);
		Hp = Hp1[1];
		ATK = ATK1[1];
		DEF = DEF1[1];
		Speed = Speed1[1];
		Ability = Ability1[1];
	}
	else
	{
		ifstream inFile("018.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name3);
		Hp = Hp1[2];
		ATK = ATK1[2];
		DEF = DEF1[2];
		Speed = Speed1[2];
		Ability = Ability1[2];
	}
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}
void NormalPokemon::choice()
{
	srand(time(0));
	int choice = 1 + rand() % 2;
	string picture;
	int i = 0;
	if (choice == 1)
	{
		ifstream inFile("019.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name1);
		Hp = Hp1[0];
		ATK = ATK1[0];
		DEF = DEF1[0];
		Speed = Speed1[0];
		Ability = Ability1[0];
	}
	else if (choice == 2)
	{
		ifstream inFile("020.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name2);
		Hp = Hp1[1];
		ATK = ATK1[1];
		DEF = DEF1[1];
		Speed = Speed1[1];
		Ability = Ability1[1];
	}
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}
void FlyingPokemon2::choice()
{
	srand(time(0));
	int choice = 1 + rand() % 2;
	string picture;
	int i = 0;
	if (choice == 1)
	{
		ifstream inFile("021.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name1);
		Hp = Hp1[0];
		ATK = ATK1[0];
		DEF = DEF1[0];
		Speed = Speed1[0];
		Ability = Ability1[0];
	}
	else if (choice == 2)
	{
		ifstream inFile("022.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name2);
		Hp = Hp1[1];
		ATK = ATK1[1];
		DEF = DEF1[1];
		Speed = Speed1[1];
		Ability = Ability1[1];
	}
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}
void PoisonPokemon1::choice()
{
	srand(time(0));
	int choice = 1 + rand() % 2;
	string picture;
	int i = 0;
	if (choice == 1)
	{
		ifstream inFile("023.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name1);
		Hp = Hp1[0];
		ATK = ATK1[0];
		DEF = DEF1[0];
		Speed = Speed1[0];
		Ability = Ability1[0];
	}
	else if (choice == 2)
	{
		ifstream inFile("024.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name2);
		Hp = Hp1[1];
		ATK = ATK1[1];
		DEF = DEF1[1];
		Speed = Speed1[1];
		Ability = Ability1[1];
	}
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}
void ElectricPokemon::choice()
{
	srand(time(0));
	int choice = 1 + rand() % 2;
	string picture;
	int i = 0;
	if (choice == 1)
	{
		ifstream inFile("025.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name1);
		Hp = Hp1[0];
		ATK = ATK1[0];
		DEF = DEF1[0];
		Speed = Speed1[0];
		Ability = Ability1[0];
	}
	else if (choice == 2)
	{
		ifstream inFile("026.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name2);
		Hp = Hp1[1];
		ATK = ATK1[1];
		DEF = DEF1[1];
		Speed = Speed1[1];
		Ability = Ability1[1];
	}
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}
void GroundPokemon::choice()
{
	srand(time(0));
	int choice = 1 + rand() % 2;
	string picture;
	int i = 0;
	if (choice == 1)
	{
		ifstream inFile("027.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name1);
		Hp = Hp1[0];
		ATK = ATK1[0];
		DEF = DEF1[0];
		Speed = Speed1[0];
		Ability = Ability1[0];
	}
	else if (choice == 2)
	{
		ifstream inFile("028.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name2);
		Hp = Hp1[1];
		ATK = ATK1[1];
		DEF = DEF1[1];
		Speed = Speed1[1];
		Ability = Ability1[1];
	}
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}
void PoisonPokemon2::choice()
{
	srand(time(0));
	int choice = 1 + rand() % 3;
	string picture;
	int i = 0;
	if (choice == 1)
	{
		ifstream inFile("029.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name1);
		Hp = Hp1[0];
		ATK = ATK1[0];
		DEF = DEF1[0];
		Speed = Speed1[0];
		Ability = Ability1[0];
	}
	else if (choice == 2)
	{
		ifstream inFile("030.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name2);
		Hp = Hp1[1];
		ATK = ATK1[1];
		DEF = DEF1[1];
		Speed = Speed1[1];
		Ability = Ability1[1];
	}
	else
	{
		ifstream inFile("031.txt");
		while (getline(inFile, picture))
		{
			for (int j = 0; j < picture.size(); )
			{
				pokemon[i][j] = picture[j];
				j++;
			}
			i++;
		}
		strcpy_s(name, name3);
		Hp = Hp1[2];
		ATK = ATK1[2];
		DEF = DEF1[2];
		Speed = Speed1[2];
		Ability = Ability1[2];
	}
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}
void PoisonPokemon3::choice()
{
	srand(time(0));
	string picture;
	int i = 0;
	ifstream inFile("032.txt");
	while (getline(inFile, picture))
	{
		for (int j = 0; j < picture.size(); )
		{
			pokemon[i][j] = picture[j];
			j++;
		}
		i++;
	}
	strcpy_s(name, name1);
	Hp = Hp1[0];
	ATK = ATK1[0];
	DEF = DEF1[0];
	Speed = Speed1[0];
	Ability = Ability1[0];
	strcpy_s(type, type1);
	MaxHp = Hp;
	MaxAtk = ATK;
	MaxDef = DEF;
	MaxSpeed = Speed;
}
void GrassPokemon::Fight(Pokemon* NPC)  //寶可夢對戰
{
	int doubleAttack = 0;
	if (NPC->getType() == "Water" || NPC->getType() == "Electric" || NPC->getType() == "Grass" || NPC->getType() == "Ground")  //依照屬性，決定傷害倍率
	{
		Hp -= (NPC->getAttack() - DEF) * 0.5;
		doubleAttack = (NPC->getAttack() - DEF) * 0.5;
	}
	else if (NPC->getType() == "Fire" || NPC->getType() == "Poison" || NPC->getType() == "Flying" || NPC->getType() == "Bug")
	{
		Hp -= (NPC->getAttack() - DEF) * 2;
		doubleAttack = (NPC->getAttack() - DEF) * 2;
	}
	else
	{
		Hp -= (NPC->getAttack() - DEF);
		doubleAttack = (NPC->getAttack() - DEF) ;
	}
	if (Hp <= 0 )
	{
		Hp = 0;
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
		return;
	}
	else
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量"<<"( "<<Hp<<" / "<<MaxHp<<" )\n\n";

	if (NPC->getAbility() == 1)  //依照能力值的不同，決定不同的戰鬥模式及標準
	{
		int temp = rand() % 4;

		if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp()+3) <= NPC->getMaxHp()&&temp==0)
		{
			NPC->setHp2(3);
			cout  << "**發動回復能力**  ,血量增加3點:\n"<< NPC->getname()<< "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 2)
	{
		srand(time(0));
		int number = 1+rand()%3;
		Hp -= number;
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout<<"**受到Burning能力影響**  ,血量減少:"<<number<<"點 \n"<<name<< "( " << Hp << " / " << MaxHp << " )\n\n";
	}
	else if (NPC->getAbility() == 5)
	{
		srand(time(0));
		int number = 2 + rand() % 2;
		Hp -= number;
		NPC->setHp2(number);
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點 " << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點 " << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			return;
		}
		else
		{
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點 " << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點 " << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 7)
	{
		srand(time(0));
		int number =1 + rand() % 5;
		if (number == 3)
		{
			Hp -= doubleAttack;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點 " << name << " ( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點 " << name << " ( " << Hp << " / " << MaxHp << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 8)
	{
		if (track2 >= 1 && track2 <= 2)
		{
			Hp -= 2;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點 " << name << " ( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點 " << name << " ( " << Hp << " / " << MaxHp << " )\n\n";
		}
		track2 += 1;
	}
	else if (NPC->getAbility() == 9)
	{
		if (track3 >= 1 && track3 <= 2)
		{
			Speed -= 2;
			cout << "**受到電擊的效果影響**:\n"<< name << " 的速度減少 " << 2 << " 點 " << name << " ( 速度: " << Speed << " / 最大攻擊速度:" << MaxSpeed << " )\n\n";
		}
		track3 += 1;
	}
	else if (NPC->getAbility() == 11)
	{
		if (track4 >= 1 && track4 <= 2)
		{
			DEF -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的防禦力減少 " << 2 << " 點" << name << "( 防禦: " << DEF << " / 最大防禦:" << MaxDef << " )\n\n";
		}
		track4 += 1;
	}
	else if (NPC->getAbility() == 12)
	{
		if (track5 >= 1 && track5 <= 2)
		{
			ATK -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的攻擊力減少 " << 2 << " 點" << name << "( 攻擊: " << ATK << " / 最大攻擊:" << MaxAtk << " )\n\n";
		}
		track5 += 1;
	}
	int temp2 = rand() % 4;

	if (temp2 == 1)
	{
		 Hp += 3;
		 cout << "**發動回復能力 血量增加3點**:\n" <<name << "( " << Hp << " / " << MaxHp<< " )\n\n";
	}
	
}
void FirePokemon::Fight(Pokemon* NPC)
{
	int doubleAttack = 0;
	if (NPC->getType() == "Fire" || NPC->getType() == "Grass" || NPC->getType() == "Bug")
	{
		Hp -= (NPC->getAttack() - DEF) * 0.5;
		doubleAttack= (NPC->getAttack() - DEF) * 0.5;
	}
	else if (NPC->getType() == "Water" || NPC->getType() == "Ground")
	{
		Hp -= (NPC->getAttack() - DEF) * 2;
		doubleAttack= (NPC->getAttack() - DEF) * 2;
	}
	else
	{
		Hp -= (NPC->getAttack() - DEF);
		doubleAttack= (NPC->getAttack() - DEF);
	}
	if (Hp <= 0)
	{
		Hp = 0;
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
		return;
	}
	else
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";

	if (NPC->getAbility() == 1)
	{
		int temp = rand() % 4;
		if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp() + 3) <= NPC->getMaxHp() && temp == 0)
		{
			NPC->setHp2(3);
			cout << "**發動回復能力**,  血量增加3點:\n" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 2)
	{
		srand(time(0));
		int number = 1 + rand() % 3;
		Hp -= number;
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
	}
	else if (NPC->getAbility() == 5)
	{
		srand(time(0));
		int number = 2 + rand() % 2;
		Hp -= number;
		NPC->setHp2(number);
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			return;
		}
		else
		{
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 7)
	{
		srand(time(0));
		int number = 1 + rand() % 5;
		if (number == 3)
		{
			Hp -= doubleAttack;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 8)
	{
		if (track2 >= 1 && track2 <= 2)
		{
			Hp -= 2;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
		track2 += 1;
	}
	else if (NPC->getAbility() == 9)
	{
		if (track3 >= 1 && track3 <= 2)
		{
			Speed -= 2;
			cout << "**受到電擊的效果影響**:\n" << name << " 的速度減少 " << 2 << " 點" << name << "( 速度: " << Speed << " / 最大攻擊速度:" << MaxSpeed << " )\n\n";
		}
		track3 += 1;
	}
	else if (NPC->getAbility() == 11)
	{
		if (track4 >= 1 && track4 <= 2)
		{
			DEF -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的防禦力減少 " << 2 << " 點" << name << "( 防禦: " << DEF << " / 最大防禦:" << MaxDef << " )\n\n";
		}
		track4 += 1;
	}
	else if (NPC->getAbility() == 12)
	{
		if (track5 >= 1 && track5 <= 2)
		{
			ATK -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的攻擊力減少 " << 2 << " 點" << name << "( 攻擊: " << ATK << " / 最大攻擊:" << MaxAtk << " )\n\n";
		}
		track5 += 1;
	}

}
void WaterPokemon::Fight(Pokemon* NPC)
{
	int doubleAttack = 0,counterAttack=0, replace = 0;
	if (NPC->getType() == "Fire" || NPC->getType() == "Water")
	{
		Hp -= (NPC->getAttack() - DEF) * 0.5;
		doubleAttack= (NPC->getAttack() - DEF) * 0.5;
		counterAttack = doubleAttack;
	}
	else if (NPC->getType() == "Electric" || NPC->getType() == "Grass")
	{
		Hp -= (NPC->getAttack() - DEF) * 2;
		doubleAttack = (NPC->getAttack() - DEF) * 2;
		counterAttack = doubleAttack;
	}
	else
	{
		Hp -= (NPC->getAttack() - DEF);
		doubleAttack= (NPC->getAttack() - DEF);
		counterAttack = doubleAttack;
	}
	if (Hp <= 0)
	{
		Hp = 0;
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
		return;
	}
	else
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";

	if (NPC->getAbility() == 1)
	{
		int temp = rand() % 4;
		if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp() + 3) <= NPC->getMaxHp() && temp == 0)
		{
			NPC->setHp2(3);
			cout << "**發動回復能力**  ,血量增加3點:\n" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 2)
	{
		srand(time(0));
		int number = 1 + rand() % 3;
		Hp -= number;
		counterAttack += number;
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
	}
	else if (NPC->getAbility() == 5)
	{
		srand(time(0));
		int number = 2 + rand() % 2;
		Hp -= number;
		NPC->setHp2(number);
		counterAttack += number;
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			return;
		}
		else
		{
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 7)
	{
		srand(time(0));
		int number = 1 + rand() % 5;
		if (number == 3)
		{
			Hp -= doubleAttack;
			counterAttack += doubleAttack;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 8)
	{
		if (track2 >= 1 && track2 <= 2)
		{
			Hp -= 2;
			counterAttack += 2;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
		track2 += 1;
	}
	else if (NPC->getAbility() == 9)
	{
		if (track3 >= 1 && track3 <= 2)
		{
			Speed -= 2;
			cout << "**受到電擊的效果影響**:\n" << name << " 的速度減少 " << 2 << " 點" << name << "( 速度: " << Speed << " / 最大攻擊速度:" << MaxSpeed << " )\n\n";
		}
		track3 += 1;
	}
	else if (NPC->getAbility() == 11)
	{
		if (track4 >= 1 && track4 <= 2)
		{
			DEF -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的防禦力減少 " << 2 << " 點" << name << "( 防禦: " << DEF << " / 最大防禦:" << MaxDef << " )\n\n";
		}
		track4 += 1;
	}
	else if (NPC->getAbility() == 12)
	{
		if (track5 >= 1 && track5 <= 2)
		{
			ATK -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的攻擊力減少 " << 2 << " 點" << name << "( 攻擊: " << ATK << " / 最大攻擊:" << MaxAtk << " )\n\n";
		}
		track5 += 1;
	}
	srand(time(0));
	replace = 1 + rand() % 5;
	if (replace == 4)
	{
		NPC->setHp(counterAttack);
		if (NPC->getHp() <= 0)
		{
			Hp = 0;
			cout << "**受到反擊效果的影響**:\n " << NPC->getname() << " 血量減少 " << counterAttack << " 點" << NPC->getname() << "(  " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
		else
		    cout<<"**受到反擊效果的影響**:\n "<<NPC->getname()<<" 血量減少 "<< counterAttack<<" 點" << NPC->getname() << "(  " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
	}
}
void BugPokemon1::Fight(Pokemon* NPC)
{
	int doubleAttack = 0;
	if (NPC->getType() == "Ground" || NPC->getType() == "Grass")
	{
		Hp -= (NPC->getAttack() - DEF) * 0.5;
		doubleAttack= (NPC->getAttack() - DEF) * 0.5;
	}
	else if (NPC->getType() == "Fire" || NPC->getType() == "Flying")
	{
		Hp -= (NPC->getAttack() - DEF) * 2;
		doubleAttack = (NPC->getAttack() - DEF) * 2;
	}
	else
	{
		Hp -= (NPC->getAttack() - DEF);
		doubleAttack=(NPC->getAttack() - DEF);
	}
	if (Hp <= 0)
	{
		Hp = 0;
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
		return;
	}
	else
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";

	if (NPC->getAbility() == 1)
	{
		int temp = rand() % 4;
		if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp() + 3) <= NPC->getMaxHp() && temp == 0)
		{
			NPC->setHp2(3);
			cout << "**發動回復能力**  ,血量增加3點:\n" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 2)
	{
		srand(time(0));
		int number = 1 + rand() % 3;
		Hp -= number;
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
	}
	else if (NPC->getAbility() == 5)
	{
		srand(time(0));
		int number = 2 + rand() % 2;
		Hp -= number;
		NPC->setHp2(number);
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			return;
		}
		else
		{
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 7)
	{
		srand(time(0));
		int number = 1 + rand() % 5;
		if (number == 3)
		{
			Hp -= doubleAttack;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 8)
	{
		if (track2 >= 1 && track2 <= 2)
		{
			Hp -= 2;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
		track2 += 1;
	}
	
}
void BugPokemon2::Fight(Pokemon* NPC)
{
	int doubleAttack = 0;
	if (NPC->getType() == "Ground" || NPC->getType() == "Grass")
	{
		Hp -= (NPC->getAttack() - DEF) * 0.5;
		doubleAttack = (NPC->getAttack() - DEF) * 0.5;
	}
	else if (NPC->getType() == "Fire" || NPC->getType() == "Flying")
	{
		Hp -= (NPC->getAttack() - DEF) * 2;
		doubleAttack = (NPC->getAttack() - DEF) * 2;
	}
	else
	{
		Hp -= (NPC->getAttack() - DEF);
		doubleAttack = (NPC->getAttack() - DEF);
	}
	if (Hp <= 0)
	{
		Hp = 0;
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
		return;
	}
	else
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";

	if (NPC->getAbility() == 1)
	{
		int temp = rand() % 4;
		if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp() + 3) <= NPC->getMaxHp() && temp == 0)
		{
			NPC->setHp2(3);
			cout << "**發動回復能力**  ,血量增加3點:\n" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 2)
	{
		srand(time(0));
		int number = 1 + rand() % 3;
		Hp -= number;
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
	}
	else if (NPC->getAbility() == 5)
	{
		srand(time(0));
		int number = 2 + rand() % 2;
		Hp -= number;
		NPC->setHp2(number);
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			return;
		}
		else
		{
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 7)
	{
		srand(time(0));
		int number = 1 + rand() % 5;
		if (number == 3)
		{
			Hp -= doubleAttack;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 8)
	{
		if (track2 >= 1 && track2 <= 2)
		{
			Hp -= 2;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
		track2 += 1;
	}
	else if (NPC->getAbility() == 9)
	{
		if (track3 >= 1 && track3 <= 2)
		{
			Speed -= 2;
			cout << "**受到電擊的效果影響**:\n" << name << " 的速度減少 " << 2 << " 點" << name << "( 速度: " << Speed << " / 最大攻擊速度:" << MaxSpeed << " )\n\n";
		}
		track3 += 1;
	}
	else if (NPC->getAbility() == 11)
	{
		if (track4 >= 1 && track4 <= 2)
		{
			DEF -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的防禦力減少 " << 2 << " 點" << name << "( 防禦: " << DEF << " / 最大防禦:" << MaxDef << " )\n\n";
		}
		track4 += 1;
	}
	else if (NPC->getAbility() == 12)
	{
		if (track5 >= 1 && track5 <= 2)
		{
			ATK -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的攻擊力減少 " << 2 << " 點" << name << "( 攻擊: " << ATK << " / 最大攻擊:" << MaxAtk << " )\n\n";
		}
		track5 += 1;
	}

}
void FlyingPokemon1::Fight(Pokemon* NPC)
{
	int doubleAttack = 0,count=0;
	srand(time(0));
	count = 1 + rand() % 5;

	if (count == 3)
		cout <<name<< " **發動迴避攻擊技能**:\n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
	else
	{
		if (NPC->getType() == "Bug" || NPC->getType() == "Grass")
		{
			Hp -= (NPC->getAttack() - DEF) * 0.5;
			doubleAttack = (NPC->getAttack() - DEF) * 0.5;
		}
		else if (NPC->getType() == "Electric")
		{
			Hp -= (NPC->getAttack() - DEF) * 2;
			doubleAttack = (NPC->getAttack() - DEF) * 2;
		}
		else if (NPC->getType() == "Ground")
		{
			Hp -= 0;
			doubleAttack = 0;
		}
		else
		{
			Hp -= (NPC->getAttack() - DEF);
			doubleAttack = (NPC->getAttack() - DEF);
		}
		if (Hp <= 0)
		{
			Hp = 0;
			cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
	}
	if (NPC->getAbility() == 1)
	{
		int temp = rand() % 4;
		if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp() + 3) <= NPC->getMaxHp() && temp == 0)
		{
			NPC->setHp2(3);
			cout << "**發動回復能力**  ,血量增加3點:\n" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 2)
	{
		srand(time(0));
		int number = 1 + rand() % 3;
		Hp -= number;
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
	}
	else if (NPC->getAbility() == 5&&count!=3)
	{
		srand(time(0));
		int number = 2 + rand() % 2;
		Hp -= number;
		NPC->setHp2(number);
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			return;
		}
		else
		{
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 7 && count != 3)
	{
		srand(time(0));
		int number = 1 + rand() % 5;
		if (number == 3)
		{
			Hp -= doubleAttack;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 8 && count != 3)
	{
		if (track2 >= 1 && track2 <= 2)
		{
			Hp -= 2;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
		track2 += 1;
	}
	else if (NPC->getAbility() == 9 && count != 3)
	{
		if (track3 >= 1 && track3 <= 2)
		{
			Speed -= 2;
			cout << "**受到電擊的效果影響**:\n" << name << " 的速度減少 " << 2 << " 點" << name << "( 速度: " << Speed << " / 最大攻擊速度:" << MaxSpeed << " )\n\n";
		}
		track3 += 1;
	}
	else if (NPC->getAbility() == 11 && count != 3)
	{
		if (track4 >= 1 && track4 <= 2)
		{
			DEF -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的防禦力減少 " << 2 << " 點" << name << "( 防禦: " << DEF << " / 最大防禦:" << MaxDef << " )\n\n";
		}
		track4 += 1;
	}
	else if (NPC->getAbility() == 12 && count != 3)
	{
		if (track5 >= 1 && track5 <= 2)
		{
			ATK -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的攻擊力減少 " << 2 << " 點" << name << "( 攻擊: " << ATK << " / 最大攻擊:" << MaxAtk << " )\n\n";
		}
		track5 += 1;
	}

}
void NormalPokemon::Fight(Pokemon* NPC)
{
	int doubleAttack = 0;
	Hp -= (NPC->getAttack() - DEF);
	doubleAttack = (NPC->getAttack() - DEF);

	if (Hp <= 0)
	{
		Hp = 0;
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
		return;
	}
	else
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";

	if (NPC->getAbility() == 1)
	{
		int temp = rand() % 4;
		if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp() + 3) <= NPC->getMaxHp() && temp == 0)
		{
			NPC->setHp2(3);
			cout << "**發動回復能力**  ,血量增加3點:\n" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 2)
	{
		srand(time(0));
		int number = 1 + rand() % 3;
		Hp -= number;
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
	}
	else if (NPC->getAbility() == 5)
	{
		srand(time(0));
		int number = 2 + rand() % 2;
		Hp -= number;
		NPC->setHp2(number);
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			return;
		}
		else
		{
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 7)
	{
		srand(time(0));
		int number = 1 + rand() % 5;
		if (number == 3)
		{
			Hp -= doubleAttack;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 8)
	{
		if (track2 >= 1 && track2 <= 2)
		{
			Hp -= 2;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
		track2 += 1;
	}
	else if (NPC->getAbility() == 9)
	{
		if (track3 >= 1 && track3 <= 2)
		{
			Speed -= 2;
			cout << "**受到電擊的效果影響**:\n" << name << " 的速度減少 " << 2 << " 點" << name << "( 速度: " << Speed << " / 最大攻擊速度:" << MaxSpeed << " )\n\n";
		}
		track3 += 1;
	}
	else if (NPC->getAbility() == 11)
	{
		if (track4 >= 1 && track4 <= 2)
		{
			DEF -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的防禦力減少 " << 2 << " 點" << name << "( 防禦: " << DEF << " / 最大防禦:" << MaxDef << " )\n\n";
		}
		track4 += 1;
	}
	else if (NPC->getAbility() == 12)
	{
		if (track5 >= 1 && track5 <= 2)
		{
			ATK -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的攻擊力減少 " << 2 << " 點" << name << "( 攻擊: " << ATK << " / 最大攻擊:" << MaxAtk << " )\n\n";
		}
		track5 += 1;
	}

}
void FlyingPokemon2::Fight(Pokemon* NPC)
{
		int doubleAttack = 0;
		if (NPC->getType() == "Bug" || NPC->getType() == "Grass")
		{
			Hp -= (NPC->getAttack() - DEF) * 0.5;
			doubleAttack = (NPC->getAttack() - DEF) * 0.5;
		}
		else if (NPC->getType() == "Electric")
		{
			Hp -= (NPC->getAttack() - DEF) * 2;
			doubleAttack = (NPC->getAttack() - DEF) * 2;
		}
		else if (NPC->getType() == "Ground")
		{
			Hp -= 0;
			doubleAttack = 0;
		}
		else
		{
			Hp -= (NPC->getAttack() - DEF);
			doubleAttack = (NPC->getAttack() - DEF);
		}
		if (Hp <= 0)
		{
			Hp = 0;
			cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";

		if (NPC->getAbility() == 1)
		{
			int temp = rand() % 4;
			if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp() + 3) <= NPC->getMaxHp() && temp == 0)
			{
				NPC->setHp2(3);
				cout << "**發動回復能力**  ,血量增加3點:\n" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			}
		}
		else if (NPC->getAbility() == 2)
		{
			srand(time(0));
			int number = 1 + rand() % 3;
			Hp -= number;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
		else if (NPC->getAbility() == 5)
		{
			srand(time(0));
			int number = 2 + rand() % 2;
			Hp -= number;
			NPC->setHp2(number);
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
					<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
				return;
			}
			else
			{
				cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
					<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			}
		}
		else if (NPC->getAbility() == 7)
		{
			srand(time(0));
			int number = 1 + rand() % 5;
			if (number == 3)
			{
				Hp -= doubleAttack;
				if (Hp <= 0)
				{
					Hp = 0;
					cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
					return;
				}
				else
					cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			}
		}
		else if (NPC->getAbility() == 8)
		{
			if (track2 >= 1 && track2 <= 2)
			{
				Hp -= 2;
				if (Hp <= 0)
				{
					Hp = 0;
					cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
					return;
				}
				else
					cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			}
			track2 += 1;
		}
		else if (NPC->getAbility() == 9)
		{
			if (track3 >= 1 && track3 <= 2)
			{
				Speed -= 2;
				cout << "**受到電擊的效果影響**:\n" << name << " 的速度減少 " << 2 << " 點" << name << "( 速度: " << Speed << " / 最大攻擊速度:" << MaxSpeed << " )\n\n";
			}
			track3 += 1;
		}
		else if (NPC->getAbility() == 11)
		{
			if (track4 >= 1 && track4 <= 2)
			{
				DEF -= 2;
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的防禦力減少 " << 2 << " 點" << name << "( 防禦: " << DEF << " / 最大防禦:" << MaxDef << " )\n\n";
			}
			track4 += 1;
		}
		else if (NPC->getAbility() == 12)
		{
			if (track5 >= 1 && track5 <= 2)
			{
				ATK -= 2;
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的攻擊力減少 " << 2 << " 點" << name << "( 攻擊: " << ATK << " / 最大攻擊:" << MaxAtk << " )\n\n";
			}
			track5 += 1;
		}


}
void PoisonPokemon1::Fight(Pokemon* NPC)
{	
		int doubleAttack = 0;
		if (NPC->getType() == "Poison" || NPC->getType() == "Grass" || NPC->getType() == "Bug")
		{
			Hp -= (NPC->getAttack() - DEF) * 0.5;
			doubleAttack = (NPC->getAttack() - DEF) * 0.5;
		}
		else if (NPC->getType() == "Ground")
		{
			Hp -= (NPC->getAttack() - DEF) * 2;
			doubleAttack = (NPC->getAttack() - DEF) * 2;
		}
		else
		{
			Hp -= (NPC->getAttack() - DEF);
			doubleAttack = (NPC->getAttack() - DEF);
		}
		if (Hp <= 0)
		{
			Hp = 0;
			cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";

		if (NPC->getAbility() == 1)
		{
			int temp = rand() % 4;
			if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp() + 3) <= NPC->getMaxHp() && temp == 0)
			{
				NPC->setHp2(3);
				cout << "**發動回復能力**  ,血量增加3點:\n" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			}
		}
		else if (NPC->getAbility() == 2)
		{
			srand(time(0));
			int number = 1 + rand() % 3;
			Hp -= number;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
		else if (NPC->getAbility() == 5)
		{
			srand(time(0));
			int number = 2 + rand() % 2;
			Hp -= number;
			NPC->setHp2(number);
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
					<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
				return;
			}
			else
			{
				cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
					<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			}
		}
		else if (NPC->getAbility() == 7)
		{
			srand(time(0));
			int number = 1 + rand() % 5;
			if (number == 3)
			{
				Hp -= doubleAttack;
				if (Hp <= 0)
				{
					Hp = 0;
					cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
					return;
				}
				else
					cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			}
		}
		else if (NPC->getAbility() == 8)
		{
			if (track2 >= 1 && track2 <= 2)
			{
				Hp -= 2;
				if (Hp <= 0)
				{
					Hp = 0;
					cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
					return;
				}
				else
					cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			}
			track2 += 1;
		}
		else if (NPC->getAbility() == 9)
		{
			if (track3 >= 1 && track3 <= 2)
			{
				Speed -= 2;
				cout << "**受到電擊的效果影響**:\n" << name << " 的速度減少 " << 2 << " 點" << name << "( 速度: " << Speed << " / 最大攻擊速度:" << MaxSpeed << " )\n\n";
			}
			track3 += 1;
		}
		else if (NPC->getAbility() == 11)
		{
			if (track4 >= 1 && track4 <= 2)
			{
				DEF -= 2;
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的防禦力減少 " << 2 << " 點" << name << "( 防禦: " << DEF << " / 最大防禦:" << MaxDef << " )\n\n";
			}
			track4 += 1;
		}
		else if (NPC->getAbility() == 12)
		{
			if (track5 >= 1 && track5 <= 2)
			{
				ATK -= 2;
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的攻擊力減少 " << 2 << " 點" << name << "( 攻擊: " << ATK << " / 最大攻擊:" << MaxAtk << " )\n\n";
			}
			track5 += 1;
		}

}
void ElectricPokemon::Fight(Pokemon* NPC)
{
	int doubleAttack = 0;
	if (NPC->getType() == "Electric" || NPC->getType() == "Flying")
	{
		Hp -= (NPC->getAttack() - DEF) * 0.5;
		doubleAttack = (NPC->getAttack() - DEF) * 0.5;
	}
	else if (NPC->getType() == "Ground")
	{
		Hp -= (NPC->getAttack() - DEF) * 2;
		doubleAttack = (NPC->getAttack() - DEF) * 2;
	}
	else
	{
		Hp -= (NPC->getAttack() - DEF);
		doubleAttack = (NPC->getAttack() - DEF);
	}
	if (Hp <= 0)
	{
		Hp = 0;
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
		return;
	}
	else
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";

	if (NPC->getAbility() == 1)
	{
		int temp = rand() % 4;
		if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp() + 3) <= NPC->getMaxHp() && temp == 0)
		{
			NPC->setHp2(3);
			cout << "**發動回復能力**  ,血量增加3點:\n" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 2)
	{
		srand(time(0));
		int number = 1 + rand() % 3;
		Hp -= number;
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
	}
	else if (NPC->getAbility() == 5)
	{
		srand(time(0));
		int number = 2 + rand() % 2;
		Hp -= number;
		NPC->setHp2(number);
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			return;
		}
		else
		{
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 7)
	{
		srand(time(0));
		int number = 1 + rand() % 5;
		if (number == 3)
		{
			Hp -= doubleAttack;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 8)
	{
		if (track2 >= 1 && track2 <= 2)
		{
			Hp -= 2;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
		track2 += 1;
	}
	else if (NPC->getAbility() == 9)
	{
		if (track3 >= 1 && track3 <= 2)
		{
			Speed -= 2;
			cout << "**受到電擊的效果影響**:\n" << name << " 的速度減少 " << 2 << " 點" << name << "( 速度: " << Speed << " / 最大攻擊速度:" << MaxSpeed << " )\n\n";
		}
		track3 += 1;
	}
	else if (NPC->getAbility() == 11)
	{
		if (track4 >= 1 && track4 <= 2)
		{
			DEF -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的防禦力減少 " << 2 << " 點" << name << "( 防禦: " << DEF << " / 最大防禦:" << MaxDef << " )\n\n";
		}
		track4 += 1;
	}
	else if (NPC->getAbility() == 12)
	{
		if (track5 >= 1 && track5 <= 2)
		{
			ATK -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的攻擊力減少 " << 2 << " 點" << name << "( 攻擊: " << ATK << " / 最大攻擊:" << MaxAtk << " )\n\n";
		}
		track5 += 1;
	}
}
void GroundPokemon::Fight(Pokemon* NPC)
{
	int doubleAttack = 0,count=0;
	srand(time(0));
	count = 1 + rand() % 5;
	if (NPC->getType() == "Poison")
	{
		Hp -= (NPC->getAttack() - DEF) * 0.5;
		doubleAttack = (NPC->getAttack() - DEF) * 0.5;
	}
	else if (NPC->getType() == "Water" || NPC->getType() == "Grass")
	{
		Hp -= (NPC->getAttack() - DEF) * 2;
		doubleAttack = (NPC->getAttack() - DEF) * 2;
	}
	else if (NPC->getType() == "Electric")
	{
		Hp -= 0;
		doubleAttack = 0;
	}
	else
	{
		Hp -= (NPC->getAttack() - DEF);
		doubleAttack = (NPC->getAttack() - DEF);
	}
	if (Hp <= 0&&count!=3)
	{
		Hp = 0;
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
		return;
	}
	else if (Hp > 0 && count != 3)
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";

	if (NPC->getAbility() == 1)
	{
		int temp = rand() % 4;
		if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp() + 3) <= NPC->getMaxHp() && temp == 0)
		{
			NPC->setHp2(3);
			cout << "**發動回復能力**  ,血量增加3點:\n" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 2)
	{
		srand(time(0));
		int number = 1 + rand() % 3;
		Hp -= number;
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
	}
	else if (NPC->getAbility() == 5)
	{
		srand(time(0));
		int number = 2 + rand() % 2;
		Hp -= number;
		NPC->setHp2(number);
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			return;
		}
		else
		{ 
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 7)
	{
		srand(time(0));
		int number = 1 + rand() % 5;
		if (number == 3)
		{
			Hp -= doubleAttack;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 8)
	{
		if (track2 >= 1 && track2 <= 2)
		{
			Hp -= 2;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else 
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
		track2 += 1;
	}
	else if (NPC->getAbility() == 9)
	{
		if (track3 >= 1 && track3 <= 2)
		{
			Speed -= 2;
			cout << "**受到電擊的效果影響**:\n" << name << " 的速度減少 " << 2 << " 點" << name << "( 速度: " << Speed << " / 最大攻擊速度:" << MaxSpeed << " )\n\n";
		}
		track3 += 1;
	}
	else if (NPC->getAbility() == 11)
	{
		if (track4 >= 1 && track4 <= 2)
		{
			DEF -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的防禦力減少 " << 2 << " 點" << name << "( 防禦: " << DEF << " / 最大防禦:" << MaxDef << " )\n\n";
		}
		track4 += 1;
	}
	else if (NPC->getAbility() == 12)
	{
		if (track5 >= 1 && track5 <= 2)
		{
			ATK -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的攻擊力減少 " << 2 << " 點" << name << "( 攻擊: " << ATK << " / 最大攻擊:" << MaxAtk << " )\n\n";
		}
		track5 += 1;
	}
	if (count == 3)
	{
		Hp+= doubleAttack;
		Hp -= 2;
		cout<<"**發動地屬性的附加效果**:\n"<< name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
	}
}
void PoisonPokemon2::Fight(Pokemon* NPC)
{
	int doubleAttack = 0;
	if (NPC->getType() == "Poison" || NPC->getType() == "Grass" || NPC->getType() == "Bug")
	{
		Hp -= (NPC->getAttack() - DEF) * 0.5;
		doubleAttack = (NPC->getAttack() - DEF) * 0.5;
	}
	else if (NPC->getType() == "Ground")
	{
		Hp -= (NPC->getAttack() - DEF) * 2;
		doubleAttack = (NPC->getAttack() - DEF) * 2;
	}
	else
	{
		Hp -= (NPC->getAttack() - DEF);
		doubleAttack = (NPC->getAttack() - DEF);
	}
	if (Hp <= 0)
	{
		Hp = 0;
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
		return;
	}
	else
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";

	if (NPC->getAbility() == 1)
	{
		int temp = rand() % 4;
		if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp() + 3) <= NPC->getMaxHp() && temp == 0)
		{
			NPC->setHp2(3);
			cout << "**發動回復能力**  ,血量增加3點:\n" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 2)
	{
		srand(time(0));
		int number = 1 + rand() % 3;
		Hp -= number;
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
	}
	else if (NPC->getAbility() == 5)
	{
		srand(time(0));
		int number = 2 + rand() % 2;
		Hp -= number;
		NPC->setHp2(number);
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			return;
		}
		else
		{
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 7)
	{
		srand(time(0));
		int number = 1 + rand() % 5;
		if (number == 3)
		{
			Hp -= doubleAttack;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 8)
	{
		if (track2 >= 1 && track2 <= 2)
		{
			Hp -= 2;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
		track2 += 1;
	}
	else if (NPC->getAbility() == 9)
	{
		if (track3 >= 1 && track3 <= 2)
		{
			Speed -= 2;
			cout << "**受到電擊的效果影響**:\n" << name << " 的速度減少 " << 2 << " 點" << name << "( 速度: " << Speed << " / 最大攻擊速度:" << MaxSpeed << " )\n\n";
		}
		track3 += 1;
	}
	else if (NPC->getAbility() == 11)
	{
		if (track4 >= 1 && track4 <= 2)
		{
			DEF -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的防禦力減少 " << 2 << " 點" << name << "( 防禦: " << DEF << " / 最大防禦:" << MaxDef << " )\n\n";
		}
		track4 += 1;
	}
	else if (NPC->getAbility() == 12)
	{
		if (track5 >= 1 && track5 <= 2)
		{
			ATK -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的攻擊力減少 " << 2 << " 點" << name << "( 攻擊: " << ATK << " / 最大攻擊:" << MaxAtk << " )\n\n";
		}
		track5 += 1;
	}

}
void PoisonPokemon3::Fight(Pokemon* NPC)
{
	int doubleAttack = 0;
	if (NPC->getType() == "Poison" || NPC->getType() == "Grass" || NPC->getType() == "Bug")
	{
		Hp -= (NPC->getAttack() - DEF) * 0.5;
		doubleAttack = (NPC->getAttack() - DEF) * 0.5;
	}
	else if (NPC->getType() == "Ground")
	{
		Hp -= (NPC->getAttack() - DEF) * 2;
		doubleAttack = (NPC->getAttack() - DEF) * 2;
	}
	else
	{
		Hp -= (NPC->getAttack() - DEF);
		doubleAttack = (NPC->getAttack() - DEF);
	}
	if (Hp <= 0)
	{
		Hp = 0;
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";
		return;
	}
	else
		cout << name << "受到攻擊 減少 " << doubleAttack << " 點血量" << "( " << Hp << " / " << MaxHp << " )\n\n";

	if (NPC->getAbility() == 1)
	{
		int temp = rand() % 4;
		if (NPC->getHp() < NPC->getMaxHp() && (NPC->getHp() + 3) <= NPC->getMaxHp() && temp == 0)
		{
			NPC->setHp2(3);
			cout << "**發動回復能力**  ,血量增加3點:\n" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 2)
	{
		srand(time(0));
		int number = 1 + rand() % 3;
		Hp -= number;
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
			return;
		}
		else
			cout << "**受到Burning能力影響**  ,血量減少:" << number << "點 \n" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
	}
	else if (NPC->getAbility() == 5)
	{
		srand(time(0));
		int number = 2 + rand() % 2;
		Hp -= number;
		NPC->setHp2(number);
		if (Hp <= 0)
		{
			Hp = 0;
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
			return;
		}
		else
		{
			cout << "**受到吸血能力影響**:\n" << name << " 的血量減少 " << number << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n"
				<< NPC->getname() << " 的血量增加 " << number << " 點" << NPC->getname() << "( " << NPC->getHp() << " / " << NPC->getMaxHp() << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 7)
	{
		srand(time(0));
		int number = 1 + rand() % 5;
		if (number == 3)
		{
			Hp -= doubleAttack;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到二次攻擊的能力影響**:\n" << name << " 的血量減少 " << doubleAttack << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
	}
	else if (NPC->getAbility() == 8)
	{
		if (track2 >= 1 && track2 <= 2)
		{
			Hp -= 2;
			if (Hp <= 0)
			{
				Hp = 0;
				cout << "**受到中毒的效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
				return;
			}
			else
				cout << "**受到中毒的附加效果影響**:\n" << name << " 的血量減少 " << 2 << " 點" << name << "( " << Hp << " / " << MaxHp << " )\n\n";
		}
		track2 += 1;
	}
	else if (NPC->getAbility() == 9)
	{
		if (track3 >= 1 && track3 <= 2)
		{
			Speed -= 2;
			cout << "**受到電擊的效果影響**:\n" << name << " 的速度減少 " << 2 << " 點" << name << "( 速度: " << Speed << " / 最大攻擊速度:" << MaxSpeed << " )\n\n";
		}
		track3 += 1;
	}
	else if (NPC->getAbility() == 11)
	{
		if (track4 >= 1 && track4 <= 2)
		{
			DEF -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的防禦力減少 " << 2 << " 點" << name << "( 防禦: " << DEF << " / 最大防禦:" << MaxDef << " )\n\n";
		}
		track4 += 1;
	}
	else if (NPC->getAbility() == 12)
	{
		if (track5 >= 1 && track5 <= 2)
		{
			ATK -= 2;
			cout << "**受到中毒的附加效果影響**:\n" << name << " 的攻擊力減少 " << 2 << " 點" << name << "( 攻擊: " << ATK << " / 最大攻擊:" << MaxAtk << " )\n\n";
		}
		track5 += 1;
	}

}

