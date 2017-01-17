#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
/*
Thread Sonlandırma
Bir thread, başka bir thread tarafından, ilgili pthread_t id değeri
verilmek suretiyle cancel edilebilir:
int pthread_cancel (pthread_t thread);
*/

void *worker(void *data)
{
    char *name = (char *)data;
    int i;

    for (i=0; i<120; i++)
    {
        usleep(50000);
        printf("Hello from thread %s\n",name);
    }

    printf("Thread %s done ...\n",name);
    return NULL;
}


int main()
{
    pthread_t thread1,thread2;

    pthread_create(&thread1,NULL,worker,"A");
    pthread_create(&thread2,NULL,worker,"B");

    sleep(1);

    printf("## Cancelling thread B \n");

    pthread_cancel(thread2);

    printf("## Cancelling thread A \n");

    pthread_cancel(thread1);

    printf("Exiting from main program\n");

    return 0;
}
