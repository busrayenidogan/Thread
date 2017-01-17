#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define x 1000
#define z x*x

int A[x][x],B[x][x],C[x][x];

struct matrix
{
    int row;
    int column;
};

void _random();
void *process(void *ptr);

int main()
{
    int i,j,thread_counter=0;

    pthread_t thread[z];
    _random();

    for (i=0; i<x; i++)
    {
        for (j=0; j<x; j++)
        {
            struct matrix * a = (struct matrix *)malloc(sizeof(struct matrix));
            a->row = i;
            a->column = j;
            pthread_create(&thread[thread_counter],NULL,process,a);
            pthread_join(thread[thread_counter],NULL);
            thread_counter++;
        }
    }

    for (i=0; i<z; i++)
    {
        pthread_join(thread[i],NULL);
    }

    for (i=0; i<x; i++)
    {
        for (j=0; j<x; j++)
        {
            printf("%d      ",C[i][j]);
        }
        printf("\n");
    }
    return 0;
}
void _random()
{
    srand(time(NULL));

    int i,j;

    for (i=0; i<x; i++)
    {
        for (j=0; j<x; j++)
        {
            A[i][j] = rand()%1000;
            B[i][j] = rand()%1000;
        }
    }
}

void *process(void *ptr)
{
    struct matrix * temp = ptr;
    int i,summary=0;

    for (i=0; i<x; i++)
    {
        summary += A[temp->row][i] * B[i][temp->column];
    }
    C[temp->row][temp->column]=summary;
    pthread_exit(0);
}
