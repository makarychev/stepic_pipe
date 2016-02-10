#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

void test_shmSysV()
{
    int size = 1024*1024; //
    key_t key = ftok("/tmp/mem.temp", 1);
    int shm_id = shmget(key, size, IPC_CREAT | 0777);
    if (shm_id < 0) {
            printf("shmget error = %d\n", shm_id);
            return;
    }
    void *data = shmat(shm_id, 0, 0);
    if (data == (char *)-1)
    {
            printf("shmat error\n");
            return;
    }
    char c = 42;
     void* p = memset(data, c, size);
 }

 int main(int argc, char* argv[])
 {
    test_shmSysV();

    return 0;
}
