#include <sys/mman.h> // Link with -lrt.
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h> /* For O_* constants */
#include <string.h>
#include <unistd.h> // ftruncate

void test()
{
    mode_t mode = S_IRUSR | S_IWUSR |S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int shm_id = shm_open("/test.shm", O_RDWR | O_CREAT, mode);
    int res = ftruncate(shm_id, 1024*1024);

    void * data = mmap(0,
                    1024*1024,
                    PROT_WRITE,
                    MAP_SHARED,
                    shm_id,
                    0);
    char c = 13;
    memset(data, c, 1024*1024);
    munmap(0, 1024*1024);
}


int main(int argc, char* argv[])
{
    test();

    return 0;
}
