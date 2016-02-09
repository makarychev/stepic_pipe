#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>
#include <mqueue.h>
#include <stdio.h>

void mq_test()
{
  struct mq_attr attr;
  mode_t omask;
  omask = umask(0);
  mqd_t mq_id = mq_open("//test.mq", O_RDONLY, (S_IRWXU | S_IRWXG | S_IRWXO), &attr); //  | O_NONBLOCK
  umask(omask);
  char buff[255] = {0};
  int size = mq_receive(mq_id, buff, sizeof(buff), NULL);
  if (size > 0)
  {
    FILE* file = fopen("//home//box//message.txt", "w");
    int len = fwrite(buff, 1, size, file);
    fclose(file);
  }

  int res = mq_close(mq_id);
}


int main()
{
  mq_test();
  return 0;
}


#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <stdio.h>

void mq_test()
{
        struct mq_attr attr;
        attr.mq_flags = O_RDONLY;                                                      
        attr.mq_maxmsg = 20;
        attr.mq_msgsize = 1024;
        attr.mq_curmsgs = 0;
        mqd_t mq_id = mq_open("//test.mq", O_CREAT | O_RDONLY, 0777, &attr);
        char buff[255] = {0};
        int size = mq_receive(mq_id, buff, sizeof(buff), NULL);
        if (size > 0)
        {
                FILE* file = fopen("//home//box//message.txt", "w");
                int len = fwrite(buff, 1, size, file);
                fclose(file);
        }
        int res = mq_close(mq_id);
}

int main()
{
mq_test();
return 0;
}
