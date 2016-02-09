#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;


void test_shmSysV()
{
    int size = 16; // 2024*1024
    key_t key = ftok("//tmp//mem.tmp", 1);
    int shm_id = shmget(key, size, IPC_CREAT | 0777);
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
    char str[17] = {0};
    cout << "data = \n" << (char* )memcpy(str, (char *)data, size) << endl;
    char c = 31;
    void* p = memset(data, c, size);
    cout << "p = \n" << (char* )memcpy(str, (char *)p, size) << endl;
}

int main(int argc, char* argv[])
{
    test_shmSysV();

    return 0;
}
