#include<iostream>
using namespace std;
int sum(int a);

int main()
{
	int a,b;
	while(cin>>a)
	{
		if(a==0)
		{
			return 0;
		}
		b=sum(a);
		while(b>=10)
		 {
			b=sum(b);
		 }
		
		cout<<b<<endl;
	}
}

int sum(int a)
{
	if((a/10)==0)
	{
		return a;
	}
	else
	{
		return a%10+sum(a/10);
	}
}
