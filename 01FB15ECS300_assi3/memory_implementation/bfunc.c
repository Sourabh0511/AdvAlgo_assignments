#include "btr.h"

void init(BN ***n) //initialization of the outer bigger 2D array of BN type
{

	(*n) = (BN **)malloc(N * sizeof(BN*));  
	
	for(int i=0;i<N;++i)
	{
		(*n)[i] = (BN *)malloc((2*t) * sizeof(BN));

	}

	initialize_of_f_nodes(*n); //function call to initialize the inner nodes of the 2D array


}

void initialize_of_f_nodes(BN **n) //all first nodes shall be dummy nodes holding the count
{
	for(int i=0;i<N;++i)
	{

		n[i][0].key = 0;
		strcpy(n[i][0].rec.coun,"");
		strcpy(n[i][0].rec.grade,"");
		n[i][0].rec.sub1 = -1;
		n[i][0].rec.sub2 = -1;
		n[i][0].rchild = -1;
	}

}

void init_f_l(bool *l)
{
    for(int i = 0; i < N; ++i)
    {
        l[i] = true;
    }
    l[0] = false;
}
int track_fl_ind(bool *l) //function to track a free list ind
{ 
    int i = 0;
    while(i < N && l[i] != true)
    {
        i++;
    }
    if(i >= N){
        printf("\nNo more empty places available\n");
        return -1;
    }
    l[i] = false;
    return i;  //changes the ind it is returning to occupied and returns the ind
}

void mod_fl(bool *l, int ind) //function that modifies the free list when a record is deleted
{
    l[ind] = true;
}


void inp_node(BN *bt)   //to capture data and input it appropriately acc to the fields
{

	scanf("%ld",&(bt->key));
	scanf("%s",((bt->rec).coun));
	scanf("%s",((bt->rec).grade));
	scanf("%d",&(bt->rec.sub1));
	scanf("%d",&(bt->rec.sub2));
	bt->rchild = -1;

}

void make_copy_arr(BN *p, BN *q, int src, int dest)
{
    int j = 1;
    for(int i = src; i < dest; i++)
    {
        q[j++] = p[i];
        (q[0].key)++;
    }
}

void insert_at_pos(BN *ar, BN *n) //after findind index add n into the 2d array
{
    long int val = ar[0].key;
    int j = val;

    while(j > 0 && (ar[j].key > (n->key)))
    {
        ar[j + 1] = ar[j];
        j--;
    }

    ar[j + 1] = *n;
    (ar[0].key)++;
}

void display_n(BN *n)  //function to print the inner node
{

	printf("\n");
	printf("\n");
	printf("Key value is:%ld\n",n->key);
	printf("Country name is:%s\n",n->rec.coun);
	printf("Grade name is:%s\n",n->rec.grade);
	printf("Scoring of sub1 is:%d\n",n->rec.sub1);
	printf("Scoring of sub1 is:%d\n",n->rec.sub2);
	//printf(Right child found at index:- %d \n",n->rchild);

}


void display_an(BN *ar) //function to print the outer 2D node
{

	printf("\nNo of keys in the node looked at = %ld\n",ar[0].key);
	printf("Keys of the structs are:\n");
	long int a = ar[0].key;
	for(int i=1;i<=a;++i)
	{
		printf("%ld\t",ar[i].key);

	}
	printf("\n");

}

/*
void pseu_main(BN **bt) // a dummy function for testing purpose
{
    bool fl[N];
    init_f_l(fl);

    int no_ip = 16;
    for(int i = 0; i < no_ip; ++i)
    {
        bt_insert(bt, fl);
    }

    
    

    bt_delete(bt,474378,fl);

    
} */


void bt_insert(BN **b, bool *f_l)
{
    BN n;
    inp_node(&n); 

    

    int start = 0;  //initially start is at 0 and prev is at -1 like we do in linked_list
    int prev = -1;

    while(start != -1)
    {
        long int curr_key_count = b[start][0].key;
        
        if(curr_key_count >= ((2 * (t)) - 1))
        {
            
            int ind_lc = track_fl_ind(f_l);
            int ind_rc = track_fl_ind(f_l);
            node_split(b, start, prev, ind_lc, ind_rc, f_l);
            if(prev != -1)  //case when it is not the root node then  update start
            {
                if(n.key > b[ind_rc][1].key)
                {
                    start = ind_rc;
                }
                else
                {
                    start = ind_lc;
                }
            }
            
        }
        else
        {
            BN *sarr = b[start];
            int i = (curr_key_count / 2) + 1; // search from mid
            if(curr_key_count == 0) // If count is 0
            {
                
                prev = start;
                start = -1;
            }
            else
            {
                if(sarr[i].key < n.key)
                {
                    //key that is bigger than one to be inserted
                    while(i <= (curr_key_count) && sarr[i].key < n.key)
                    {
                        i++;
                    }
                    prev = start;
                    start = sarr[i - 1].rchild;
                }
                else
                {
                    //key that is smaller than one to be inserted
                    while(i > 0 && sarr[i].key > n.key)
                    {
                        i--;
                    }
                    prev = start;
                    start = sarr[i].rchild;
                }
            }
        }
    }
    insert_at_pos(b[prev], &n);
}


