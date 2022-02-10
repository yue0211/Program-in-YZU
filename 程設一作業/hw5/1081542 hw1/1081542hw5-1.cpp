#include<iostream>
using namespace std;
int sum(int a,int b);

int main()
{
	int a,b,text,i = 1;
	cin>>text;
	while(cin>>a>>b)
	{
		if( a % 2 == 0 )
		{
			a = a + 1;
		}
		
		if( b % 2 == 0 )
		{
			b = b - 1;
		}
			
		cout<<"Case "<< i <<": "<<sum(a,b)<<"\n";
		i++;
	}
	
}

int sum(int a,int b)
{	
	if( a == b )
	{
		return b;
	}
	
	else 
	{
		return a + sum( a + 2, b );
	} 
	
	
}

