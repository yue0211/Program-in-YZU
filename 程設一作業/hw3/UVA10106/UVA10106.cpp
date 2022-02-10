#include <iostream>
#include<cstring>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */ 
int main(int argc, char** argv) 
{
	

	
 	char w[251],s[251];
    while(cin>>w>>s)
    {
	int a[60000]={0},b[60000]={0},c=0,d=0,e[90000]={0},i=0,x=0,g=0,h=0,ii=0,xx=0,z=0,Z=0,zz=0;
    g=strlen(w);
    h=strlen(s);
    
    /*	for(g--;g>=0;g--)
	{
		cout<<w[g];
	}
	
		for(h--;h>=0;h--)
	{
		cout<<s[h];
	}*/
	
  	g=strlen(w);
  	for(i=0;i<g;i++)
  {
	a[i]=w[g-i-1]-'0'; 
  }
    h=strlen(s);
    for(x=0;x<h;x++)
  {
  	b[x]=s[h-x-1]-'0';
  }
  	ii=i-1;
  	xx=x-1;
	  
	/*  for(i--;i>=0;i--)
	{
		cout<<a[i];
	}
	
		for(x--;x>=0;x--)
	{
		cout<<b[x];
	}
	*/
     
  	 i=0;
  	 x=0;
    for( z=0;z<=ii;z++)
  {
  	e[z]=a[i]*b[x];
  	i++;
  }
  //
    Z=1;
  	i=0;
  	
  	for(;x<xx;)
 {
 	for( z=Z;i<=ii;)
	{	
    	e[z]=e[z]+b[x+1]*a[i];
		i++;	
		z++;
    }
    x++;
    Z++;
    i=0;
 }                            //把直式乘法的值累加到陣列 
 
 	zz=z;
 	
	for( z=0;z<=zz;z++)                      
{   
	e[z+1]=e[z+1]+e[z]/10;
	e[z]=e[z]%10;
}                           //進位  



	for(;e[z]==0;)
	{
   		z=z-1;
	}	 
	
	if(z<0)
	cout<<'0'; 
	
	for(;z>=0;z--)
	{
		cout<<e[z];
	}

	cout<<endl;
}	
	return 0;

}
