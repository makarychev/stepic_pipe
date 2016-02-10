#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <stdio.h>
#include <time.h>

void mq_test()
{
        struct mq_attr attr;
        attr.mq_flags = 0;
        attr.mq_maxmsg = 10;
        attr.mq_msgsize = 64;
        attr.mq_curmsgs = 0;
        mode_t mode = S_IRUSR | S_IWUSR |S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
        mqd_t mq_id = mq_open("/test.mq", O_RDWR | O_CREAT, mode, &attr);
        char buff[64] = {0};
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 120;
        int size = mq_timedreceive(mq_id, buff, 64, NULL, &ts);
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
