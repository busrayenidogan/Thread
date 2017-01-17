#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define x 3
#define y 2
#define k x*y

int matrix1[x][y] = {{1, 4}, {2, 5}, {3, 6}};
int matrix2[y][x] = {{8, 7, 6}, {5, 4, 3}};
int matrix3[k][k];

struct total
{
    int row;
    int column;
};

void *worker(void *ptr);


int main()
{
    int i,j,thread_counter=0;
    pthread_t thread[k]; //k tane thread oluştur


    for (i=0; i<x; i++)
    {
        for (j=0; j<x; j++)
        {
            struct total * a = (struct total*)malloc(sizeof(struct total));
            a->row = i;
            a->column = j;
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
        for (j=0; j<x; j++)
        {
            printf("%d ",matrix3[i][j]);
        }
        printf("\n");
    }


    return 0;
}

void *worker(void *ptr)
{
    struct total * temp = ptr;
    int i,summary=0;

    for (i=0; i<y; i++)
    {
        summary += matrix1[temp->row][i] * matrix2[i][temp->column];
    }
    matrix3[temp->row][temp->column] = summary;
    pthread_exit(0);
}
