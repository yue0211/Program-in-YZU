#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv)
{
	
    cout<<"all Armstrong numbers of three digits:";
	cout<<"\n"; 
	int i,x,y,z; 
	for(i=100;i<1000;i++)
{
	x=i/100;
	y=i/10%10;
	z=i%10;	
	
	if(x*x*x+y*y*y+z*z*z==i)
{
	cout<<i<<" ";	
}
}
	
	
	return 0;
}
