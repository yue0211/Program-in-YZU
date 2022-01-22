#include<iostream>
using namespace std;
int gcd(int a,int b);

int main()
{
	int n,g;
	while(cin>>n) 
	{
		
		if(n==0)
		{
			return 0;
		}	
		else
		for(int i=1;i<n;i++)
		{
			for(int m=i+1;m<=n;m++)
			{
				g+=gcd(m,i);
			}
			
		}
		cout<<g<<endl;
		g=0; 
		
		
	}
} 

int gcd(int a,int b)
{
	
	if(b==0)
	return a;
	else
	return gcd(b,a%b);
	
}














