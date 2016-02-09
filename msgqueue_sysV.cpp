#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

struct message {
    long mtype;
    char mtext[80];
};

void recvMsg_test()
{
  key_t key = ftok("//tmp//msg.temp", 1);
  int msg_qid = msgget(key, IPC_CREAT | 0777);
  message msg;
  int size = 0;
  // wait while some process write in queue msg
  while ((size = msgrcv(msg_qid, (void *)&msg, sizeof(msg.mtext), 0, )) != 0) {
    /* code */
    FILE* file = fopen("//home//box//message.txt", "w");
    int len = fwrite((char *)msg.mtext, 1, size, file);
    fclose(file);
    break; // after reading go to exit
  }
  // msgctl(msg_qid, IPC_RMID, NULL)
}


int main()
{
  recvMsg_test();
  return 0;
}
