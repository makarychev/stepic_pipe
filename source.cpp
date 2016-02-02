#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void who_wc()
{
    int pipe1[2];
    int pipe2[2];
    int pipe3[2];
    pipe(pipe1);

    if (!fork())
    {
        if (!fork())
        {
            close(STDOUT_FILENO);
            dup2(pipe1[1], STDOUT_FILENO);
            close(pipe1[0]);
            close(pipe1[1]);
            close(pipe2[0]);
            close(pipe2[1]);
            execlp("ls", "ls", NULL);
        }
        else
        {
            close(STDOUT_FILENO);
            close(STDIN_FILENO);
            dup2(pipe1[0], STDIN_FILENO);
            dup2(pipe2[1], STDOUT_FILENO);
            close(pipe1[0]);
            close(pipe1[1]);
            close(pipe2[0]);
            close(pipe2[1]);
            execlp("grep", "grep", "sour*", NULL);
        }
    } else
    {
        close(STDIN_FILENO);
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        execlp("wc", "wc", "-l", NULL);
    }
}

int main (int argc, char ** argv)
{
    who_wc();
    return 0;
}
