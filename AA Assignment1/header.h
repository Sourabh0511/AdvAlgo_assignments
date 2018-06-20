#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

typedef struct DynamicTable{
    int max_size;
    int* table;
    int size;
    float inc_factor;
    float dec_factor;
}DTable;

void createDynamicTable(DTable *x, int n, float i, float d);
void Define_Operations(int *operations, int o, int *pushes);
void push(DTable *x);
void delete(DTable *x);
