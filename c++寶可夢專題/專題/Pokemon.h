#ifndef POKEMON_H
#define POKEMON_H
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Pokemon
{
	public:
		Pokemon();
		virtual void setData() = 0;  //用於設定寶可夢數值
		virtual void choice() = 0;  //用於決定寶可夢種類
		virtual void Fight(Pokemon* NPC) = 0;  //用於寶可夢對戰
	    string getname();
		int getSpeed();
		int getAttack();
		int getAbility();
		int getDefence();
		int getHp();
		int getMaxHp();
		void originalStatus();
		string getType();
		void setHp(int attack);
		void setHp2(int rise);
		void printpicture();
		void printpicture2();
		void printpicture3();
		void cleanpicture();
		void printability();
		void printability2();
		void printability3();
		void BeforeCatch();
		int getTrack();

		class WrongFail:public exception
		{
			public:
				WrongFail();
		};
	protected:
		int track;  //用於追蹤是否有抓到寶
		int track2=0;  //計算中毒回合數
		int track3=0;  //計算降低速度回合數
		int track4 = 0;  //計算降低防禦力回合數
		int track5 = 0;  //計算降低攻擊力回合數
		int Hp = 0;
		int ATK=0;
		int DEF=0;
		int Speed=0;
		int Ability=0;
		int MaxHp = 0;
		int MaxAtk = 0;
		int MaxDef = 0;
		int MaxSpeed = 0;
		char name[11] = {};
		char pokemon[24][600] = {};  
		char type[9] = {};
};

class GrassPokemon :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[6] = "Grass";
		char name1[10] = "Bulbasaur";
		char name2[8] = "Ivysaur";
		char name3[9] = "Venusaur";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};
class FirePokemon :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[5] = "Fire";
		char name1[11] = "Charmander";
		char name2[11] = "Charmeleon";
		char name3[10] = "Charizard";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};
class WaterPokemon :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[6] = "Water";
		char name1[9] = "Squirtle";
		char name2[10] = "Wartortle";
		char name3[10] = "Blastoise";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};
class BugPokemon1 :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[4] = "Bug";
		char name1[9] = "Caterpie";
		char name2[8] = "Metapod";
		char name3[11] = "Butterfree";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};
class BugPokemon2 :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[4] = "Bug";
		char name1[7] = "Weedle";
		char name2[7] = "Kakuna";
		char name3[9] = "Beedrill";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};
class FlyingPokemon1 :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[7] = "Flying";
		char name1[7] = "Pidgey";
		char name2[10] = "Pidgeotto";
		char name3[8] = "Pidgeot";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};
class NormalPokemon :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[7] = "Normal";
		char name1[8] = "Rattata";
		char name2[9] = "Raticate";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};

class FlyingPokemon2 :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[7] = "Flying";
		char name1[8] = "Spearow";
		char name2[7] = "Fearow";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};
class PoisonPokemon1 :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[7] = "Poison";
		char name1[6] = "Ekans";
		char name2[6] = "Arbok";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};
class ElectricPokemon :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[9] = "Electric";
		char name1[8] = "Pikachu";
		char name2[7] = "Raichu";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};
class GroundPokemon :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[7] = "Ground";
		char name1[10] = "Sandshrew";
		char name2[10] = "Sandslash";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};
class PoisonPokemon2 :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[7] = "Poison";
		char name1[10] = "Nidoran♀";
		char name2[9] = "Nidorina";
		char name3[10] = "Nidoqueen";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};
class PoisonPokemon3 :public Pokemon
{
	public:
		void setData();
		void choice();
		void Fight(Pokemon* NPC);
	private:
		char type1[7] = "Poison";
		char name1[10] = "Nidoran♂";
		vector<int> Hp1;
		vector<int> ATK1;
		vector<int> DEF1;
		vector<int> Speed1;
		vector<int> Ability1;
};

#endif 


