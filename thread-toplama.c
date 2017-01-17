#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define x 1
#define y 3
#define k x*y

int matrix1[x][y],matrix2[x][y],matrix3[x][y];

struct total
{
    int row;
    int column;
};

void *worker(void *ptr);

int main()
{
    int i,j,thread_counter=0;
    pthread_t thread[k];

    for (i=0; i<x; i++)
    {
        for (j=0; j<y; j++)
        {
            printf("M1[%d][%d] = ",i,j);
            scanf("%d",&matrix1[i][j]);
        }
    }
    printf("\n\n");
    for (i=0; i<x; i++)
    {
        for (j=0; j<y; j++)
        {
            printf("M2[%d][%d] = ",i,j);
            scanf("%d",&matrix2[i][j]);
        }
    }
    for (i=0; i<x; i++)
    {
        for (j=0; j<y; j++)
        {
            printf("%d ",matrix1[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    for (i=0; i<x; i++)
    {
        for (j=0; j<y; j++)
        {
            printf("%d ",matrix2[i][j]);
        }
        printf("\n");
    }

    for (i=0; i<x; i++)
    {
        for (j=0; j<y; j++)
        {
            struct total * a = (struct total*)malloc(sizeof(struct total));
            a->row = i;
            a->column= j;
            pthread_create(&thread[thread_counter],NULL,worker,a);
            pthread_join(thread[thread_counter],NULL);
            thread_counter++;
        }
    }
    for (i=0; i<k; i++)
    {
        pthread_join(thread[i],NULL);
    }
    for (i=0; i<x; i++)
    {
        for (j=0; j<y; j++)
        {
            printf("%d ",matrix3[i][j]);
        }
        printf("\n");
    }

    return 0x0;
}

void *worker(void *ptr)
{
    struct total * temp = ptr;
    int i,summary=0;

    for (i=0; i<x; i++)
    {
        summary += matrix1[i][temp->column] + matrix2[i][temp->column];
    }
    matrix3[temp->row][temp->column] = summary;
    pthread_exit(0);
}
