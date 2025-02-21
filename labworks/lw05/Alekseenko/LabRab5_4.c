#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/stat.h>
/// Лабораторная работа №5
/// Тема:Организация работы с разделяемой памятью.
/// Задание:Первая программа должна создавать сегмент разделяемой памяти и копировать туда
/// собственный исходный текст, вторая программа должна брать оттуда этот
/// текст, печатать его на экране и удалять сегмент разделяемой памяти из системы.
/// Выполнила студент группы ИСТбд-21 Алексеенко Д.В,

int main()
{
    printf("Выполнил студент группы ИСТбд-21 Алексеенко Д.В.\n");
    key_t key = ftok("/home/dmitry/Documents/", 2);

    // Доступ к созданной области разделяемой памяти в дальнейшем
    // обеспечивается ее дескриптором, который вернет системный
    // вызов shmget().
    int sh = shmget(key, 5000, IPC_CREAT|0777);

    // включить область разде-
    // ляемой памяти в адресное пространство текущего процесса
    char* m = (char*)shmat(sh, NULL, 0);

    printf("%s\n",m);

    // удаляем разделяемую память из адресного
    // пространства текущего процесса и завершаем работу
    shmdt(m);

    // удалить область разделяемой памяти из системы
    // можно воспользоваться и системным вызовом shmctl()
    shmctl(sh, IPC_RMID, NULL);
    return 0;
}
