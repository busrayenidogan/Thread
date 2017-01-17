#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/time.h>
#include "../common/utlist.h"
#include "../common/debug.h"

#define DEFAULT_LOOP_COUNT 10000000

struct list
{
    int no;
    struct list *next;
};
//timespce geçen zamanı temsil eder
//time_t tv_sec : Bu, geçen zamanın tüm saniye sayısını temsil eder.
//long int tv_nsec:Bu, geçen zamanın geri kalan kısmıdır (saniyenin bir kısmı), nanosaniye sayısı olarak temsil edilir.
//Her zaman bir milyardan daha az.
struct timespec timespec_diff(struct timespec before,struct timespec after)
{
    struct timespec res;

    if ((after.tv_nsec - before.tv_nsec)<0)
    {
        res.tv_sec = after.tv_sec - before.tv_sec - 1;
        res.tv_nsec = 1000000000 + after.tv_nsec - before.tv_nsec;
    }
    else
    {
        res.tv_sec = after.tv_sec - before.tv_sec;
        res.tv_nsec = after.tv_nsec - before.tv_nsec;
    }

    return res;
}

#ifdef USE_SPINLOCK
pthread_spinlock_t spinlock;
#else
pthread_mutex_t mutex;
#endif // USE_SPINLOCK

struct list *mylist;
pid_t gettid()
{
    return syscall(__NR_gettid);
}

void *worker (void *args)
{
    (void)args;

    struct list *tmp;

    infof("Worker thread %lu started",(unsigned long)gettid());

    while(1)
    {
        #ifdef USE_SPINLOCK
            pthread_spin_lock(&spinlock);
        #else
            pthread_mutex_lock(&mutex);
        #endif // USE_SPINLOCK

        if (mylist == NULL)
        {
            #ifdef USE_SPINLOCK
                pthread_spin_unlock(&mutex);
            #else
                pthread_mutex_unlock(&mutex);
            #endif // USE_SPINLOCK

                break;
        }

        tmp = mylist;
        LL_DELETE(mylist,tmp);

        #ifdef USE_SPINLOCK
            pthread_spin_unlock(spinlock);
        #else
            pthread_mutex_unlock(&mutex);
        #endif
    }

    return NULL;
}

int main(int argc , char *argv[])
{
    int i;
    int loop_count;
    pthread_t thread1,thread2;

    struct timespec before,after;
    struct timespec result;
    struct list *el;

    #ifdef USE_SPINLOCK
        pthread_spin_init(&spinlock,0);
    #elif USE_HYBRID
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_ADAPTIVE_NP);
    #else
        pthread_mutex_init(&mutex,NULL);
    #endif // USE_SPINLOCK

    if (argc == 2)
    {
        loop_count = atoi(argv[1]);
    }
    else
    {
        loop_count = DEFAULT_LOOP_COUNT;
    }

    infof("Preparing list");

    struct list *container = calloc(loop_count,sizeof(struct list));

    for (i=0; i<loop_count; i++)
    {
        el = &container[i];
        el->no = i;
        LL_PREPEND(mylist,el);
    }

    clock_gettime(CLOCK_MONOTIC,&before);

    pthread_create(&thread1,NULL,worker,NULL);
    pthread_create(&thread2,NULL,worker,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    clock_gettime(CLOCK_MONOTIC,&after);

    result = timespec_diff(before,after);

    debugf("Elapsed time with %d loops : %li.%06li",loop_count,result.tv_sec,result.tv_nsec/1000);

    #ifdef USE_SPINLOCK
        pthread_spinlock_destroy(&spinlock);
    #else
        pthread_mutex_destroy(&mutex);
    #endif // USE_SPINLOCK

    return 0x0;
}
