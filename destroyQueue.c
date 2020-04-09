#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{

    key_t key;
    key = ftok("logServer.o", 'S');
    int queueId = msgget(key, 0666);
    perror("Couldn't Get QUEUE: ");
    if (msgctl(queueId, IPC_RMID, NULL) > -1)
    {
        printf("Message queue deleted successfully");
    }
    else
    {
        perror("Queue Not deleted");
    }
    return 0;
}