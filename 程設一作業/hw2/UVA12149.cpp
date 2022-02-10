#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) 
{
   int n,a=0;
  
   while(cin>>n)
{   
     if(n!=0)
     {
	
	for(int i=0;i<=n;i++)
   {
	a=a+i*i;  
   }
   cout<<a;
   cout<<"\n";
   a=0;
    }
    else
    return 0;

}

}
