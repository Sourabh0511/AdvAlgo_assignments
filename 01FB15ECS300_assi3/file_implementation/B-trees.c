

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

#define T 3

int hash();
void insert();
void addKey();
void split();
void search();
void display();
void delete();
typedef struct data
{
    int i;
    char *s;
    char *t;
    int a;
    int b;
}data;

data ar[1000000];



typedef struct node
{
    int n;
    int leaf;
    int key[2*T-1];
    long ind[2*T-1];
    int valid[2*T-1];
    struct node *next[2*T];
    //struct node *prev;
    //int hasChild;

}node;

node *start;
int mode = 1;

void main()
{
printf("ENTER 1-ARRAY , 2-FILE   :  \n");
printf("Once mode is selected enter a value without - minus sign to search and with a - sign to delete\n");
scanf("%d",&mode);
printf("Creating B tree...\n");
start = calloc(sizeof(node),1);
start->n = 0;
start->leaf = 1;

FILE *fp;
fp = fopen("dataset.csv", "rb");
long ct = 0;
long off = 0;
int i,a,b;
//printf("%d",t);

while(1)
{
off = ftell(fp);
char *s = malloc(sizeof(char)*10);
char *t = malloc(sizeof(char)*10);
//fgets(s,1000,fp);
fscanf(fp,"%d,%[^,],%[^,],%d,%d",&i,s,t,&a,&b);

if(mode==1)
insert(i,ct);
else
{
    //if(ct<10)
    //printf("%d,%ld  ",i,off);
    insert(i,off);
}

//printf("%d,%s,%s,%d,%d \n",i,s,t,a,b);

data d;
d.s = (char *)malloc(sizeof(char)*5);
d.t = (char *)malloc(sizeof(char)*5);
d.i = i;
d.s = s;
d.t = t;
d.a = a;
d.b = b;



if(mode == 1)
    ar[ct] = d;






//free(s);
//free(t);
//char buf;
//scanf("%c",&buf);



//display(start);

//printf("________________________________\n");
//display(start);

//printf("________________________________\n");

if(ct==999999)
    break;

ct++;

}
printf("B Tree successfully created\n\n");


while(1)
{   
    
    int key;
    //scanf("%d\n",&op);
    printf("Enter Search Key (precede by - for deletion) : ");
    scanf("%d",&key);
    if(key<0)
        delete(-1*key);
    else
    search(key);
    
}

}



void insert(int key, long ind)
{
if(start->n == 2*T-1)
{
    //printf("START SPLIT\n");
    node *new = (node *)malloc(sizeof(node));
    new->n = 0;
    new->leaf = 0;
    new->next[0] = start;
    start = new;
    split(start,0);
  
}

addKey(start,key,ind);

}

void addKey(node* x, int key ,long ind)
{
   int i=x->n-1;
   //printf("[%d]\n",i);
   if(x->leaf)
   {
   while(i>=0 && x->key[i]>key)
   {
       x->key[i+1] = x->key[i];
       x->ind[i+1] = x->ind[i];
       x->valid[i+1] = x->valid[i];
       i--;
   }
   x->key[i+1] = key;
   x->ind[i+1] = ind;
   x->valid[i+1] = 1;
   x->n++;
   //printf("Key Added : %d\n",key);

   }
   else
   {
       while(i>=0 && x->key[i]>key)
        i--;
       i++;
       //display(start);
       //printf("| %x %x|,%d\n",x,x->next[i],i);
       //display(x->next[i]);
       if(x->next[i]->n == 2*T-1)
            {
                //printf("SPLITTING %x  at  %d\n",x,i);
                
                split(x,i);
                //printf("SPLIT IS FINE\n");
                if(key>x->key[i])
                    i++;
            }
        addKey(x->next[i],key,ind);
   }

   


}

void split(node *x, int pos)
{
    //printf("Zeroth , %d\n",pos);
    struct node *new = (struct node*)malloc(sizeof(node));
    //struct node *left = (struct node*)malloc(sizeof(node));
    struct node *left;
    //printf("|%x|\n",x);
    left = x->next[pos];
    //printf("|%x|\n",left);
    new->leaf = left->leaf;
    new->n = T-1;
    //printf("first\n");
    for(int i=0;i<T-1;i++) 
    {   
        new->key[i] = left->key[i+T];
        new->ind[i] = left->ind[i+T];
        new->valid[i] = left->valid[i+T];
    }
    if(left->leaf == 0)
    {
        for(int i=0;i<T;i++)
            new->next[i] = left->next[i+T];
    }
    //printf("second\n");
    left->n = T-1;
    for(int i = x->n;i>=pos;i--)
    {
        x->next[i+1] = x->next[i];
    }
    //printf("third\n");
    x->next[pos+1] = new;
    for(int i=x->n-1;i>=pos;i--)
    {
        x->key[i+1]=x->key[i];
        x->ind[i+1]=x->ind[i];
        x->valid[i+1] = x->valid[i];
    }
    //printf("fourth\n");
    x->key[pos] = left->key[T-1];
    x->ind[pos] = left->ind[T-1];
    x->valid[pos] = left->valid[T-1];
    x->n++;
    //printf("fifth n=%d\n",x->n);

    //display(start);
}

void search(int key)
{
    struct node *temp = start;
    while(1)
    {
        int i=0;
        while( i<temp->n  && key > temp->key[i] )
            i++;
        if(temp->key[i] == key && temp->valid[i]==1)
        {
            //printf("FOUND\n");
            long ind = temp->ind[i];
            if(mode==1)
            printf("\n%d , %s , %s , %d , %d \n\n",ar[ind].i,ar[ind].s,ar[ind].t,ar[ind].a,ar[ind].b);
            else
            {
                FILE *fp;
                fp = fopen("dataset.csv", "rb");
                // disk access from file
                int i,a,b;
                char s[5],t[5];
                //printf("ind = %ld\n",ind);
                fseek(fp,ind,SEEK_SET);
                //for(int j=0;j<ind;j++)
                    //fscanf(fp,"%d,%[^,],%[^,],%d,%d",&i,s,t,&a,&b);
                fscanf(fp,"%d,%[^,],%[^,],%d,%d",&i,s,t,&a,&b);
                printf("\n%d,%s,%s,%d,%d \n\n",i,s,t,a,b);
            }
            return; 
        }
        else if(temp->leaf)
        {
            printf("NOT FOUND\n");
            return;
        }
        else
            temp = temp->next[i];
    }

}

void display(node *temp)
{
    if(temp == NULL)
        return;
    //printf("|%x| , leaf = %d\n",temp,temp->leaf);
    for(int i=0;i<temp->n;i++)
        printf("%d ",temp->key[i]);
    printf("\n");
    if(!temp->leaf)
    for(int i=0;i<=temp->n;i++)
    {
        printf("temp=%x, temp->next[%d] = %x\n\n",temp,i,temp->next[i]);
        display(temp->next[i]);

    }
}

void delete(int key)
{

    struct node *temp = start;
    while(1)
    {
        int i=0;
        while( i<temp->n  && key > temp->key[i] )
            i++;
        if(temp->key[i] == key && temp->valid[i]==1)
        {
            temp->valid[i]=0;
            printf("%d deleted\n",key);
            return; 
        }
        else if(temp->leaf)
        {
            printf("NOT FOUND, CANNOT DELETE\n");
            return;
        }
        else
            temp = temp->next[i];
    }


}
