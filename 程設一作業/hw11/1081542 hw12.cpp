#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstring>
#include <cstdlib>

using namespace::std;

char foods[14][48] = { "",
						   "Pork XiaoLongBao (12)",
						   "Steamed Vegetable and Ground Pork Dumplings (8)",
						   "Steamed Shrimp and Pork Dumplings (8)",
						   "Steamed Fish Dumplings (8)",
						   "Steamed Vegetarian Mushroom Dumplings (8)",
						   "Steamed Shrimp and Pork Shao Mai (12)",
						   "Pork Buns (5)",
						   "Vegetable and Ground Pork Buns (5)",
						   "Red Bean Buns (5)",
						   "Sesame Buns (5)",
						   "Taro Buns (5)",
						   "Vegetarian Mushroom Buns (5)",
						   "Golden Lava Buns (5)" };

int price[14] = { 0, 220, 176, 216, 200, 200, 432, 225,
					      225, 200, 200, 225, 250, 225 };

struct Date
{
	int year = 0;
	int month = 0;
	int day = 0;
};

struct Account
{
	char email[40] = {}; // used as the account number
	char password[20] = {};
	char name[12] = {};
	char address[80] = {};
	char phone[12] = {};
	int cart[14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; // Cart[i] is the quantity of food #i in the shopping cart
};

struct Order
{
	char orderNumber[12] = {};
	char email[40] = {};
	Date deliveryDate;
	Date arrivalDate;
	int quantity[14] = {}; // quantity[i] is the quantity of food #i in the order
};

// load all accounts details from the file Accounts.dat
void loadAccountDetails(vector< Account >& accountDetails);

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end);

// add a new account to the file Accounts.dat
void registration(vector< Account >& accountDetails);

// return true if email belongs to accountDetails
bool exists(char email[], const vector< Account >& accountDetails);

// save all elements in accountDetails to the file Accounts.dat
void saveAllAccounts(const vector< Account >& accountDetails);

// login and call shopping
void login(vector< Account >& accountDetails);

// return true if there exists an account with specified email and password; and
// put the account with specified email and password into account
bool valid(char email[], char password[], Account& account,
	const vector< Account >& accountDetails);

// add chosen Foods to the shopping cart
void shopping(Account& account);

// return true if the shopping cart is empty
bool emptyCart(const Account& account);

// display the shopping cart in account
bool displayCart(const Account& account);

// append account in the file Accounts.dat
void saveAccount(const Account& account);

// update the shopping cart in account
void updateCart(Account& account);

// generate a Bill and reset account.cart
void check(Account& account);

// compute the current date
void compCurrentDate(Date& currentDate);

// open the file Orders.dat and call displayOrderDetails twice
void createOrder(const Account& account, const Order& order);

// write an order to Orders.txt or display it on the output window depending on os
void displayOrderDetails(ostream& os, const Account& account, const Order& order);

int main()
{
	vector< Account > accountDetails; // account details for all accounts

	loadAccountDetails(accountDetails);

	cout << "Welcome to DintaiFung Shopping Mall!\n";

	srand(static_cast<int>(time(0)));    //為了隨機製造訂單編碼 所以需要打此行 

	int choice;

	while (true)
	{
		cout << "\n1 - Registration\n";
		cout << "2 - Login\n";
		cout << "3 - End\n";

		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			registration(accountDetails);
			break;

		case 2:
			login(accountDetails);
			break;

		case 3:
			saveAllAccounts(accountDetails);
			cout << "Thank you! Goodbye!\n\n";
			system("pause");
			return 0;
		}
	}

	system("pause");
}

