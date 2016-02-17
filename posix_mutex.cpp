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
pthread_spinlock_t m_spinlock;
pthread_rwlock_t m_rwlock;

void WritePIDtoFile()
{
  pid_t pid = getpid();
  FILE* file = fopen("//home//box//main.pid", "w");
  int len = fprintf(file, "%d", pid);
  if (len <= 0)
    printf("fprintf len error\n");
  fclose(file);
}

static void* thread_waitMutex(void * arg)
{
  int *int_value = (int *)arg;

  pthread_mutex_lock(&m_mutex);
  (*int_value)++;
  pthread_mutex_unlock(&m_mutex);
  return arg;
}

static void* thread_waitSpinMutex(void * arg)
{
  int *int_value = (int *)arg;

  pthread_spin_lock(&m_spinlock);
  (*int_value)++;
  pthread_spin_unlock(&m_spinlock);
  return arg;
}

static void* thread_waitRdMutex(void * arg)
{
  int *int_value = (int *)arg;

  pthread_rwlock_rdlock(&m_rwlock);
  (*int_value)++;
  pthread_rwlock_unlock(&m_rwlock);
  return arg;
}

static void* thread_waitWrMutex(void * arg)
{
  int *int_value = (int *)arg;

  pthread_rwlock_wrlock(&m_rwlock);
  (*int_value)++;
  pthread_rwlock_unlock(&m_rwlock);
  return arg;
}

int main(int argc, char const *argv[]) {
  pthread_t threadWaitMutex;
  pthread_t threadWaitSpinMutex;
  pthread_t threadWaitRdMutex;
  pthread_t threadWaitWrMutex;
  pthread_attr_t attr;
  int s, arg = 0;
  int stack_size = 1024;
  void *res;


  pthread_mutex_init(&m_mutex, NULL);
  pthread_spin_init(&m_spinlock, PTHREAD_PROCESS_SHARED);
  pthread_rwlock_init(&m_rwlock, NULL);

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
  pthread_spin_lock(&m_spinlock);
  pthread_rwlock_rdlock(&m_rwlock);
  pthread_rwlock_wrlock(&m_rwlock);


  s = pthread_create(&threadWaitMutex, &attr, &thread_waitMutex, (void *)&arg);
  if (s != 0)
      handle_error_en(s, "pthread_create threadWaitMutex");
  s = pthread_create(&threadWaitSpinMutex, &attr, &thread_waitSpinMutex, (void *)&arg);
  if (s != 0)
      handle_error_en(s, "pthread_create threadWaitSpinMutex");
  s = pthread_create(&threadWaitRdMutex, &attr, &thread_waitRdMutex, (void *)&arg);
  if (s != 0)
      handle_error_en(s, "pthread_create threadWaitRdMutex");
  s = pthread_create(&threadWaitWrMutex, &attr, &thread_waitWrMutex, (void *)&arg);
  if (s != 0)
      handle_error_en(s, "pthread_create threadWaitWrMutex");

  s = pthread_attr_destroy(&attr);
  if (s != 0)
     handle_error_en(s, "pthread_attr_destroy");

  s = pthread_join(threadWaitMutex, &res);
  if (s != 0)
    handle_error_en(s, "threadWaitMutex");
  s = pthread_join(threadWaitSpinMutex, &res);
  if (s != 0)
    handle_error_en(s, "threadWaitSpinMutex");
  s = pthread_join(threadWaitRdMutex, &res);
  if (s != 0)
    handle_error_en(s, "threadWaitRdMutex");
  s = pthread_join(threadWaitWrMutex, &res);
  if (s != 0)
    handle_error_en(s, "threadWaitWrMutex");

  pthread_mutex_unlock(&m_mutex);
  pthread_spin_unlock(&m_spinlock);
  pthread_rwlock_unlock(&m_rwlock);

  pthread_mutex_destroy(&m_mutex);
  pthread_spin_destroy(&m_spinlock);
  pthread_rwlock_destroy(&m_rwlock);

  return 0;
}
