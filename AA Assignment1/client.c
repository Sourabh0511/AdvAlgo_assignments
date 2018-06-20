#include "header.h"

int main(int argc, char const *argv[]){
    printf("\n\n\t\t\tDynamic Table\n\n");

    DTable dt;
    int n; // start size of the table
    float i; // increase factor
    float d; // decrease factor

    //printf("\nEnter the start size of the table : ");
    scanf("%d", &n);

    //printf("\nEnter the increase factor : ");
    scanf("%f", &i);

    //printf("\nEnter the decrease factor : ");
    scanf("%f", &d);

    createDynamicTable(&dt, n, i, d);
    printf("\n\n\tInitialised Dynamic Table...\n\n");

    int o;
    int *operations;
    //printf("\nEnter the number of operations: ");
    scanf("%d", &o);
    operations = (int *)malloc(o * sizeof(int));

    int pushes;
    Define_Operations(operations, o, &pushes);
    printf("\n\n\tOperations to be performed defined...\n\n");

    int z;
    int p;
    int print = 0;

    double avg_all = 0.0;
    double avg_insertion = 0.0;
    double avg_deletions = 0.0;

    double max_insert = 0.0;
    double max_delete = 0.0;

    for(z = 0; z < o; ++z){
        if(operations[z] == 0){
            if(print == 0){
                printf("\nAfter all pushes\n\n");
                printf("Max size : %d\n", dt.max_size);
                for(p = 0; p < dt.max_size; p++){
                    printf("%d  ", dt.table[p]);
                }
                printf("\n");
                print = 1;
            }
            printf("\n\tDelete\n");
            struct timespec start,end;
            clock_gettime(CLOCK_REALTIME,&start);

        	delete(&dt);

            clock_gettime(CLOCK_REALTIME,&end);
            double time = (end.tv_sec-start.tv_sec)*1000000000 + (end.tv_nsec-start.tv_nsec);
   	        time /= 1000000;
            printf("Time Elapsed(milliseconds) for delete = %lf\n\n",time);
            avg_all += time;
            avg_deletions += time;
            if(time > max_delete){
                max_delete = time;
            }
        }
        else if(operations[z] == 1){
            printf("\n\tPush\n");
            struct timespec start,end;
            clock_gettime(CLOCK_REALTIME,&start);

        	push(&dt);

            clock_gettime(CLOCK_REALTIME,&end);
            double time = (end.tv_sec-start.tv_sec)*1000000000 + (end.tv_nsec-start.tv_nsec);
   	        time /= 1000000;
            printf("Time Elapsed(milliseconds) for insert = %lf\n\n",time);
            avg_all += time;
            avg_insertion += time;
            if(time > max_insert){
                max_insert = time;
            }
        }
    }
    printf("\nmax_size = %d\n", dt.max_size);
    for(p = 0; p < dt.max_size; p++){
        printf("%d  ", dt.table[p]);
    }
    printf("\n");

    avg_all = (avg_all / o);
    avg_insertion = (avg_insertion / pushes);
    avg_deletions = (avg_deletions / (o - pushes));

    printf("\n\nAverage of all %d instructions = %lf", o, avg_all);
    printf("\n\nAverage of all %d inserts = %lf", pushes, avg_insertion);
    printf("\n\nAverage of all %d deletions = %lf", (o-pushes), avg_deletions);
    printf("\n\nMax time for insert = %lf", max_insert);
    printf("\n\nMax time for deletion = %lf\n\n", max_delete);
    return 0;
}
