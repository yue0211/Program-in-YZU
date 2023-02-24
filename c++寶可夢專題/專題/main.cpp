#include<iostream>
#include<fstream>
#include<string>
#include<random>
#include<time.h>
#include"rlutil.h"
#include"Pokemon.h"
using namespace std;
using namespace rlutil;
#define waitkey rlutil::anykey("Press any key to continue...\n")
void draw(char map[][104], string name, GrassPokemon a[], FirePokemon b[], WaterPokemon c[], BugPokemon1 d[]
	, BugPokemon2 e[], FlyingPokemon1 f[], NormalPokemon g[], FlyingPokemon2 h[], PoisonPokemon1 s[], 
	ElectricPokemon p[], GroundPokemon t[], PoisonPokemon2 l[], PoisonPokemon3 m[]);

void getPokemon(char map[][104],int x,int y, Pokemon* user[],int &PokemonNumber, GrassPokemon a[], int &count, 
	FirePokemon b[], WaterPokemon c[], BugPokemon1 d[], BugPokemon2 e[], FlyingPokemon1 f[], NormalPokemon g[], 
	FlyingPokemon2 h[], PoisonPokemon1 s[], ElectricPokemon p[], GroundPokemon t[], PoisonPokemon2 l[], PoisonPokemon3 m[]);

void FightwithNPC(Pokemon* user[], char map[][104], int y, int x,int & totalwin,string name);

void Playstart(string &name);

