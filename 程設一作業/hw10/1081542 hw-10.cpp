#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstring>

using namespace::std;

struct Date
{
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
};

struct MemberRecord
{
	char IDNumber[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };   // account number
	char password[24] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };   // password
	char name[8] = { 0,0,0,0,0,0,0,0 };        // name
};

struct ReservationRecord
{
	char IDNumber[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 }; // account number
	int branchCode = 0;      // branch code
	Date date;           // reservation date
	int numCustomers = 0;    // number of customers
};

char branchNames[17][24] = { "", "Taipei Dunhua South", "Taipei SOGO",
									 "Taipei Songjiang",    "Taipei Nanjing",
									 "Taipei Linsen",       "Taipei Zhonghua New",
									 "Banqiao Guanqian",    "Yonghe Lehua",
									 "Taoyuan Zhonghua",    "Taoyuan Nankan",
									 "Zhongli Zhongyang",   "Hsinchu Beida",
									 "Taichung Ziyou",      "Chiayi Ren'ai",
									 "Tainan Ximen",        "Kaohsiung Zhonghua New" };

// input memberDetails from the file Members.txt
void loadMemberDetails(vector< MemberRecord >& memberDetails);

// input reservations from the file Reservations.txt
void loadReservations(vector< ReservationRecord >& reservations);

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end);

// login and display the submenu
void login(const vector< MemberRecord >& memberDetails,
	vector< ReservationRecord >& reservations);

// there exists a member with specified IDNumber and password
bool valid(char IDNumber[], char password[],
	const vector< MemberRecord >& memberDetails);

// add a new reservation for the member with specified IDnumber
void reservation(char IDNumber[], vector< ReservationRecord >& reservations);

// compute the current date
void compCurrentDate(Date& currentDate);

// compute 7 dates which is starting from the current date
void compAvailableDates(Date currentDate, Date availableDates[]);

// display all fields of reservation
void output(ReservationRecord reservation);

// display all reservations for the member with specified IDnumber,
// then let the member to choose one of them to delete
void queryDelete(char IDNumber[], vector< ReservationRecord >& reservations);

// add a new member
void registration(vector< MemberRecord >& memberDetails);

// return true if IDNumber is a legal ID number
bool legalID(char IDNumber[]);

// return true if IDNumber belongs to memberDetails
bool existingID(char IDNumber[], const vector< MemberRecord >& memberDetails);

// output all memberDetails into the file Members.txt
void saveMemberDetails(const vector< MemberRecord >& memberDetails);

// output all reservations into the file Reservations.txt
void saveReservations(const vector< ReservationRecord >& reservations);

int days(Date& currentDate);

bool leap_year(int year);

int main()
{
	vector< MemberRecord > memberDetails; // member details for all members
	vector< ReservationRecord > reservations; // all reservations

	loadMemberDetails(memberDetails);
	loadReservations(reservations);

	cout << "Welcome to the Cashbox Party World!\n\n";

	int choice;

	while (true)
	{
		cout << "1 - Login\n";
		cout << "2 - Registration\n";
		cout << "3 - End\n";

		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			login(memberDetails, reservations);
			break;

		case 2:
			registration(memberDetails);
			break;

		case 3:
			saveMemberDetails(memberDetails);
			saveReservations(reservations);
			cout << "Thank you! Goodbye!\n\n";
			system("pause");
			return 0;

		default:
			cout << "\nIncorrect choice!\n";
			break;
		}
	}

	system("pause");
}

// input memberDetails from the file Members.txt
void loadMemberDetails(vector< MemberRecord >& memberDetails)
{
	ifstream a("Members.txt", ios::in | ios::binary);

	if (!a)        //如果 Members.txt不存在則建檔 
	{
		ofstream a("Members.txt", ios::out | ios::binary);
		a.close();       //開完檔要關檔 
	}
	else
	{
		MemberRecord temp;


		a.seekg(0, ios::end);  //seekg的第一個參數是偏移量 ,第二個參數是起始地址 
		int end = a.tellg();

		a.seekg(0, ios::beg);
		int beg = a.tellg();

		a.clear();

		int times = (end - beg) / sizeof(MemberRecord);  //計算讀取所需花的時間 

		for (int i(1); i <= times; i++)
		{
			a.read(reinterpret_cast<char*> (&temp.IDNumber), sizeof(temp.IDNumber));
			a.read(reinterpret_cast<char*> (&temp.password), sizeof(temp.password));
			a.read(reinterpret_cast<char*> (&temp.name), sizeof(temp.name));

			memberDetails.push_back(temp);
		}

		a.close();
	}
}

