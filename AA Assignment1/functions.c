#include "header.h"

void createDynamicTable(DTable *x, int n, float i, float d){
    x -> max_size = n;
    x -> size = 0;
    x -> inc_factor = i;
    x -> dec_factor = d;

    x -> table = (int*)malloc(n * sizeof(int));
}

void Define_Operations(int *operations, int o, int *pushes){
    // Since operations array is malloced it will be Initialised with
    // zeroes....So only put ones in random positions
    srand(getpid());
    int no_of_ones = (int)ceil(0.67 * o);
    printf("\nNo of pushes(ones) : %d\n", no_of_ones);
    *pushes = no_of_ones;
    int i;
    for(i = 0; i < no_of_ones; ++i){
        operations[i] = 1;
    }
    for(i = 0; i < o; ++i){
		int j = rand() % o;
		int t = operations[i];
        operations[i] = operations[j];
        operations[j] = t;
	}
    printf("\n\tOPERATIONS\t(0->pop\t1->push)\n");
    for(i = 0; i < o; ++i){
        printf("%d\t", operations[i]);
    }
    printf("\n");
}

void push(DTable *x){
    if((x -> size) == (x -> max_size)){
        printf("\nSize Increased\n");
        // increase size of array and copy elements
        int* temp;
        int new_max_size = (int)ceil((x -> max_size) * (x -> inc_factor));
        temp = (int *)malloc(new_max_size * sizeof(int));
        x -> max_size = new_max_size;

        // copy elements to new array
        int i;
        for(i = 0; i < (x -> size); ++i){
            //printf("Copying\n");
            temp[i] = x -> table[i];
        }
        x -> table = temp;

    }
    x -> table[x -> size] = (rand() % 1000) + 1;
    (x -> size)++;
}

void delete(DTable *x){
    if(x -> size > 0){
        x -> table[(x -> size) - 1] = 0;
        x -> size = ((x -> size) - 1);

        int reduced_size = (int)ceil((x -> max_size) * (x -> dec_factor));
        //printf("size = %d\n", x->size);
        //printf("reduced_size = %d\n", reduced_size);
        if((x -> size) <= reduced_size){
            printf("\nSize Decreased\n");
            int* temp;
            temp = (int *)malloc(reduced_size * sizeof(int));
            int i;
            for(i = 0; i < (x -> size); ++i){
                //printf("Copying\n");
                temp[i] = x -> table[i];
            }
            x -> max_size = reduced_size;
            x -> table = temp;
        }
    }
}
