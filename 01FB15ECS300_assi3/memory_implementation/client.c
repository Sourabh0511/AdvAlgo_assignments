#include "btr.h"


int main()
{

	BN **bt;
	init(&bt);

	//BN tes;

	//pseu_main(bt);
	bool fl[N];
    init_f_l(fl);

    int no_ip = 25000;
    for(int i = 0; i < N; ++i)
    {
        bt_insert(bt, fl); //creation of the tree for the whole dataset
    }

    printf("Tree created\n");

    int q = 180049;

    printf("I am searching for the key 180049(some random number in first 25k elements\n");
    BN ret_n = search(bt, q); //this lies within the first 25000 elements that were inserted
    display_n(&ret_n);

    printf("I am deleting the same node with key 180049\n");
    bt_delete(bt,q,fl);
    ret_n = search(bt, q);
    display_n(&ret_n);






    

    /*
    int r,q;
   
    do
    {
        printf("1.Search 2.Delete 3.Exit\n");
        scanf("%d",&r);
        switch(r)
        {
            case 1: printf("Enter number\n");
                    scanf("%d",&q);
		    		BN ret = search(bt, q);
                    display_n(&ret);
                    break;

            case 2: printf("Enter number\n");
                    scanf("%d",&q);
                    bt_delete(bt,q,fl);
                    BN dum = search(bt, q);
                    printf("After deletion the node is\n");
                    display_n(&dum);
                    break;


            case 3:break;

            default: printf("Invalid inp\n");
        }
        printf("\n");
    }while(r!=3);  */

    



	//return 0;

}