void node_split(BN **bt, int ind, int parent, int lc_ind, int rc_ind, bool *f_l) //splitting node into two children and the mid will act as parent
{

    long int mid = (bt[ind][0].key / 2) + 1;

    make_copy_arr(bt[ind], bt[lc_ind], 1, mid);
    make_copy_arr(bt[ind], bt[rc_ind], mid + 1, (bt[ind][0].key + 1));

    //after retrieving the indices the children are inserted at respective indices 
    bt[rc_ind][0].rchild = bt[ind][mid].rchild;
    bt[lc_ind][0].rchild = bt[ind][0].rchild;

    bt[ind][mid].rchild = rc_ind;



    if(parent == -1)
    {
        bt[ind][1] = bt[ind][mid];
        bt[ind][0].key = 1;
        bt[ind][0].rchild = lc_ind;
    }

    else
    {
        BN *p = bt[parent];
        // inserting the mid element
        long int val = p[0].key;
        int i = val;

        while(i > 0 && (p[i].key > (bt[ind][mid].key)))
        {
            p[i + 1] = p[i];
            i--;
        }

        p[i + 1] = bt[ind][mid];
        (p[0].key)++;
        p[i].rchild = lc_ind;

        bt[ind][0].key = 0;
        mod_fl(f_l, ind);
    }
}


//look into search
BN search(BN **bt, long int k){
    int start = 0;
    bool present = false;

    BN n_present; //hold the return values
    n_present.key = -1;
    strcpy(n_present.rec.coun, "");
    strcpy(n_present.rec.grade, "");
    n_present.rec.sub1 = -1;
    n_present.rec.sub2 = -1;
    n_present.rchild = -1;

    int i;
    while(start != -1 && present == false){
        long int curr_key_count = bt[start][0].key;
        BN *sarr = bt[start];
        i = (curr_key_count / 2) + 1;

        if(curr_key_count == 0){
            // B-TREE is empty
            start = -1;
        }
        else{
            if(sarr[i].key < k){
                
                while(i <= (curr_key_count) && sarr[i].key < k){
                    i++;
                }
                if(i <= curr_key_count){
                    if(sarr[i].key == k){
                        present = true;
                    }
                }
                if(present == false){
                    start = sarr[i - 1].rchild;
                }
            }
            else{
                
                while(i > 0 && sarr[i].key > k){
                    i--;
                }
                if(i != 0){
                    if(sarr[i].key == k){
                        present = true;
                    }
                }
                if(present == false){
                    start = sarr[i].rchild;
                }
            }
        }
    }
    if(present){
        return bt[start][i];
    }
    return n_present;
}



