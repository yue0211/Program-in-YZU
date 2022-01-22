#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace::std;

struct MemberRecord
{
   char IDNumber[ 12 ]={};   // account number
   char password[ 24 ]={};   // password
   char name[ 8 ]={};        // name
};

// input memberDetails from the file Members.dat
void loadMemberDetails( vector< MemberRecord > &memberDetails );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// login
void login( const vector< MemberRecord > &memberDetails );

// there exists a member with specified IDNumber and password
bool valid( char IDNumber[], char password[],
            const vector< MemberRecord > &memberDetails );

// add a new member
void registration( vector< MemberRecord > &memberDetails );

// return true if IDNumber is a legal ID number
bool legalID( char IDNumber[] );

// return true if IDNumber belongs to memberDetails
bool existingID( char IDNumber[], const vector< MemberRecord > &memberDetails );

// output all memberDetails into the file Members.dat
void saveMemberDetails( const vector< MemberRecord > &memberDetails );

int main()
{
   vector< MemberRecord > memberDetails ; // member details for all members
   int numMembers = 0;                     // number of members

   loadMemberDetails( memberDetails );
   
   cout << "Welcome to the Cashbox Party World!\n\n";

   int choice;

   while( true )
   {
      cout << "1 - Login\n";
      cout << "2 - Registration\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch ( choice )
      {
      case 1:
         login( memberDetails );
         break;

      case 2:
         registration( memberDetails );
         break;

      case 3:
         saveMemberDetails( memberDetails );
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;

      default:
         cout << "\nIncorrect choice!\n";
         break;
      }
   }

   system( "pause" );
}
// input memberDetails from the file Members.dat
void loadMemberDetails( vector< MemberRecord > &memberDetails )
{
	 ifstream a("Members.dat",ios::in);      //將檔案輸入資料到程式 
	 MemberRecord temp;
	 while(!a.eof()) 
	 {
	 	a>>temp.IDNumber;
	 	a>>temp.password;
	 	a>>temp.name;
	 	memberDetails.push_back(temp);

	 }
	a.close(); 
} 

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end )    //輸入一個整數介於 begin 和 end 之間 
{
	string integer;                    
	cin>>integer;
	if(integer[0]-48>=begin&&integer[0]-48<=end&&integer.size()==1) 
	{
		return integer[0]-48;
	}
	else
	{
		return -1;
	}
	
	
}
// login
void login( const vector< MemberRecord > &memberDetails )
{
	 char number[12],password[24];
	 cout<<"Please enter your ID number:";
     cin>>number;
	 cout<<"Enter your password:";
	 cin>>password;
	 cout<<endl;
     while(!valid( number,password,memberDetails )||!legalID( number))  //如果是無效帳戶或是不合法的帳號 就重新輸入 
     {
     	cout<<"Invalid account number or password. Please try again."<<endl<<endl;
     	cout<<"Please enter your ID number:";
     	cin>>number;
		cout<<"Enter your password:";
		cin>>password;   
		cout<<endl;	   	   	
	 }
	
}
// there exists a member with specified IDNumber and password
bool valid( char IDNumber[], char password[],const vector< MemberRecord > &memberDetails )
{
	for(int i=0;i<memberDetails.size();i++)
	{
		if(strcmp(IDNumber,memberDetails[i].IDNumber)==0)
		{
			if(strcmp(password,memberDetails[i].password)==0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}
// add a new member
void registration( vector< MemberRecord > &memberDetails )
{
	char number[12]={},names[8]={},password[24]={};
	cout<<"Input your ID number:";
	cin>>number;
	cout<<endl;
	if(existingID(number,memberDetails )==1)
	{
		cout<<"You are already a member!"<<endl;
	}
	else if(legalID(number)==0)
	{
		cout<<"The ID number "<<number<<" is illegal."<<endl<<endl;
	}
	else
	{
		cout<<"Input your Name: ";
		cin>>names;
		cout<<endl;
		cout<<"Choose a password:";
		cin>>password;
		cout<<endl;
		cout<<"Registration Completed!"<<endl<<endl;
		MemberRecord temp;		               //將新註冊的帳號存到 memberdetail 中 
		strcpy(temp.IDNumber,  number);
		strcpy(temp.password,  password);
		strcpy(temp.name,  names);
		memberDetails.push_back(temp);
	}
}
// return true if IDNumber is a legal ID number
bool legalID( char IDNumber[] )
{
	 if(IDNumber[0]<65||IDNumber[0]>90)  //如果number開頭不是A~Z 即錯 
	 {
	 	return false;
	 }
	 string a=IDNumber;
	 if( a.size() != 10 )   //如果number總數不是10 即錯 
	 {
	 	return false;
	 }
	 int x;
	 if( a.size() == 10 && a[0] >= 65 && a[0] <= 90 )    //將開頭的英文字母轉換成數字並放在字串中最前面的兩個位置 
	 {  	 
	 	for(int i=65,k=48;i<=72;i++,k++)
	 	{
			if(a[0]==i)
	 		{
	 			for(int h=9;h>=1;h--)
	 			{
	 				a[h+1]=a[h];	
				}
					a[0]=49;
					a[1]=k;
				break;
			}	 	
	 	}
	 	for(int i=74,k=56;i<=75;i++,k++)
	 	{
			if(a[0]==i)
	 		{
	 			for(int h=9;h>=1;h--)
	 			{
	 				a[h+1]=a[h];	
				}
					a[0]=49;
					a[1]=k;
				break;	
			}	 	
	 	}
	 	for(int i=76,k=48;i<=79;i++,k++)
	 	{
			if(a[0]==i)
	 		{
	 			for(int h=9;h>=1;h--)
	 			{
	 				a[h+1]=a[h];	
				}
					a[0]=50;
					a[1]=k;
				break;	
			}	 	
	 	}
	 	for(int i=80,k=51;i<=86;i++,k++)
	 	{
			if(a[0]==i)
	 		{
	 			for(int h=9;h>=1;h--)
	 			{
	 				a[h+1]=a[h];	
				}
					a[0]=50;
					a[1]=k;
				break;	
			}	 	
	 	}
	 	if(a[0]==87)
	 	{
	 		for(int h=9;h>=1;h--)
	 		{
	 			a[h+1]=a[h];	
			}
			a[0]=51;
			a[1]=50;
		}	
	 	if(a[0]==90)
	 	{
	 		for(int h=9;h>=1;h--)
	 		{
	 			a[h+1]=a[h];	
			}
			a[0]=51;
			a[1]=51;
		}	
		if(a[0]==73)
	 	{
	 		for(int h=9;h>=1;h--)
	 		{
	 			a[h+1]=a[h];	
			}
			a[0]=51;
			a[1]=52;
		}	
		if(a[0]==79)
	 	{
	 		for(int h=9;h>=1;h--)
	 		{
	 			a[h+1]=a[h];	
			}
			a[0]=51;
			a[1]=53;
		}	
		for(int i=88,k=48;i<=89;i++,k++)
	 	{
			if(a[0]==i)
	 		{
	 			for(int h=9;h>=1;h--)
	 			{
	 				a[h+1]=a[h];	
				}
					a[0]=51;
					a[1]=k;
				break;
			}	 	
	 	}
	 	for(int i=0;i<=10;i++)
		{
			a[i] -= 48;
		}
		x = 10 - ((9*a[1]+a[0])+8*a[2]+7*a[3]+6*a[4]+5*a[5]+4*a[6]+3*a[7]+2*a[8]+a[9]) % 10;

		if(  x == 10 )     //如果X=10 就讓X=0 
		{
			x = 0;
		}
		
		if( x == a[10] )   //如果X=身分證最後一個數字 即對 
		{
			return 1;
		}
		else            //如果X!=身分證最後一個數字 即錯 
		{
			return 0;
		}	
		
	 }
}
// return true if IDNumber belongs to memberDetails
bool existingID( char IDNumber[], const vector< MemberRecord > &memberDetails )
{
	 for(int i=0;i<memberDetails.size();i++)
	{
		if(strcmp(IDNumber,memberDetails[i].IDNumber)==0)
		{
			return true;
		}
	}
	return false;
	 
}
// output all memberDetails into the file Members.dat
void saveMemberDetails( const vector< MemberRecord > &memberDetails )
{
	ofstream a("Members.dat",ios::out);          //存檔用 
	for(int i=0;i < memberDetails.size();i++)
	{
		a<<memberDetails[i].IDNumber<<endl;
		a<<memberDetails[i].password<<endl;
		a<<memberDetails[i].name<<endl;
	}
	a.close();
}


        
