// input reservations from the file Reservations.txt
void loadReservations(vector< ReservationRecord >& reservations)
{
	ifstream a("Reservations.txt", ios::in | ios::binary);

	if (!a)  //如果 Reservations.txt.txt不存在則建檔  
	{
		ofstream a("Reservations.txt", ios::out | ios::binary);
		a.close();
	}
	else
	{
		ReservationRecord temp;

		a.seekg(0, ios::end); 	//seekg的第一個參數是偏移量 ,第二個參數是起始地址 
		int end = a.tellg();

//		a.seekg(0, ios::beg);
//		int beg = a.tellg();

//		a.clear();

		int times = (end /*- beg*/) / sizeof(ReservationRecord);   //計算讀取所需花的時間 

		for (int i(1); i <= times; i++)
		{
			a.read(reinterpret_cast<char*> (&temp.IDNumber), sizeof(temp.IDNumber));
			a.read(reinterpret_cast<char*> (&temp.branchCode), sizeof(temp.branchCode));
			a.read(reinterpret_cast<char*> (&temp.date), sizeof(temp.date));
			a.read(reinterpret_cast<char*> (&temp.numCustomers), sizeof(temp.numCustomers));

			reservations.push_back(temp);
		}

		a.close();
	}
}

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end)
{
	string a;

	cin >> a;

	if (a.size() == 1 && a[0] >= begin + 48 && a[0] <= end + 48)
	{
		return a[0] - 48;
	}

	if (a.size() == 2 && ((a[0] - 48) * 10 + a[1]) >= begin + 48 && ((a[0] - 48) * 10 + a[1]) <= end + 48)
	{
		return ((a[0] - 48) * 10 + a[1]) - 48;
	}
	else
	{
		return -1;
	}
}

// login and display the submenu
void login(const vector< MemberRecord >& memberDetails,
	vector< ReservationRecord >& reservations)
{
	char IDNumber[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	char password[24] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	cout << "Please enter your ID number: ";

	cin >> IDNumber;

	cout << endl << "Enter your password: ";

	cin >> password;

	while (!valid(IDNumber, password, memberDetails) || !legalID(IDNumber))   //當帳號無效或著不合法執行此迴圈 
	{
		cout << endl << "Invalid account number or password. Please try again." << endl << endl;

		cout << "Please enter your ID number: ";

		cin >> IDNumber;

		cout << endl << "Enter your password: ";

		cin >> password;

		cout << endl;
	}

	int choice(0);

	while (1)
	{
		cout << endl << "1 - Make Reservation" << endl << "2 - Reservation Enquiry/Canceling" << endl << "3 - End" << endl;

		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			reservation(IDNumber, reservations);
			break;

		case 2:
			queryDelete(IDNumber, reservations);
			break;

		case 3:
			return;
		}
	}

}

