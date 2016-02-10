#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h> // Link with -pthread.

void test_semposix()
{
  sem_t * sem_local = sem_open("/test.sem", O_RDWR | O_CREAT, 0777, 66);
  //int res = sem_setvalue()

  sem_close(sem_local);
}


int main(int argc, char const *argv[]) {
  test_semposix();
  return 0;
}
