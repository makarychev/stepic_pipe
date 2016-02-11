#include <pthread.h> // Compile and link with -pthread.
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

void* thread_func(void * arg)
{
  int *int_value = (int *)arg;
  pid_t pid = getpid();
  FILE* file = fopen("//home//box//main.pid", "w");
  int len = fprintf(file, "%d", pid);
  if (len <= 0)
    printf("fprintf len error\n");
  fclose(file);
  while ((*arg) != 10000)
  {
     (*int_value)++;
     usleep(10);
  }
  returnt arg;
}

int main(int argc, char const *argv[]) {
  pthread_t threadId;
  pthread_attr_t attr;
  int arg = 0;
  void *res;

  s = pthread_attr_init(&attr);
  if (s != 0)
     handle_error_en(s, "pthread_attr_init");
  if (stack_size > 0) {
    s = pthread_attr_setstacksize(&attr, stack_size);
    if (s != 0)
       handle_error_en(s, "pthread_attr_setstacksize");
  }

  s = pthread_create(&threadId, NULL, void *(*thread_func)(void*), (void *)&arg);
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
