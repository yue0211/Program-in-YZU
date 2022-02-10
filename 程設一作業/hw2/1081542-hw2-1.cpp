#include <iostream>
using namespace std; 
int main()
{ int a,b[100],i;
 
  cout<<"Enter a positive decimal integer of at most 8 digits: ";
  cin>>a;
  int c;
  c=a;
  cout<<"The binary equivalent of "<<a<<" is ";
  for(i=0;a>0;i++)
{ b[i]= a%2;
  a = a/2;
}

  for(i=i-1;i>=0;i--)
{
  cout<<b[i];
}
  
  cout<<"\n";
  
  int d[100],x;
  cout<<"The octal equivalent of "<<c<<" is ";
  for(x=0;c>0;x++)
{
  d[x]=c%8;
  c=c/8;
} 
  
  while(x>0)
{
	x=x-1;
	cout<<d[x];
}


}
 