int main( )
{
	GrassPokemon a[3]; FirePokemon b[3]; WaterPokemon c[3]; BugPokemon1 d[3]; BugPokemon2 e[3]; FlyingPokemon1 f[3];
	NormalPokemon g[3]; FlyingPokemon2 h[3]; PoisonPokemon1 s[3]; ElectricPokemon p[3]; GroundPokemon t[3]; PoisonPokemon2 l[3]; PoisonPokemon3 m[3];
	char map[31][104] = {};
	ifstream inFile("yzumap.txt", ios::in);
	if (!inFile)
		std::cout << "File couldn't be opened!\n";
	else
	{
			string name;
			Playstart(name);   //呼叫 輸入使用者名稱的檔案
			
			string line;
			int i = 0,k=0;
			while (getline(inFile, line))   // 將地圖寫入 map的二維陣列
			{
				for (int j = 0; j < line.size(); j++)
					map[i][j] = line[j];
				i++;
			}

			draw(map,name ,a,b,c,d,e,f,g,h,s,p,t,l,m);   //呼叫畫地圖的檔案
			
		
	}
	inFile.close();
}
void draw(char map[][104],string name, GrassPokemon a[], FirePokemon b[], WaterPokemon c[], BugPokemon1 d[]
	, BugPokemon2 e[], FlyingPokemon1 f[], NormalPokemon g[], FlyingPokemon2 h[], PoisonPokemon1 s[],
	ElectricPokemon p[], GroundPokemon t[], PoisonPokemon2 l[], PoisonPokemon3 m[])
{
	int count = 0,totalwin=0,track=0;
	Pokemon* user[3] = {};    // 用來存玩家的寶可夢
	int PokemonNumber = 0;
	srand(time(0));
	for (int j = 0; j < 31; j++)    // 設定場景顏色
	{
		for (int k = 0; k < 104; k++)
		{
			if (map[j][k] == '~')
				setColor(3);
			else if(map[j][k] == ';')
				setColor(10);
			else if(map[j][k] == '!')
				setColor(12);
			else if(map[j][k] == '#')
				setColor(6);
			else
				setColor(14);
			cout << map[j][k];
		}
		cout << endl;
	}
	locate(20, 30); setColor(4);cout << "@"<<endl;  
	setColor(11);
	locate(5, 33);
	cout << "目前玩家:" << name;
	locate(5, 35);
	int count2 = 0;
	cout << "目前持有寶可夢種類: ";
	for (int i = 0; i < 3; i++)
	{
		if (user[i] == nullptr && count2 == 0)   //如果玩家沒寶可夢，則輸出無，有的話則輸出寶可夢的名字
		{
			cout << "無\n\n";
			break;
		}
		else if (user[i] == nullptr && count2 != 0)
			break;
		cout << user[i]->getname() << "  ";
		count2++;
	}
	cout << "    如果需要查詢寶可夢資訊請按 r\n\n    如果需要放棄寶可夢請按 t";
	
	int x = 20,y=30; 
	hidecursor();
	saveDefaultColor();
	while (true) 
	{
		if (kbhit()) 
		{
			char k = getch(); 
			locate(x, y);
			if ((map[y - 1][x - 1] == '~' || map[y - 1][x - 1] == ';' || map[y - 1][x - 1] == '#'))  //進入草地 水池 還有入口 不會變成空白
			{
				if(map[y - 1][x - 1] == '~')
					setColor(3);
				else if (map[y - 1][x - 1] == ';')
					setColor(10);
				else if (map[y - 1][x - 1] == '#')
					setColor(6);
				cout << map[y - 1][x - 1];
			}
			else   //其餘變成空白
			{
				cout << " "; 
			}
			if ((k == 'a' || k == 'A')) --x;       //改變座標
			else if ((k == 'd'|| k == 'D')) ++x;
			else if ((k == 'w'|| k == 'W')) --y;
			else if ((k == 's'|| k == 'S')) ++y;
			else if (k == 'r')  //使用者輸入r時，可查詢寶可夢
			{
				setColor(11);
				locate(5, 41);
				cout << "請選擇想查詢的寶可夢(由左至右的寶可夢分別為1 2 3,請輸入1 2 3): ";
				int choice3 = 0;
				cin >> choice3;
				user[choice3 - 1]->printpicture3();
				locate(5, 41);
				cout << "                                                                                                                                        ";
			}
			else if (k == 't')   //使用者輸入t時，可刪除寶可夢
			{
				    setColor(11);
				    locate(5, 41);
					int choice3 = 0;
				   cout << "請選擇想刪除的寶可夢(由左至右的寶可夢分別為1 2 3,請輸入1 2 3, 取消 : 0 ): ";
				   cin >> choice3;
				   for (int i = 0; i < 2; i++)
				   {
					   if (choice3 == 2)
						   user[1] = user[2];
					   else if (choice3 == 1 && PokemonNumber != 1)
						   user[i] = user[i + 1];
					   else if (choice3 == 3)
						   user[2] = nullptr;
					   else if (choice3 == 1 && PokemonNumber == 1)
						   user[i] = nullptr;
				   }
				   if (choice3 != 0)
				   {
					   user[2] = nullptr;
					   PokemonNumber -= 1;
					   count -= 1;
					   locate(25, 35);
					   cout << "                                                                                                             ";
					   locate(25, 35);
					   for (int i = 0; user[i] != nullptr; i++)
						   cout << user[i]->getname() << "  ";
				   }
				   for (int i = 41; i < 100; i++)
				   {
					   locate(1, i);
					   cout << "                                                                                                                ";
				   }
				   locate(1, 1); cout << " ";
			}
			else if (k == ' ') break;
		
			if ((k == 'a') && (map[y-1][x-1] == '*' || map[y-1][x-1] >= 48 && map[y-1][x-1] <= 57 || map[y-1][x-1] == '!' || map[y-1][x-1] >= 65 && map[y-1][x-1] <= 90))  //如果是星星 樹木 數字 則無法通行，定位游標位置
				++x;
			else if ((k == 'd' ) && (map[y-1][x-1] == '*' || map[y-1][x-1] >= 48 && map[y-1][x-1] <= 57 || map[y-1][x-1] == '!' || map[y-1][x-1] >= 65 && map[y-1][x-1] <= 90))
				--x;
			else if ((k == 'w') && (map[y-1][x-1] == '*' || map[y-1][x-1] >= 48 && map[y-1][x-1] <= 57 || map[y-1][x-1] == '!' || map[y-1][x-1] >= 65 && map[y-1][x-1] <= 90))
				++y;
			else if ((k == 's') &&( map[y-1][x-1] == '*' || map[y-1][x-1] >= 48 && map[y-1][x-1] <= 57 || map[y-1][x-1] == '!' || map[y-1][x-1] >= 65 && map[y-1][x-1] <= 90))
				--y;
			locate(x, y);setColor(4); cout << '@'; 
			int temp = rand() % 10;
			if (temp == 0 && map[y - 1][x - 1] != '#'&&PokemonNumber<3&&(k == 'a'|| k == 'd'|| k == 'w'|| k == 's'))    //10%的機率進入抓寶流程，且map存的值不能是建築物入口，且寶可夢數量要小於等於3
			{
				setColor(7);
				getPokemon(map,x,y,user, PokemonNumber,a,count,b,c,d,e,f,g,h,s,p,t,l,m);   //進入抓寶流程
				PokemonNumber++;
			}
			else if (map[y - 1][x - 1] == '#'&& PokemonNumber==3)
			{
				FightwithNPC(user,map,y,x, totalwin,name);
				if (totalwin == 7)
					exit(0);
				track = 1;
			}
			setColor(11);
			locate(5, 33);
			cout << "目前玩家:"<<name;
			locate(5, 35);
			int count2 = 0;
			cout << "目前持有寶可夢種類: ";
			for (int i = 0; i < 3; i++)   //如果玩家沒寶可夢，則輸出無，有的話則輸出寶可夢的名字
			{
				if (user[i] == nullptr && count2 == 0)
				{
					cout << "無\n\n";
					break;
				}
				else if (user[i] == nullptr && count2 != 0)
					break;
				cout << user[i]->getname() << "  ";
				count2++;
			}
			if (track == 1)
			{
				locate(5, 41);
				cout << "目前獲勝場數: " << totalwin;
			}
			if (PokemonNumber < 3)
			{
				locate(5, 43);
				setColor(12);
				cout << "**抓滿三隻寶可夢,才可進入道館** ";
			}
		}
	    cout.flush();
		hidecursor();
	}
}
void FightwithNPC(Pokemon* user[], char map[][104],int y,int x, int &totalwin,string name)
{
	system("cls");
	setColor(11);
	int chooce[3] = {};
	Pokemon* replace[3] = {};
	replace[0] = user[0];
	replace[1] = user[1];
	replace[2] = user[2];
	cout << "即將展開與館主的對戰\n\n當某一方的寶可夢都死亡時，結束對戰\n\n對戰結束後，玩家寶可夢將完全恢復 。\n\n";

	cout << name << "現有的寶可夢 : " << user[0]->getname() << "  " << user[1]->getname() << "  " << user[2]->getname()<<endl<<endl;

	Pokemon* NPC[3];
	srand(time(0));
	int number = 1 + rand() % 13;

	GrassPokemon a; FirePokemon b; WaterPokemon c; BugPokemon1 d; BugPokemon2 e;
	FlyingPokemon1 f; NormalPokemon g; FlyingPokemon2 h; PoisonPokemon1 k; ElectricPokemon m;
	GroundPokemon n; PoisonPokemon2 o; PoisonPokemon3 p;

	if (number == 1)  //  當number屬於1~13時，會設定NPC的寶可夢的屬性
	{
		NPC[0] = &a; 
		NPC[1] = &c;
		NPC[2] = &e;
	}
	else if (number == 2)
	{
		NPC[0] = &g;
		NPC[1] = &h;
		NPC[2] = &k;
	}
	else if (number == 3)
	{
		NPC[0] = &f;
		NPC[1] = &m;
		NPC[2] = &n;
	}
	else if (number == 4)
	{
		NPC[0] = &b;
		NPC[1] = &d;
		NPC[2] = &p;
	}
	else if (number == 5)
	{
		NPC[0] = &o;
		NPC[1] = &b;
		NPC[2] = &m;
	}
	else if (number == 6)
	{
		NPC[0] = &g;
		NPC[1] = &a;
		NPC[2] = &p;
	}
	else if (number == 7)
	{
		NPC[0] = &b;
		NPC[1] = &g;
		NPC[2] = &h;
	}
	else if (number == 8)
	{
		NPC[0] = &e;
		NPC[1] = &f;
		NPC[2] = &c;
	}
	else if (number == 9)
	{
		NPC[0] = &d;
		NPC[1] = &m;
		NPC[2] = &e;
	}
	else if (number == 10)
	{
		NPC[0] = &e;
		NPC[1] = &k;
		NPC[2] = &n;
	}
	else if (number == 11)
	{
		NPC[0] = &c;
		NPC[1] = &f;
		NPC[2] = &g;
	}
	else if (number == 12)
	{
		NPC[0] = &m;
		NPC[1] = &a;
		NPC[2] = &g;
	}
	else if (number == 13)
	{
		NPC[0] = &k;
		NPC[1] = &b;
		NPC[2] = &f;
	}
	NPC[0]->setData();NPC[0]->choice();NPC[1]->setData();NPC[1]->choice();NPC[2]->setData();NPC[2]->choice();   //設定NPC的寶可夢的種類和數值


	cout << "館主現有的寶可夢 : " << NPC[0]->getname() << "  " << NPC[1]->getname() << "  " << NPC[2]->getname() << "  ";


	setColor(14);
	string solution;
	cout << "\n\n是否需取消對戰 ( y or n ) : ";
	while (solution != "n")
	{
		cin >> solution;
		if (solution == "y")
		{
			system("cls");
			for (int j = 0; j < 31; j++)
			{
				for (int k = 0; k < 104; k++)
				{
					if (map[j][k] == '~')
						setColor(3);
					else if (map[j][k] == ';')
						setColor(10);
					else if (map[j][k] == '!')
						setColor(12);
					else if (map[j][k] == '#')
						setColor(6);
					else
						setColor(14);
					cout << map[j][k];
				}
				cout << endl;
			}
			locate(x, y); setColor(4); cout << '@'; 
			locate(5, 37); setColor(11);
			cout << "如果需要查詢寶可夢資訊請按 r\n\n    如果需要放棄寶可夢請按 t";
			return;
		}
		else if (solution == "n")
			break;
		else
			cout << "\n輸入錯誤，請重新輸入: ";
	}
	string solution2;
	cout << "\n是否需查詢 "<< name<<" 的寶可夢能力 ( y or n) : ";
	while (solution2 != "y" || solution2 != "n")
	{
		cin >> solution2;
		if (solution2 == "y" || solution2 == "n")
			break;
		else
		  cout << "\n輸入錯誤，請重新輸入: ";
	}
	for (int i = 0; i < 30; i++)
	{
		locate(1, 11 + i);
		cout << "                                                                ";
	}
	int choice3 = -1;
	while (solution2=="y")   // 用於查詢寶可夢能力
	{
		setColor(14);
		locate(1,11 );
		cout << "請選擇想查詢的 "<<name<<" 的寶可夢(由左至右的寶可夢分別為1 2 3,請輸入1 2 3),取消查詢(請輸入4) :  ";
		cin >> choice3;
		while (choice3 <= 0 || choice3 > 4)
		{
			cout<< "\n輸入錯誤，請重新輸入: ";
			cin >> choice3;
		}
		if (choice3 == 4)
			break;
		user[choice3 - 1]->printpicture3();
		for (int i = 0; i < 30; i++)
		{
			locate(1, 11 + i);
			cout << "                                                                ";
		}
		locate(1, 11); cout << "                                                                                                                                                                 ";
	}
		for (int i = 0; i < 30; i++)
		{
			locate(1, 11 + i);
			cout << "                                                                                                                                                        ";
		}
		locate(1, 11);
		cout << "請選擇 " << name << " 的寶可夢的出場順序 ( 由左至右分別為 1~3 ),請分別輸入3個數字\n\n";
		for (int i = 0; i < 3; i++)   //用於決定寶可夢的出場順序
		{
			cout << name << " 的第 " << i + 1 << " 隻寶可夢 : ";
			cin >> chooce[i];
			while (chooce[i] <= 0 || chooce[i] >3)
			{
				cout<< "\n輸入錯誤，請重新輸入: ";
				cin >> chooce[i];
			}
			cout << endl;
		}
		user[0] = replace[chooce[0] - 1];
		user[1] = replace[chooce[1] - 1];
		user[2] = replace[chooce[2] - 1];
		cout << endl << endl; waitkey;
		
	system("cls");
	 int win = 0,win2=0,cnt=1,track=0,i=0,j=0;

	 while (NPC[2]->getHp()!=0)   // 當NPC的最後一隻寶可夢的血量不為0時
	 {

		 while (user[i]->getHp() != 0 && NPC[j]->getHp() != 0)  // 當NPC和玩家目前戰鬥的寶可夢的血量不為0時
		 {
			 user[i]->printpicture();   //印玩家的寶可夢的圖片
			 NPC[j]->printpicture2(); //印NPC的寶可夢的圖片

			 user[i]->printability2();   //印玩家的寶可夢的能力
			 cout << "\n\n"<< name<<" 的第一隻寶可夢:" << user[0]->getname() << "\n\n"<<name<<" 的第二隻寶可夢:"
				 << user[1]->getname() << "\n\n"<<name<<" 的第三隻寶可夢:" << user[2]->getname();
			 NPC[j]->printability3(); locate(55, 33);  //印NPC的寶可夢的能力
			 cout << "館主的第一隻寶可夢:" << NPC[0]->getname(); locate(55, 35);
			 cout << "館主的第二隻寶可夢:" << NPC[1]->getname(); locate(55, 37);
			 cout << "館主的第三隻寶可夢:" << NPC[2]->getname() << endl << endl << "------------------------------------------------------------------------------\n";

			 cout << "\nRound  " << cnt<<"           ";

			 if (user[i]->getSpeed() >= NPC[j]->getSpeed() && cnt == 1)     //從寶可夢的速度判斷，玩家的寶可夢先攻，還是NPC的寶可夢先攻
			 {
				 cout << user[i]->getname() << " 先攻擊 " << NPC[j]->getname()<< endl ;
				 track = 1;
			 }
			 else if (user[i]->getSpeed() < NPC[j]->getSpeed() && cnt == 1)
				 cout << NPC[j]->getname() << " 先攻擊 " << user[i]->getname() << endl;

			 if (track == 1)
			 {
				 cout << "\n\n館主的 ";
				 NPC[j]->Fight(user[i]);     //NPC的寶可夢被攻擊  
				 cout <<name<< " 的 ";
				 user[i]->Fight(NPC[j]);   //玩家的寶可夢被攻擊
			 }
			 else
			 {
				 cout << "\n\n"<<name<<" 的 "; 
				user[i]->Fight(NPC[j]);   //玩家的寶可夢被攻擊
				 cout << "館主的 ";
				 NPC[j]->Fight(user[i]);  // NPC的寶可夢被攻擊  	 
			 }
			 ++cnt;
			  waitkey;
			 system("cls");
			 if (user[i]->getHp() == 0 || NPC[j]->getHp() == 0)//當任一方手邊戰鬥的寶可夢血量為0時，跳出迴圈
				 break;

		 }
		 if (user[i]->getHp() == 0)  //如果是玩家的寶可夢死亡，則派出玩家的下一隻寶可夢
		 {
			i += 1;
			win2 += 1;
		 }
		 else if (NPC[j]->getHp() == 0)  //如果是NPC的寶可夢死亡，則派出NPC的下一隻寶可夢
		 {
				j += 1;
				win += 1;
		 }
		 system("cls");
		 track = 0;
		 cnt = 1;
		 if (NPC[2]->getHp() == 0 || user[2]->getHp() == 0)  //如果NPC或是玩家全部的寶可夢死亡時，跳出迴圈
			 break;
	 }
	 if (win > win2)
	 {
		cout << name<<" 獲勝\n\n";
		totalwin += 1;
		if (totalwin == 7)
		{
			system("cls"); locate(30,20);
			cout << "恭喜 "<<name<<" 的獲勝達7場，歡迎再次遊玩!!!";
		}
	 }
	 else if(win < win2)
		 cout << "館主獲勝\n\n";
	 if (totalwin != 7)
		 cout << "目前 "<<name<<" 的獲勝場數 : " << totalwin << " 場";
	 cout << endl<<endl; waitkey; 
	 user[0]->originalStatus(); user[1]->originalStatus(); user[2]->originalStatus();   // 將玩家的所有寶可夢回復血量
	 NPC[0]->originalStatus(); NPC[1]->originalStatus(); NPC[2]->originalStatus(); // 將NPC的所有寶可夢回復血量
	 if (totalwin != 7)
	 {
		 system("cls");
		 for (int j = 0; j < 31; j++)
		 {
			 for (int k = 0; k < 104; k++)
			 {
				 if (map[j][k] == '~')
					 setColor(3);
				 else if (map[j][k] == ';')
					 setColor(10);
				 else if (map[j][k] == '!')
					 setColor(12);
				 else if (map[j][k] == '#')
					 setColor(6);
				 else
					 setColor(14);
				 cout << map[j][k];
			 }
			 cout << endl;
		 }
		 locate(x, y); setColor(4); cout << '@'; 
		 locate(5, 37); setColor(11);
		 cout << "如果需要查詢寶可夢資訊請按 r\n\n    如果需要放棄寶可夢請按 t";
	 }
	
}
void getPokemon(char map[][104], int x, int y, Pokemon* user[], int& PokemonNumber, GrassPokemon a[], int& count,
	FirePokemon b[], WaterPokemon c[], BugPokemon1 d[], BugPokemon2 e[], FlyingPokemon1 f[], NormalPokemon g[],
	FlyingPokemon2 h[], PoisonPokemon1 s[], ElectricPokemon p[], GroundPokemon t[], PoisonPokemon2 l[], PoisonPokemon3 m[])
{
	char choice ;
	system("cls");
	srand(time(0));
	int  number = 1 + rand() %13;
	int  number2 = 0;
	if (map[y - 1][x - 1] == ';'&& number!=1)  //如果在草地環境，提高遇到草系寶可夢的機率
	{
		number2= 1 + rand() % 9;
		if (number2 == 3)
			number = 1;
	}
	if (map[y - 1][x - 1] == '~' && number != 3)    //如果在水的環境，提高遇到水系寶可夢的機率
	{
		number2 = 1 + rand() % 9;
		if (number2 == 3)
			number = 3;
	}
	if (number == 1)     //當number屬於1~13時，會將user指標指向相對應屬性的寶可夢
		user[PokemonNumber] = &a[count];
	else if (number == 2)
		user[PokemonNumber] = &b[count];
	else if (number == 3)
		user[PokemonNumber] = &c[count];
	else if (number == 4)
		user[PokemonNumber] = &d[count];
	else if (number == 5)
		user[PokemonNumber] = &e[count];
	else if (number == 6)
		user[PokemonNumber] = &f[count];
	else if (number == 7)
		user[PokemonNumber] = &g[count];
	else if (number == 8)
		user[PokemonNumber] = &h[count];
	else if (number == 9)
		user[PokemonNumber] = &s[count];
	else if (number == 10)
		user[PokemonNumber] = &p[count];
	else if (number == 11)
		user[PokemonNumber] = &t[count];
	else if (number == 12)
		user[PokemonNumber] = &l[count];
	else if (number == 13)
		user[PokemonNumber] = &m[count];
	count++;
	user[PokemonNumber]->setData();  //設定寶可夢的數值
	user[PokemonNumber]->cleanpicture();  //清除圖片資料
	user[PokemonNumber]->choice();   //設定寶可夢的種類
	user[PokemonNumber]->printpicture();  //印出寶可夢的圖像
	user[PokemonNumber]->printability();  //印出寶可夢的能力
	try
	{
		user[PokemonNumber] ->BeforeCatch();  //抓寶前的提示話語
	}
	catch (Pokemon::WrongFail & e)
	{
		cerr << e.what() << endl;
	}
	if (user[PokemonNumber]->getTrack() == 0)   //如果沒抓到寶，就將使用者存寶可夢對應的指標陣列設為空指標
	{
		user[PokemonNumber] = nullptr;
		count -= 1;
		PokemonNumber -= 1;
	}
	cout << endl << "目前持有寶可夢數量:" << (PokemonNumber + 1) << endl<<endl;

	if ((PokemonNumber + 1) == 3)
		cout << "已達寶可夢數量持有上限，將無法再遇到寶可夢\n\n";
	int count2 = 0;
	cout << "目前持有寶可夢種類:";
	for (int i=0;i<3;i++)  //如果玩家沒寶可夢，則輸出無，有的話則輸出寶可夢的名字
	{
		if (user[i] == nullptr && count2 == 0)
		{
			cout << "無\n\n";
			break;
		}
		else if (user[i] == nullptr && count2 != 0)
			break;
		cout << user[i]->getname() << "  ";
		count2++;
	}
	if ((PokemonNumber + 1) == 3)   //如果玩家抓到的寶可夢數量為3隻時，則詢問玩家是否需要放生寶可夢
	{
		string choice2;
		int choice3 = 0;
		cout << "\n\n是否需要放棄已擁有的寶可夢 ( y or n): ";
		while (cin >> choice2)
		{
			if (choice2 == "n")
				break;
			else if (choice2 =="y")
			{
				cout << "\n請選擇想刪除的寶可夢(由左至右的寶可夢分別為1 2 3,請輸入1 2 3, 取消:0 ): ";    //選擇需要刪除的寶可夢，不管選擇哪一個寶可夢，																																				
				cin >> choice3;																													 //都會將最後一個指標陣列設為空指標
				for (int i = 0; i < 2; i++)
				{
					if (choice3 == 2)
						user[1] = user[2];
					else if (choice3 == 1)
						user[i] = user[i + 1];
					else if (choice3 == 3)
						user[2] = nullptr;
				}
				if (choice3 != 0)
				{
					user[2] = nullptr;
					PokemonNumber -= 1;
					count -= 1;
				}
				break;
			}
			else
				cout << "\n\n輸入錯誤請重新輸入: ";
		}
	}
	cout << endl<<endl;
	waitkey;

	system("cls");
	for (int j = 0; j < 31; j++)   //將地圖印出
	{
		for (int k = 0; k < 104; k++)
		{
			if (map[j][k] == '~')
				setColor(3);
			else if (map[j][k] == ';')
				setColor(10);
			else if (map[j][k] == '!')
				setColor(12);
			else if (map[j][k] == '#')
				setColor(6);
			else
				setColor(14);
			cout << map[j][k];
		}
		cout << endl;
	}
	locate(x, y); setColor(4); cout << '@'; 
	locate(5, 37); setColor(11);
	cout << "如果需要查詢寶可夢資訊請按 r\n\n    如果需要放棄寶可夢請按 t";

	return;
}
void Playstart(string& name)  //  玩法說明 及 輸入使用者名稱
{
	setColor(11);
	cout << " 玩法說明 : \n\n 鍵盤中的 w , a , s , d 分別為移動鍵的上下左右。\n\n @ : 表示玩家的所在位置 , * 和 ! 分別表示牆和樹木 ,玩家不可穿越。 \n\n"
		<< " # 表示道館入口 , 進入後,將立即與道館主展開對決。\n\n" << " 玩家剛進入遊戲時,要先抓滿3隻寶可夢才可與館主對決。\n\n" << " 抓滿3隻寶可夢時,將不會再遇到任何寶可夢!!!\n\n"
		<< " 贏過任意館主7場,遊戲才能結束\n\n";


	cout << endl << endl; waitkey;
	system("cls");
	setColor(10);

	
	char choice;
	cout << "請輸入玩家名稱:";
	getline(cin, name);
	cout << "\n玩家名稱:" << name<< "\t是否想更改玩家名稱 ( y or n) :";
	cin >> choice;
	
	while (choice != 'n' )
	{
		if (choice == 'y' )
		{
			cin.ignore();
			name.clear();
			cout << "\n請更改玩家名稱:";
			getline(cin, name);
			cout << "\n玩家名稱:" << name << "\t是否想更改玩家名稱 ( y or n) :";
			cin >> choice;
			cin.ignore();
		}
		else 
		{
			cout << "\n請重新輸入( y or n):";
			cin >> choice;
			cout << endl;
		}
	}
	system("cls");
}