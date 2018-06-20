#include<stdio.h>

long int eu[3];

long int* ext_euc(long int ,long int);
long int mod_exp(long int m,long int n, long int p);
long int mod_mul_inv(long int a, long int b,long int n);

int main()
{
	long int a = 9973, b = 9967;
	long int *p;
	p = ext_euc(a,b);
	printf("d:%ld\n",p[0]);
	printf("x:%ld\n",p[1]);
	printf("y:%ld\n",p[2]);
	int expo = mod_exp(7,560,561);
	printf("mod_exp_val:%ld\n",expo);
	
	//to find e
	//long int i = 2;
	long int e =2;
	//long int *arr;
	//arr = ext_euc(fi,e);
	long int fi = 12;
	ext_euc(fi,e); 
	while(eu[0]!=1)
	{
		e++;
		ext_euc(fi,e);
	
	}
	printf("e value is:%ld\n",e);
	
	long int inverse = mod_mul_inv(e,1,fi);
	printf("inverse is %ld\n",inverse);
	return 0;
	
}

long int mod_mul_inv(long int a, long int b,long int n)
{
	ext_euc(a,n);
	long int x0;
	long int d = eu[0];
	long int x1 = eu[1];
	long int y1 = eu[2];
	if(b%d == 0)
	{
		 x0 = (x1 * (b/d))%n;
		 if(x0 < 0)
		 	return (x0 + n);
		 return x0;
	}


}

long int mod_exp(long int m,long int n, long int p)
{
	long int t = 1;
	
	m = m%p;
	
	while(n>0)
	{
		if(n&1)
		{
			t= (t*m)%p;
		}
		n = n>>1;
		m = (m*m)%p;
		
	
	}
	
	return t;

}



long int* ext_euc(long int a_no,long int b_no)
{
	if(b_no==0)
	{
		eu[0] = a_no;
		eu[1] = 1;
		eu[2] = 0;
		long int *ptr = &eu;
		return ptr;
	}
	else
	{
		long int *ptr;
		ptr = ext_euc(b_no, a_no%b_no);
		eu[0] = *ptr;
		eu[1] = *(ptr + 1) ;
		eu[2] = *(ptr + 2);
		long int t;
		t = eu[2];
		eu[2] = (eu[1] - (a_no/b_no)*eu[2]);
		eu[1] = t;
		ptr = &eu;
		return ptr;
	}
	

}
