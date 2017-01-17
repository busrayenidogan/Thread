#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define x 60

void *worker1(void *ptr);
void *worker2(void *ptr);

int main()
{
    pthread_t thread;

    pthread_create(&thread,NULL,worker1,"LOTR");
    pthread_join(thread,NULL);
    sleep(20);

    return 0x0;
}

void *worker1(void *ptr)
{
    int i;
    char * string = (char*)ptr;

    for (i=0; i<x; i++)
    {
        if(i==30)
        {
            pthread_t thread2;
            pthread_create(&thread2,NULL,worker2,"The oa");
            pthread_join(thread2,NULL);
        }
        else
        {
            usleep(500);
            printf("%d. Lord of the Rings (%s)\n",i,string);
        }
    }
    printf("Thread %s done ..\n\n",string);
    return NULL;
}
void *worker2(void *ptr)
{
    int i;
    char *string2 = (char*)ptr;

    for (i=0; i<x; i++)
    {
        usleep(5000);
        printf("%d. %s\n",i,string2);
    }
    printf("Thread %s done ..\n\n",string2);
    return NULL;
}
