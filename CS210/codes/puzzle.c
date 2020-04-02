#include <stdio.h>


unsigned int add_help(unsigned int a, unsigned int b,unsigned int t, unsigned int s)
{
	if (t == b) 
	   return s;
	return add_help(a, b, ++t, ++s);
}

unsigned int mult_help(unsigned int a, unsigned int b,unsigned int t, unsigned int x)
{
	if(t==b)
	   return a;
	return mult_help(add_help(a,x,0,a),b,++t,x);   
}


unsigned int pow_help(unsigned int a, unsigned int b, unsigned int t, unsigned int s)
{
	if(t==b)
	   return a;  
	return pow_help(mult_help(a,s,1,a),b,++t,s);   	
}

unsigned int add(unsigned int a, unsigned int b)
{
	return add_help(a,b,0,a);
}

unsigned int mult(unsigned int a, unsigned int b)
{
	 
	return mult_help(a,b,1,a);  
	
}

unsigned int power(unsigned int a, unsigned int b)
{
	return pow_help(a,b,1,a);
}


int main()
{
	printf("5 + 6 = %u\n", add (5, 6));
	printf("7 * 8 = %u\n", mult(7, 8));
	printf("2 ^ 9 = %u\n", power (2, 9));
	return 0;
}