// load all accounts details from the file Accounts.dat
void loadAccountDetails(vector< Account >& accountDetails)   //載入檔案 
{
	ifstream a("Accounts.dat", ios::in | ios::binary);

	if (!a)  //如果 Accounts.dat不存在則建檔 
	{
		ofstream a("Accounts.dat", ios::out | ios::binary);
		a.close();
	}
	else
	{
		Account temp;

		a.seekg(0, ios::end);   //seekg的第一個參數是偏移量 ,第二個參數是起始地址  
		int end = a.tellg();

		a.seekg(0, ios::beg);

		int times = end / sizeof(Account);   //計算讀取所需花的時間  

		for (int i(1); i <= times; i++)
		{
			a.read(reinterpret_cast<char*> (&temp.email), sizeof(temp.email));
			a.read(reinterpret_cast<char*> (&temp.password), sizeof(temp.password));
			a.read(reinterpret_cast<char*> (&temp.name), sizeof(temp.name));
			a.read(reinterpret_cast<char*> (&temp.address), sizeof(temp.address));
			a.read(reinterpret_cast<char*> (&temp.phone), sizeof(temp.phone));
			a.read(reinterpret_cast<char*> (&temp.cart), sizeof(temp.cart));

			accountDetails.push_back(temp);
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

	if (a.size() == 3 && ((a[0] - 48) * 100 + (a[1] - 48) * 10 + a[2]) >= begin + 48 && ((a[0] - 48) * 100 + (a[1] - 48) * 10 + a[2]) <= end + 48)
	{
		return ((a[0] - 48) * 100 + (a[1] - 48) * 10 + a[2]) - 48;
	}

	if (a.size() == 4 && ((a[0] - 48) * 1000 + (a[1] - 48) * 100 + (a[2] - 48) * 10 + a[3]) >= begin + 48 && ((a[0] - 48) * 1000 + (a[1] - 48) * 100 + (a[2] - 48) * 10 + a[3]) <= end + 48)
	{
		return ((a[0] - 48) * 1000 + (a[1] - 48) * 100 + (a[2] - 48) * 10 + a[3]) - 48;
	}

	if (a.size() == 5 && ((a[0] - 48) * 10000 + (a[1] - 48) * 1000 + (a[2] - 48) * 100 + (a[3] - 48) * 10 + a[4]) >= begin + 48 && ((a[0] - 48) * 10000 + (a[1] - 48) * 1000 + (a[2] - 48) * 100 + (a[3] - 48) * 10 + a[4]) <= end + 48)
	{
		return ((a[0] - 48) * 10000 + (a[1] - 48) * 1000 + (a[2] - 48) * 100 + (a[3] - 48) * 10 + a[4]) - 48;
	}

	if (a.size() == 6 && ((a[0] - 48) * 100000 + (a[1] - 48) * 10000 + (a[2] - 48) * 1000 + (a[3] - 48) * 100 + (a[4] - 48) * 10 + a[5]) >= begin + 48 && ((a[0] - 48) * 100000 + (a[1] - 48) * 10000 + (a[2] - 48) * 1000 + (a[3] - 48) * 100 + (a[4] - 48) * 10 + a[5]) <= end + 48)
	{
		return ((a[0] - 48) * 100000 + (a[1] - 48) * 10000 + (a[2] - 48) * 1000 + (a[3] - 48) * 100 + (a[4] - 48) * 10 + a[5]) - 48;
	}

	if (a.size() == 7 && ((a[0] - 48) * 1000000 + (a[1] - 48) * 100000 + (a[2] - 48) * 10000 + (a[3] - 48) * 1000 + (a[4] - 48) * 100 + (a[5] - 48) * 10 + a[6]) >= begin + 48 && ((a[0] - 48) * 1000000 + (a[1] - 48) * 100000 + (a[2] - 48) * 10000 + (a[3] - 48) * 1000 + (a[4] - 48) * 100 + (a[5] - 48) * 10 + a[6]) <= end + 48)
	{
		return ((a[0] - 48) * 1000000 + (a[1] - 48) * 100000 + (a[2] - 48) * 10000 + (a[3] - 48) * 1000 + (a[4] - 48) * 100 + (a[5] - 48) * 10 + a[6]) - 48;
	}

	return -1;
}

// add a new account to the file Accounts.dat
void registration(vector< Account >& accountDetails)
{
	char email[40] = {};
	char password[20] = {};
	char name[12] = {};
	char address[80] = {};
	char phone[12] = {};

	cout << "Email address (Account number): ";

	cin >> email;

	if (exists(email, accountDetails))
	{
		cout << endl << "You are already a member!" << endl;
	}
	else
	{
		cout << "Password: ";

		cin >> password;

		cout << "Name: ";

		cin >> name;

		cout << "Shipping address: ";

		cin >> address;

		cout << "Contact phone number: ";

		cin >> phone;

		cout << endl << "Registration Completed!" << endl << endl;

		Account temp;

		strcpy_s(temp.email, email);
		strcpy_s(temp.password, password);
		strcpy_s(temp.name, name);
		strcpy_s(temp.address, address);
		strcpy_s(temp.phone, phone);

		accountDetails.push_back(temp);

		saveAccount(temp);
	}
}

// return true if email belongs to accountDetails
bool exists(char email[], const vector< Account >& accountDetails)
{
	vector< Account >::const_iterator iter = accountDetails.begin();

	bool tf = 0;

	for (; iter < accountDetails.end(); iter++)
	{
		if (strcmp((iter->email), email) == 0)
		{
			tf = 1;

			break;
		}
	}

	return tf;
}

// save all elements in accountDetails to the file Accounts.dat
void saveAllAccounts(const vector< Account >& accountDetails)   //存檔 
{
	fstream a("Accounts.dat", ios::out | ios::binary);

	vector< Account >::const_iterator iter = accountDetails.begin();

	for (; iter != accountDetails.end(); ++iter)
	{
		a.write(reinterpret_cast<const char*>(&iter->email), sizeof(iter->email));
		a.write(reinterpret_cast<const char*>(&iter->password), sizeof(iter->password));
		a.write(reinterpret_cast<const char*>(&iter->name), sizeof(iter->name));
		a.write(reinterpret_cast<const char*>(&iter->address), sizeof(iter->address));
		a.write(reinterpret_cast<const char*>(&iter->phone), sizeof(iter->phone));
		a.write(reinterpret_cast<const char*>(&iter->cart), sizeof(iter->cart));
	}
	a.close();
}

// login and call shopping
void login(vector< Account >& accountDetails)
{
	char email[40] = {};
	char password[20] = {};

	Account account;

	account.phone[11] = 13;

	do {
		cout << "Email address (0 to end): ";

		cin >> email;

		if (email[0] == 48 && email[1] == 0)   //當輸入0時 return 到呼叫的地方 
		{
			return;
		}

		cout << "Password: ";

		cin >> password;

		if (!valid(email, password, account, accountDetails))
		{
			cout << endl << "Invalid account number or password. Please try again." << endl << endl;
		}

	} while (!valid(email, password, account, accountDetails));

	cout << endl;

	int choice(1);

	while (choice > 0 && choice < 4)
	{
		if (choice == 3)
		{
			check(account);

			account.cart[0] = 1;
		}

		if (choice == 2)
		{
			updateCart(account);

			cout << "Your Shopping Cart Contents:" << endl;

			displayCart(account);
		}

		if (choice == 1)
		{
			for (int i(1); i < 14; i++)
			{
				cout << right << setw(2) << i << ". " << left << setw(50) << foods[i] << price[i] << endl;
			}

			if (!emptyCart(account))  //當cart不是空的時候要輸出此文字 
			{
				cout << endl << "14. View your shopping cart" << endl;
				account.phone[11] = 14;
			}
			else
			{
				account.phone[11] = 13;
			}

			shopping(account);
		}

		if (account.cart[0] == 0)
		{
			cout << "\n1. Continue Shopping" << endl
				<< "2. Update Cart" << endl
				<< "3. Check" << endl;

			do cout << "\nEnter your choice (1~3): ";
			while ((choice = inputAnInteger(1, 3)) == -1);
			cout << endl;
		}

		if (account.cart[0] == 1)
		{
			vector< Account >::iterator iter = accountDetails.begin();

			choice = 0;

			for (; iter < accountDetails.end(); iter++)
			{
				if (strcmp((iter->email), email) == 0 && strcmp((iter->password), password) == 0)
				{
					for (int i(1); i < 14; i++)
					{
						iter->cart[i] = account.cart[i];
					}
					break;
				}
			}
		}
	}
}

// return true if there exists an account with specified email and password; and
// put the account with specified email and password into account
bool valid(char email[], char password[], Account& account,
	const vector< Account >& accountDetails)
{
	vector< Account >::const_iterator iter = accountDetails.begin();

	bool tf = 0;

	for (; iter < accountDetails.end(); iter++)
	{
		if (strcmp((iter->email), email) == 0 && strcmp((iter->password), password) == 0)
		{
			tf = 1;

			strcpy_s(account.email, email);

			strcpy_s(account.password, password);

			strcpy_s(account.name, iter->name);

			strcpy_s(account.address, iter->address);

			strcpy_s(account.phone, iter->phone);

			for (int i(0); i < 14; i++)
			{
				account.cart[i] = iter->cart[i];
			}
			break;
		}
	}

	return tf;
}

// add chosen Foods to the shopping cart
void shopping(Account& account)
{
	int choice(0), choice2(0);

	do cout << "\nEnter your choice (0 to logout): ";
	while ((choice = inputAnInteger(0, account.phone[11])) == -1);
	cout << endl;

	if (choice == 0)   //登出用 
	{
		account.cart[0] = 1;
		return;
	}

	if (choice < 14)
	{
		do cout << "Enter the quantity: ";
		while ((choice2 = inputAnInteger(1, 4971026)) == -1);
		cout << endl;
	}

	account.cart[choice] += choice2;

	cout << "Your Shopping Cart Contents:" << endl;

	displayCart(account);
}

// return true if the shopping cart is empty
bool emptyCart(const Account& account)   //檢查cart是否為空 
{
	int number = 0;

	for (int i(0); i < 14; i++)
	{
		number += account.cart[i];
	}

	if (number == 0)
	{
		return true;
	}

	return false;
}

// display the shopping cart in account
bool displayCart(const Account& account)  //用來輸出 cart 
{
	long long total(0);

	cout << endl << "Code                                            Item  Price  Quantity  Subtotal" << endl;

	for (int i(1); i < 14; i++)
	{
		if (account.cart[i] > 0)
		{
			cout << right << setw(4) << i << setw(48) << foods[i] << setw(7) << price[i] << setw(10) << account.cart[i] << setw(10) << (price[i]) * (account.cart[i]) << endl;
			(total += (price[i] * account.cart[i]));
		}
	}

	cout << endl << "Total Cost: " << total << endl << endl;

	return 1;
}

// append account in the file Accounts.dat
void saveAccount(const Account& account)   //儲存一筆帳戶資料 
{
	fstream a("Accounts.dat", ios::app | ios::binary);

	a.write(reinterpret_cast<const char*>(account.email), sizeof(account.email));
	a.write(reinterpret_cast<const char*>(account.password), sizeof(account.password));
	a.write(reinterpret_cast<const char*>(account.name), sizeof(account.name));
	a.write(reinterpret_cast<const char*>(account.address), sizeof(account.address));
	a.write(reinterpret_cast<const char*>(account.phone), sizeof(account.phone));
	a.write(reinterpret_cast<const char*>(account.cart), sizeof(account.cart));

	a.close();
}

// update the shopping cart in account
void updateCart(Account& account)    //修改數量 
{
	int productCode, quantity;

	bool exist(0);

	do
	{
		cout << "\nEnter the product code: ";

		productCode = inputAnInteger(1, 14);

		if ((account.cart[productCode]) > 0)
		{
			exist = 1;
		}

	} while (exist == 0 || productCode == -1);
	cout << endl;

	do cout << "\nEnter the quantity: ";
	while ((quantity = inputAnInteger(0, 4971026)) == -1);
	cout << endl;

	account.cart[productCode] = quantity;
}

// generate a Bill and reset account.cart
void check(Account& account)
{
	Date currentDate;

	Order order;

	int year(0), month(0), day(0);

	cout << endl << "Enter arrival dateDate" << endl;

	cout << "year: ";
	cin >> year;

	cout << "month: ";
	cin >> month;

	cout << "day: ";
	cin >> day;

	cout << endl;

	cout << "Order number : " << (order.orderNumber[0] = rand() % 26 + 65) <<
								 (order.orderNumber[1] = rand() % 10 + 48) <<
							 	 (order.orderNumber[2] = rand() % 10 + 48) <<
								 (order.orderNumber[3] = rand() % 10 + 48) <<
								 (order.orderNumber[4] = rand() % 10 + 48) <<
								 (order.orderNumber[5] = rand() % 10 + 48) <<
								 (order.orderNumber[6] = rand() % 10 + 48) <<
								 (order.orderNumber[7] = rand() % 10 + 48) <<
								 (order.orderNumber[8] = rand() % 10 + 48) <<
								 (order.orderNumber[9] = rand() % 10 + 48) << endl;
		
	compCurrentDate(currentDate);

	cout << "Delivery Date: " << (order.deliveryDate.year = currentDate.year) << "/" << (order.deliveryDate.month = currentDate.month) << "/" <<(order.deliveryDate.day = currentDate.day) << endl;

	cout << "Arrival Date: " << (order.arrivalDate.year = year) << "/" << (order.arrivalDate.month = month) << "/" << (order.arrivalDate.day = day) << endl;

	cout << "Recipient: " << account.name << endl;

	cout << "Contact Phone Number: " << account.phone << endl;

	cout << "Shipping address :" << account.address << endl;

	for (int i(1); i < 14; i++)     //將帳號的訂購數量存到order 
	{
		order.quantity[i] = account.cart[i];
	}

	strcpy_s(order.email, account.email);

	createOrder(account, order);
	
	for (int i(1); i < 14; i++)  //結帳完要讓購物車的物品數量清空 
	{
		account.cart[i] = 0;
	}
}

// compute the current date
void compCurrentDate(Date& currentDate)
{
	tm newtime;
	__time64_t long_time;


	_time64(&long_time);

	_localtime64_s(&newtime, &long_time);


	currentDate.year = newtime.tm_year + 1900;
	currentDate.month = newtime.tm_mon + 1;
	currentDate.day = newtime.tm_mday;
}

// open the file Orders.txt and call displayOrderDetails twice
void createOrder(const Account& account, const Order& order)
{
	ofstream os("Orders.txt", ios::out);

	displayOrderDetails(os, account, order);

	displayOrderDetails(os, account, order);
}

// write an order to Orders.dat or display it on the output window depending on os
void displayOrderDetails(ostream& os, const Account& account, const Order& order)    //ofstream 的源頭是ostream  所以ostream可以用ofstream的功能 
{
	long long total(0);

	int size = os.tellp();

	if (size == 0)        //用於顯示在輸出視窗 
	{
		cout << endl << "Shopping details:" << endl;

		displayCart(account);

		cout << "An order has been created." << endl;

		os << "\n";  //讓file pointer可以不是0 
	}
	else       //用於寫進 Orders.dat
	{
		os << "Order number: " << order.orderNumber << endl       
			<< "Delivery Date: " << order.deliveryDate.year << "/" << order.deliveryDate.month << "/" << order.deliveryDate.day << endl
			<< "Arrival Date: " << order.arrivalDate.year << "/" << order.arrivalDate.month << "/" << order.arrivalDate.day << endl
			<< "Recipient: " << account.name << endl
			<< "Contact Phone Number: " << account.phone << endl
			<< "Shipping address: " << account.address << endl
			<< endl
			<< "Shopping details:" << endl;

		os << endl << "Code                                            Item  Price  Quantity  Subtotal" << endl;

		for (int i(1); i < 14; i++)
		{
			if (account.cart[i] > 0)
			{
				os << right << setw(4) << i << setw(48) << foods[i] << setw(7) << price[i] << setw(10) << order.quantity[i] << setw(10) << (price[i]) * (order.quantity[i]) << endl;
				(total += (price[i] * order.quantity[i]));
			}
		}

		os << endl << "Total Cost: " << total << endl;
	}

}
