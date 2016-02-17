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

pthread_mutex_t m_mutex;
pthread_cond_t m_cond;
pthread_barrier_t m_bar;

void WritePIDtoFile()
{
  pid_t pid = getpid();
  FILE* file = fopen("//home//box//main.pid", "w");
  int len = fprintf(file, "%d", pid);
  if (len <= 0)
    printf("fprintf len error\n");
  fclose(file);
}

static void* thread_waitCondition(void * arg)
{
  int *int_value = (int *)arg;

  pthread_cond_wait(&m_cond, &m_mutex);
  (*int_value)++;

  return arg;
}
static void* thread_waitBarrier(void * arg)
{
  int *int_value = (int *)arg;

  pthread_barrier_wait(&m_bar);
  (*int_value)++;

  return arg;
}

int main(int argc, char const *argv[]) {
  pthread_t threadWaitCond;
  pthread_t threadWaitBarrier;
  pthread_attr_t attr;
  int s, arg = 0;
  int stack_size = 1024;
  void *res;


  pthread_mutex_init(&m_mutex, NULL);
  pthread_cond_init(&m_cond, NULL);
  pthread_barrier_init(&m_bar, NULL, 2);

  WritePIDtoFile();
  s = pthread_attr_init(&attr);
  if (s != 0)
     handle_error_en(s, "pthread_attr_init");
  if (stack_size > 0) {
    s = pthread_attr_setstacksize(&attr, stack_size);
    if (s != 0)
       handle_error_en(s, "pthread_attr_setstacksize");
  }

  pthread_mutex_lock(&m_mutex);

  s = pthread_create(&threadWaitCond, &attr, &thread_waitCondition, (void *)&arg);
  if (s != 0)
      handle_error_en(s, "pthread_create thread_waitCondition");
  s = pthread_create(&threadWaitBarrier, &attr, &thread_waitBarrier, (void *)&arg);
  if (s != 0)
      handle_error_en(s, "pthread_create thread_waitBarrier");

  s = pthread_attr_destroy(&attr);
  if (s != 0)
     handle_error_en(s, "pthread_attr_destroy");

  s = pthread_join(threadWaitCond, &res);
  if (s != 0)
    handle_error_en(s, "threadWaitCond");
  s = pthread_join(threadWaitBarrier, &res);
  if (s != 0)
    handle_error_en(s, "threadWaitBarrier");

  pthread_mutex_unlock(&m_mutex);
  pthread_cond_signal(&m_cond);

  pthread_barrier_wait(&m_bar);


  pthread_mutex_destroy(&m_mutex);
  pthread_cond_destroy(&m_cond);
  pthread_barrier_destroy(&m_bar);

  return 0;
}
