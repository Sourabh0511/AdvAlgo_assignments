#include<stdio.h>

long int eu[3];

long int* ext_euc(long int ,long int);
long int mod_exp(long int m,long int n, long int p);
long int mod_mul_inv(long int a, long int b,long int n);

int main()
{
    
    long int testcase;
    scanf("%ld",&testcase);
    while(testcase)
   {
        long int p,q,c;
        scanf("%ld",&p);
        scanf("%ld",&q);
        scanf("%ld",&c);
        long int fi = (p-1)*(q-1);
        long int n = p*q;
        long int e =2;
        ext_euc(fi,e); 
        printf("eu[0] : %ld",eu[0]);
	    while(eu[0]!=1)
	    {
		    e++;
		    ext_euc(fi,e);
	
	    }
	    printf("e value is:%ld\n",e);
	
	    long int inverse = mod_mul_inv(e,1,fi);
	    printf("Inverse value is:%ld\n",inverse);
	    long int value = mod_exp(c,inverse,n);
	    printf("Value is %ld\n",value);
	    testcase--;
	    
    }
	    
	 return 0;   
	  
    
    
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