void bt_delete(BN **b, long int k, bool *f_l){ 
    int par = -1;
    int in_par = -1;
    int start = 0;
    bool found = false;

    int tstrt = 0;

    int i;
    while(start != -1 && found == false){
        long int curr_key_count = b[start][0].key;
        BN *sarr = b[start];
        i = (curr_key_count / 2) + 1;

        if(curr_key_count == 0)//empty tree
        {
            
            start = -1;
        }
        else{
            if(sarr[i].key < k){
                
                while(i <= (curr_key_count) && sarr[i].key < k){
                    i++;
                }
                if(i <= curr_key_count){
                    if(sarr[i].key == k){
                        found = true;
                    }
                }
                if(found == false){
                    par = start;
                    in_par = i-1;
                    start = sarr[i - 1].rchild; 
                    tstrt = sarr[i].rchild;

                
                    if((sarr[0].key - 1 < (t - 1)) && ((b[tstrt][0].key - 1) < ((t) - 1))){
                        printf("\nMerge1\n");
                        start = merge(b, par, in_par, start, tstrt, f_l);
                    }
                }
            }
            else{
                
                while(i > 0 && sarr[i].key > k){
                    i--;
                }
                if(i != 0){
                    if(sarr[i].key == k){
                        found = true;
                    }
                }
                if(found == false){
                    par = start;
                    in_par = i+1;
                    start = sarr[i].rchild;

                    tstrt = sarr[i+1].rchild;
                    
                    if((sarr[0].key - 1 < ((t) - 1)) && ((b[tstrt][0].key - 1) < ((t) - 1))){
                        printf("\nMerge2\n");
                        start = merge(b, par, in_par, start, tstrt, f_l);
                    }
                }
            }
        }
    }
    if(found){
        //we test for two cases when it is internal node or if it is a leaf node

        if(check_if_leaf(b[start])){
            
            if(b[start][0].key - 1 >= t - 1){
                

                delete_arr(b[start], i);
                (b[start][0].key)--;
            }
            else{
                if(start == 0){
                    if(b[start][0].key > 0){
                        delete_arr(b[start], i);
                        (b[start][0].key)--;
                    }
                    else{
                        printf("\n\nEMPtY B-tREE!!\n\n");
                    }
                }
                else{
                    int other_child;
                    int rightmost = true;
                    if(k > b[par][in_par].key){
                        
                        other_child = b[par][in_par - 1].rchild;
                    }
                    else{
                        
                        other_child = b[par][in_par].rchild;
                        rightmost = false;
                    }
                    
                    if(b[other_child][0].key - 1 >= (t - 1)){
                        
                        int index_to_borrow;
                        int j;
                        if(rightmost){
                            index_to_borrow = b[other_child][0].key;
    

                            j = i;
                            while(j > 1){
                                b[start][j] = b[start][j - 1];
                            }
                            b[start][1] = b[par][in_par];
                            b[start][1].rchild = -1;
                        }
                        else{
                            index_to_borrow = 1;

                            j = i + 1;
                            while(j <= b[other_child][0].key){
                                b[start][j - 1] = b[start][j];
                            }
                            b[start][b[start][0].key] = b[par][in_par];
                            b[start][b[start][0].key].rchild = -1;
                        }

                        b[other_child][index_to_borrow].rchild = b[par][in_par].rchild;
                        b[par][in_par] = b[other_child][index_to_borrow];
                        (b[other_child][0].key)--;
                    }
                    else{
                        //merging whenever required
                        if(b[par][in_par].key > k){
                            start = merge(b, par, in_par, start, other_child, f_l);
                        }
                        else{
                            start = merge(b, par, in_par, other_child, start, f_l);
                        }
                        int where = 1;
                        while(where <= b[start][0].key && b[start][where].key != k){
                            where++;
                        }
                        printf("where = %d", where);
                        delete_arr(b[start], where);
                        (b[start][0].key) --;
                    }
                }
            }
        }
        else{
            
            int left_child = b[start][i - 1].rchild;
            int right_child = b[start][i].rchild;

            int pred = left_child;
            int succ = right_child;
            
            while(pred != -1){
                left_child = pred;
                pred = b[pred][b[pred][0].key].rchild;
            }
            // Find Successor
            while(succ != -1){
                right_child = succ;
                succ = b[succ][0].rchild;
            }
            

            if(b[left_child][0].key - 1 >= (t - 1)){
                
                b[left_child][b[left_child][0].key].rchild = b[start][i].rchild;
                b[start][i] = b[left_child][b[left_child][0].key];
                (b[left_child][0].key)--;
            }
            else if(b[right_child][0].key - 1 >= (t - 1)){
                
                b[right_child][1].rchild = b[start][i].rchild;
                b[start][i] = b[right_child][1];

                // left shift coz of deletion
                int j = 2;
                while(j <= b[right_child][0].key){
                    b[right_child][j - 1] = b[right_child][j];
                    j ++;
                }

                (b[right_child][0].key)--;
            }

            else{
                
                start = merge(b, start, i, b[start][i - 1].rchild, b[start][i].rchild, f_l);
                int where = 1;
                while(where <= b[start][0].key && b[start][where].key != k){
                    where++;
                }
                
                bt_delete(b, k, f_l);
            }

        }

    }
}

void delete_arr(BN *a, int index){
    long int n = a[0].key;
    int i = index + 1;

    while(i <= n){
        a[i - 1] = a[i];
        i++;
    }
}

bool check_if_leaf(BN *a){
    long int n = a[0].key;
    bool leaf = true;
    int i = 0;

    while(i < (n + 1) && leaf == true){
        if(a[i].rchild != -1){
            leaf = false;
        }
        i++;
    }
    return leaf;
}

int merge(BN **b, int par, int par_index, int leftChild, int rightChild, bool *f_l){
    long int total_nodes = b[leftChild][0].key + 1 + b[rightChild][0].key;

    BN temp[2 * t];
    temp[0].key = total_nodes;
    strcpy(temp[0].rec.coun, "");
    strcpy(temp[0].rec.grade, "");
    temp[0].rec.sub1 = -1;
    temp[0].rec.sub2 = -1;

    temp[0].rchild = b[leftChild][0].rchild;

    int i;
    int j = 1;
    for(i = 1; i <= b[leftChild][0].key; i++){
        temp[j++] = b[leftChild][i];
    }

    b[par][par_index].rchild = b[rightChild][0].rchild;
    temp[j++] = b[par][par_index];
    b[par][0].key -= 1;

    for(i = 1; i <= b[rightChild][0].key; i++){
        temp[j++] = b[rightChild][i];
    }

    int x = 0;

    if(b[par][0].key == 0){
        // use the same place to store the new merged array
        while(x <= total_nodes){
            b[par][x] = temp[x];
            x++;
        }
    }
    else{
        // Cover up that hole created by removing the par
        for(int z = par_index; z <= b[par][0].key; z++){
            b[par][z] = b[par][z + 1];
        }
        int free_place = track_fl_ind(f_l);
        // Update b[par] and the merged nodes go to b[free]
        // copy temp to b[free_place]
        while(x <= total_nodes){
            //printf("%ld\t", temp[x].key);
            b[free_place][x] = temp[x];
            x++;
        }
        //printf("\n");
        b[par][par_index - 1].rchild = free_place;
        par = free_place;
    }

    b[leftChild][0].key = 0;
    b[rightChild][0].key = 0;

    mod_fl(f_l, leftChild);
    mod_fl(f_l, rightChild);

    return par;
}
