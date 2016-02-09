#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

void test_shmSysV()
{
        key_t key = ftok("//tmp//mem.tmp", 1);
        int shm_id = shmget(key, 1024*1024, IPC_CREAT | 0777);
        if (shm_id < 0) {
                printf("shmget error = %d\n", shm_id);
                return;
        }
        void *data = shmat(shm_id, (void *)0, 0);
        if (data == (char *)-1)
        {
                printf("shmat error\n");
                return;
        }
        char c = 42;
        memset(res, c, 1);
}

int main(int argc, char* argv[])
{
    test_shmSysV();

    return 0;
}
