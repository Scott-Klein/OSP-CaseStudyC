/* logserver.c -- implementation of the log server */
#include <signal.h>
#include "logservice.h"

int main()
{
    struct message buffer;

    printf("Generating Key\n");

    key_t key;

    key = ftok("logServer.o", 'S');
    printf("Key created\nReadying Message Queue\n");
    int queueId = msgget(key, IPC_EXCL | IPC_CREAT);

    if (queueId == -1)
    {
        perror("Message Queue Failure: ");
        exit(-1);
    }
    printf("Starting message read.\n");
    while (1)
    {
        msgrcv(queueId, &buffer, sizeof(buffer), 1, 0);
        printf("Message: %s\n", buffer.message);
    }

    return 0;
}
