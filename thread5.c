#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

long long sum=0;

void * worker(void *arg)
{
    long long *limit_ptr = (long long*)arg;
    long long limit = *limit_ptr;
    long long i;

    for (i=0; i<=limit; i++)
    {
        sum +=i;
    }

    pthread_exit(0);
}

int main(int argc, char **argv)
{
    if (argc <2 )
    {
        printf("Usage : %s <num>\n",argv[0]);
        exit(-1);
    }

    long long limit = atoll(argv[1]);

    //Thread ID:
    pthread_t threadID;

    //Create attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&threadID,&attr,worker,limit);

    //Wait until thread is done its work

    pthread_join(threadID,NULL);



    return 0;
}
