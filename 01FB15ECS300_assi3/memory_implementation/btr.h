#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define t 101 //for degree of the btree
#define N 25000

typedef struct rec //structure of the record
{

	char coun[10];
	char grade[10];
	int sub1;
	int sub2;
}REC;


typedef struct bnod   //structure of the btree node
{
	long int key;
	REC rec;
	int rchild; //pointer as index for its right child

}BN;


void init(BN ***n); 
void initialize_of_f_nodes(BN **n);
void init_f_l(bool *l); //init of free list array
void display_an(BN *arr); //print the entire outer node print array with nodes 
void inp_node(BN *n);  //to input the node
void display_n(BN *nod); //print the inner node if required
void bt_insert(BN **n, bool *fl);
void make_copy_arr(BN *p, BN *q, int src, int dest);
void insert_at_pos(BN *ar, BN *n);
void node_split(BN **b, int ind, int p, int lc_ind, int rc_ind, bool *f_l);
void pseu_main(BN **bt);
BN search(BN **bt, long int k);
int track_fl_ind(bool *l); //track the free index and return the index
void mod_fl(bool *l, int ind); //modify the free list
void bt_delete(BN **bt, long int k, bool *f_l);
bool check_if_leaf(BN *arr); //function returns true if it is a leaf
void delete_arr(BN *a, int ind);

int merge(BN **bt, int par, int p_ind, int l_c, int r_cc, bool *f_l);



//void delete(NODE **b, long int k, bool *free_list);
//void delete_array(NODE *a, int index);

//int merge(NODE **b, int parent, int parent_index, int leftChild, int rightChild, bool *free_list);

