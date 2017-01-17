#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//pthread_join fonksiyonu ile, bir thread'in sonlanmasını bekleyebiliriz.
/*
pthread_join fonksiyonu ile, bir thread'in sonlanmasını bekleyebiliriz. Bu fonksiyonun kullanıldığı thread,
sonlanması beklenen thread sonlanana kadar bloklanacaktır.
Bazen pthread_join ile join işlemi yapmanın anlamlı olmadığı, thread'in ne zaman sonlanacağının
öngörülemediği durumlar olabilir.
Bu durumda thread return ettiği noktada tüm kaynakların sisteme otomatik olarak geri verilmesini sağlayabiliriz.
Bunu sağlamak için ise, ilgili thread'leri, DETACHED durumu ile başlatmamız gerekmektedir.
Bir thread başlatılırken thread attribute değerleri üzerinden veya pthread_detach fonksiyonu ile DETACH durumu belirtiebilir:
int pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
int pthread_detach(pthread_t thread);
*/

void *worker(void *data)
{
    char *name = (char *)data;
    int i;

    for (i=0; i<120; i++)
    {
        usleep(50000);
        printf("%d. Hello from thread %s\n",i,name);
    }
    printf("Thread %s done...\n",name);
    return NULL;
}

int main()
{

    pthread_t thread1,thread2;

    pthread_create(&thread1,NULL,worker,"A");
    pthread_create(&thread2,NULL,worker,"B");

    sleep(5);

    printf("\n\nExiting from main program\n\n");

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    return 0;
}