// there exists a member with specified IDNumber and password
bool valid(char IDNumber[], char password[],
	const vector< MemberRecord >& memberDetails)
{
	for(int i=0;i<memberDetails.size();i++)
	{
		if(strcmp(IDNumber,memberDetails[i].IDNumber)==0)    //經過strcmp比較後回傳0 代表兩數相等 
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

// add a new reservation for the member with specified IDnumber
void reservation(char IDNumber[], vector< ReservationRecord >& reservations)
{
	for (int i = 1; i < 17; i++) {
		cout << i << ". " << branchNames[i] << endl;
	}
	int choice1,choice2, choice3, choice4;
	do cout << "\nEnter your choice (1~end): ";
	while ((choice1 = inputAnInteger(0, 16)) == -1);
	if (choice1 == 0)		//如果choice==0回到呼叫 reservation 的地方
	{    			 
		return;
	}
	Date currentDate,availableDates[8];
	cout << endl;
	compCurrentDate(currentDate);      //計算當前時間 
	compAvailableDates(currentDate,availableDates);    //計算可預約的時間 
	do cout << "\nEnter your choice (1 to end): ";
	while ((choice2 = inputAnInteger(0, 7)) == -1);
	cout << endl;
	if (choice2 == 0)
	{
		return;
	}
	int hourStart=currentDate.hour;
	if (currentDate.hour == 23)   //如果訂位的時間是晚上23點 則只能訂位明天的時段 
	{
		hourStart = 0;
	}
	do cout << "\nEnter hour (" << hourStart << "~23): ";
	while ((choice3 = inputAnInteger(hourStart, 23)) == -1);
	cout << endl;

	do cout << "\nEnter the number of customers (1~30, 0 to end): ";
	while ((choice4 = inputAnInteger(0, 30)) == -1);
	cout << endl;
	if (choice4 == 0)
	{
		return;
	}
	
	choice2-=1;  //為了解決bug打得
	 
	cout << "                    Branch          Date    Hour    No of Customers" << endl;
	cout << setw(26) << branchNames[choice1]<<"   ";
	cout << availableDates[choice2].year << "-" << availableDates[choice2].month << "-" << availableDates[choice2].day;
	cout << setw(8) << choice3;
	cout << setw(19) << choice4 << endl;
	cout << endl << "Reservation Completed!" << endl;
	
	ReservationRecord temp;         //將訂位資料儲存到 向量reservations
	strcpy(temp.IDNumber, IDNumber);
	temp.branchCode = choice1;
	temp.date.year = availableDates[choice2].year;
	temp.date.month = availableDates[choice2].month;
	temp.date.day = availableDates[choice2].day;
	temp.date.hour = choice3;
	temp.numCustomers = choice4;
	reservations.push_back(temp);
}

// compute the current date
void compCurrentDate(Date& currentDate)
{
	int second=static_cast<int>(time(0))+8*60*60;    //計算從1970年的第0秒到現在的時間，多打8*60*60是因為台灣時間跟英國差了八小時 
	int day;
	int hour;
	int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31}; //day[0]用不到 
	int month=1;
	int year=1970;
	int secondsperyear=365*24*60*60;
	if( leap_year( year ) )    //閏年的話要加一天 
	{
		secondsperyear+=24*60*60;
	}
	while(second>=secondsperyear)
	{
		second-=secondsperyear;
		year++;
		
		secondsperyear=365*24*60*60;
		if(leap_year( year ))        
		{
			secondsperyear+=24*60*60;		
		}				
	}
	currentDate.year=year;
	if(leap_year( year ))  //閏年 2月有29天  
	{
		days[2]=29;
	}
	while(second>=days[month]*24*60*60)  //second目前只剩1年的秒數 
	{
		second-=days[month]*24*60*60;
		month++;	
	}
	
	currentDate.month=month;
	
	day=second/(24*60*60)+1;
	
	currentDate.day=day;
	
	second%=24*60*60;
	hour=second/(60*60);
	
	currentDate.hour=hour;
	//直接在呼叫此function時 輸出 
	
	
	//currentDate.hour=newtime.tm
	cout<<endl<<"The current hour is "<<currentDate.year<<'/'<<currentDate.month<<'/'<<currentDate.day<<"\:"<<currentDate.hour<<endl<<endl;						   
							   														   
}

// compute 7 dates which is starting from the current date
void compAvailableDates(Date currentDate, Date availableDates[])
{
	
	cout<<"Available days:"<<endl<<endl;
	
	for(int i=0;i<=6;i++)    //可預約 7天 
	{
		availableDates[i].year=currentDate.year;
		availableDates[i].month=currentDate.month;
		availableDates[i].day=currentDate.day+i;
	}
	for(int i=0;i<=6;i++)
	{
		if(availableDates[i].day>31)
		{
			if(availableDates[i].month==12)
			{
				availableDates[i].month=1;
			}
			else
			{
				availableDates[i].month=availableDates[i].month+1;
			}
			availableDates[i].day=availableDates[i].day-31;
		}
	}
	for(int i=0,a=1;i<=6;i++,a++)	//直接在呼叫此function時 輸出 
	{
    	cout<<a<<'.'<<" "<<availableDates[i].year<<'/'<<availableDates[i].month<<'/'<<availableDates[i].day<<endl;
	}

}

// display all fields of reservation
void output(ReservationRecord reservation)  //使用查詢功能時用來輸出帳號已選的訂單 
{
	cout << setw(24) << branchNames[reservation.branchCode];

	int n1(0), n2(0), n3(0), copy1 = reservation.date.year, copy2 = reservation.date.month, copy3 = reservation.date.day;

	for (; copy1 != 0; n1++)
	{
		copy1 /= 10;
	}

	for (; copy2 != 0; n2++)
	{
		copy2 /= 10;
	}

	for (; copy3 != 0; n3++)
	{
		copy3 /= 10;
	}

	for (int i(12 - n1 - n2 - n3); i > 0; i--)
	{
		cout << " ";
	}

	cout << reservation.date.year << "-" << reservation.date.month << "-" << reservation.date.day;

	cout << setw(8) << reservation.date.hour;

	cout << setw(19) << reservation.numCustomers << endl;
}

// display all reservations for the member with specified IDnumber,
// then let the member to choose one of them to delete
void queryDelete(char IDNumber[], vector< ReservationRecord >& reservations)
{
	cout << "                    Branch          Date    Hour    No of Customers" << endl;

	vector< ReservationRecord >::const_iterator iter = reservations.begin();
	int arr[1000] = {};

	int i(0), num(0);

	for (; iter != reservations.end(); ++iter, ++num)
	{
		arr[i] = num;

		if (!strcmp(reservations[num].IDNumber, IDNumber) )
		{
			cout << i + 1 << ".";
			output(reservations[num]);
			++i;
		}
	}

	int choice(0);

	do cout << "\nChoose a reservation to cancel (0: keep all reservations): ";
	while ((choice = inputAnInteger(0, i)) == -1);
	cout << endl;

	if (choice == 0)
	{
		return;
	}

	reservations.erase(reservations.begin() + arr[ choice - 1] );  //清除想要取消的訂位資料 

}

// add a new member
void registration(vector< MemberRecord >& memberDetails)
{
	char IDNumber[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	char password[24] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	char name[8] = { 0,0,0,0,0,0,0,0 };

	cout << "Input your ID Number: ";

	cin >> IDNumber;

	if (existingID(IDNumber, memberDetails))
	{
		cout << endl << "You are already a member!" << endl << endl;
	}
	else if (!legalID(IDNumber))
	{
		cout << endl << "The ID number " << IDNumber << " is illegal." << endl << endl;
	}
	else
	{
		cout << endl << "Input your Name: ";

		cin >> name;

		cout << endl << "Choose a password: ";

		cin >> password;

		cout << endl << "Registration Completed!" << endl << endl;

		MemberRecord temp;   //註冊成功後，將帳號資料儲存到向量 memberDetails

		strcpy(temp.IDNumber, IDNumber);
		strcpy(temp.password, password);
		strcpy(temp.name, name);

		memberDetails.push_back(temp);

	}
}

// return true if IDNumber is a legal ID number
bool legalID(char IDNumber[])  //帳號規則 
{
	int interger[10];
    int sum = 0;

    switch (IDNumber[0])
	{
	    case 'A': interger[0] = 10; break;   case 'P': interger[0] = 23; break;
	    case 'B': interger[0] = 11; break;   case 'Q': interger[0] = 24; break;
	    case 'C': interger[0] = 12; break;   case 'R': interger[0] = 25; break;
	    case 'D': interger[0] = 13; break;   case 'S': interger[0] = 26; break;
	    case 'E': interger[0] = 14; break;   case 'T': interger[0] = 27; break;
	    case 'F': interger[0] = 15; break;   case 'U': interger[0] = 28; break;
	    case 'G': interger[0] = 16; break;   case 'V': interger[0] = 29; break;
	    case 'H': interger[0] = 17; break;   case 'W': interger[0] = 32; break;
	    case 'I': interger[0] = 34; break;   case 'X': interger[0] = 30; break;
	    case 'J': interger[0] = 18; break;   case 'Y': interger[0] = 31; break;
	    case 'K': interger[0] = 19; break;   case 'Z': interger[0] = 33; break;
	    case 'L': interger[0] = 20; break;
	    case 'M': interger[0] = 21; break;
	    case 'N': interger[0] = 22; break;
	    case 'O': interger[0] = 35; break;
    }
    for (int i = 1; i < 10; i++)
	{
        interger[i] = static_cast<int>(IDNumber[i]) - '0';
    }
    
    if (interger[1] != 1 && interger[1] != 2)
	{
        return false;
    }
    
    sum = (interger[0] % 10) * 9 + interger[0] / 10;
    
    for (int i = 1; i < 9; i++)
	{
        sum += interger[i] * (9 - i);
    }
    
    if (sum % 10 == 0) 
	{
        if (interger[9] != 0) 
		{
            return false;
        }
    }
    
    else if (interger[9] != (10 - (sum % 10)))
	{
        return false;
    }
    return true;
}

// return true if IDNumber belongs to memberDetails
bool existingID(char IDNumber[], const vector< MemberRecord >& memberDetails)  //檢查是否存在 
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

// output all memberDetails into the file Members.txt
void saveMemberDetails(const vector< MemberRecord >& memberDetails)
{
	ofstream a("Members.txt",ios::out|ios::binary);
	vector<MemberRecord>::const_iterator iter=memberDetails.begin();
	for(;iter!=memberDetails.end();iter++)
	{
		a.write(reinterpret_cast<const char*>(&iter->IDNumber),sizeof(iter->IDNumber));
		a.write(reinterpret_cast<const char*>(&iter->password),sizeof(iter->password));
		a.write(reinterpret_cast<const char*>(&iter->name),sizeof(iter->name));
	}
	a.close();
	
}

// output all reservations into the file Reservations.txt
void saveReservations(const vector< ReservationRecord >& reservations)
{
	ofstream a("Members.txt",ios::out|ios::binary);
	vector<ReservationRecord>::const_iterator iter=reservations.begin();
	for(;iter!=reservations.end();iter++)
	{
		a.write(reinterpret_cast<const char*>(&iter->IDNumber),sizeof(iter->IDNumber));
		a.write(reinterpret_cast<const char*>(&iter->branchCode),sizeof(iter->branchCode));
		a.write(reinterpret_cast<const char*>(&iter->date),sizeof(iter->date));
		a.write(reinterpret_cast<const char*>(&iter->numCustomers),sizeof(iter->numCustomers));
	}
	a.close();
}

bool leap_year(int year)      //計算閏年的方法 
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		return 1;
	}

	return 0;
}
