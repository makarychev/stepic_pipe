#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void pipe_solution()
{
  char path[] = "//home//box//result.out";
  char command[255] = {0};
  char result[255] = {0};
  if (fgets(command, sizeof(command), stdin))
  {
    FILE* fexec = popen(command, "r");
    FILE* fout = fopen(path, "w");
    int len = read(fexec, result, sizeof(result));
    write(fout, result, len);
    // dup2(fileno(fexec), STDIN_FILENO);
    // dup2(fileno(fout), STDOUT_FILENO);
    pclose(fexec);
    fclose(fout);
  }
}

int main(int argc, char **argv)
{
  pipe_solution();
  return 0;
}
