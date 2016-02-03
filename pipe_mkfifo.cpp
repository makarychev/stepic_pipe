#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void test_run()
{
    char sFileInp[] = "//home//box//in.fifo";
    char sFileOut[] = "//home//box//out.fifo";

    int res = mkfifo(sFileInp, 0666);
    res = mkfifo(sFileOut, 0666);

    int fInp = open(sFileInp, O_RDONLY | O_NONBLOCK);
    int fOut = open(sFileOut, O_WRONLY | O_NONBLOCK);

    while (true)
    {
        char buffer[255] = {0};
        int len = read(fInp, buffer, sizeof(buffer));
        if (len > 0)
        {
            int size = 0;
            while (size < len)
                size += write(fOut, buffer, len);
        }
    }
}

int main(int argc, char **argv)
{
    test_run();
    return 0;
}
