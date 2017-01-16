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
