#include <pthread.h> // Compile and link with -pthread.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

static void* thread_func(void * arg)
{
  int *int_value = (int *)arg;
  pid_t pid = getpid();
  FILE* file = fopen("//home//box//main.pid", "w");
  int len = fprintf(file, "%d", pid);
  if (len <= 0)
    printf("fprintf len error\n");
  fclose(file);
  while ((*int_value) != 10000)
  {
     (*int_value)++;
     usleep(10);
  }
  return arg;
}

int main(int argc, char const *argv[]) {
  pthread_t threadId;
  pthread_attr_t attr;
  int s, arg = 0;
  int stack_size = 1024;
  void *res;

  s = pthread_attr_init(&attr);
  if (s != 0)
     handle_error_en(s, "pthread_attr_init");
  if (stack_size > 0) {
    s = pthread_attr_setstacksize(&attr, stack_size);
    if (s != 0)
       handle_error_en(s, "pthread_attr_setstacksize");
  }

  s = pthread_create(&threadId, &attr, &thread_func, (void *)&arg);
  if (s != 0)
      handle_error_en(s, "pthread_attr_destroy");

  s = pthread_attr_destroy(&attr);
  if (s != 0)
     handle_error_en(s, "pthread_attr_destroy");

  pthread_join(threadId, &res);
  if (s != 0)
    handle_error_en(s, "pthread_join");
  return 0;
}
