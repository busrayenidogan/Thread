#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
// thread creating :
//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)

void *worker(void *data)
{
    char *name = (char *)data;
    int i;

    for (i=0; i<120; i++)
    {
        usleep(50000);
        printf("%d. Hello from thread %s \n",i,name);
    }

    printf("Thread %s done ...\n",name);
    return NULL;
}


int main(void)
{
    pthread_t thread1,thread2; //thread tanımlaması

    //(thread,kurallar,fonksiyon,veriyapısı)
    pthread_create(&thread1,NULL,worker,"A");
    pthread_create(&thread2,NULL,worker,"B");
    sleep(5);
    printf("Exiting from main program \n");

    return 0;
}
