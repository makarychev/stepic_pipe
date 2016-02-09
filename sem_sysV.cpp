#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
                                                           
union semun {
            int val;
            struct semid_ds *buf;
            unsigned short  *array;
} arg;

void test_sem_sysV()
{
    const int arrSize = 16;
    key_t key = ftok("//tmp//sem.temp", 1);
    int sem_id = semget(key, arrSize, IPC_CREAT | 0777);
    for (int i = 0; i < arrSize; i++)
    {
        arg.val = i;
        semctl(sem_id, i, SETVAL, arg);
    }
}

int main(int argc, char* argv[])
{
    test_sem_sysV();

    return 0;
}
