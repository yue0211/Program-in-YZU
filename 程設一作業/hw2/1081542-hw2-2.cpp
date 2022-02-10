#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() 
{
	cout<<"Enter a positive integer of at most 8 digits: ";
	int a;
	int b;
	cin>>a;
	cout<<"\n";
	cout<<"The sum of all digits of "<<a<<" is ";
	for(int i=0;i<=7;i++)
	{ 
	  b=b+(a%10);
	  a=a/10;
    }
    cout<<b;
}


