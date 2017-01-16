# Thread
Thread Tutorial

// pthread kütüphanesi kullanıldığında linkleme :
// gcc -o example example_thread.c -lpthread

/* Bir process ile main thread oluşturulur - main thread
   Process içerisinde birden fazla multi thread oluşturulabilir
   Her threadin kendine ait : program sayacı,saklayıcıları, 
   yığını ve durumu vardır.
   Bir threaddeki değişkeni aynı işlem tarafından üretilmiş
   bütün threadler değiştirebilir veya okuyabilir.
   Threadlerin amaci çoklu görevlerde senkrenizasyonu sağlamak.
   Eğer bu threadler aynı anda aynı bölgeye girerse hatalar 
   meydana gelir. - deadlock
   Multithreading aynı anda birden çok iş yapmamızı sağlar.Böylece 
   arayüz
   kitlenmez.
   Threadi genelde arka planda sürekli çalışmasını istediğimiz
   program parçaları için kullanırız.
   Antivürüs programı thread teknolojisini kullanır.
   Linux altında thread kullanımı C kütüphanesinin bir parçası olan 
   pthread kütüphanesi 
   ile yapılmaktadır.
   Çalışan thread implementasyonunu getconf GNU_LIBPTHREAD_VERSION 
   komutuyla öğrenebilirsiniz.
   Her program başlatıldığında, bir kernel thread'i de otomatik olarak 
   oluşturulur.
   Çalışan herhangi bir process'in thread spesifik bilgileri /proc/<PID>/task 
   dizini altında yer alır. Single-thread uygulamalar için de bu dizin altında 
   PID ile aynı değere sahip bir task kaydı olduğu görünecektir.
   Threadler ana program ile aynı adresleme alanını ve aynı file descriptor
   'ları kullanırlar.
   Pthread kütüphanesi aynı zamanda senkronizasyon işlemleri için gerekli mutex 
   ve conditional işlemleri için gerekli desteği de içermektedir.
*/

Yeni bir thread oluşturmak için pthread_create fonksiyonu kullanılır.

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)

Başarılı durumda 0 döner. Hata durumunda ise geriye bir hata kodu dönecektir.+
thread parametresi pthread_t türünde olup önceden tanımlanması gerekir. Oluşan thread'e bu referansla her zaman erişilebilecektir.
attr parametresi thread spesifik olarak pthread_attr_ ile başlayan fonksiyonlarla ayarlanmış, scheduling policy, stack büyüklüğü, detach policy gibi kuralları gösterir.
start_routine thread tarafından çalıştırılacak olan fonksiyonu gösterir.
arg ise thread tarafından çalıştırılacak fonksiyona geçirilecek void*'a cast edilmiş genel bir veri yapısını göstermektedir.





