/* logserver.c -- implementation of the log server */
#include <signal.h>
#include "logservice.h"

void finish();
void exitFailure();

int main()
{
    signal(SIGINT, finish);
    struct message buffer;
    buffer.type = 1;
    printf("Generating Key\n");

    key_t key = 1234;

    if (key == -1)
    {
        printf("Key fail");
        exitFailure();
    }

    printf("Key created\nReadying Message Queue\n");
    int queueId = msgget(key, 0666 | IPC_EXCL | IPC_CREAT);
    if (queueId == -1)
    {
        exitFailure();
    }
    printf("Attached to queue %d\n", queueId);
    printf("Starting message read.\n");

    if (msgrcv(queueId, &buffer, sizeof(buffer.message), 1, 0) == -1)
    {
        exitFailure();
    }
    printf("Message: %s\n", buffer.message);
    printf("Collected message from queue");
    finish();
    return 0;
}

void exitFailure()
{
    perror("Message");
    exit(EXIT_FAILURE);
}

void finish()
{
    key_t key;
    key = 1234;
    int queueId = msgget(key, 0666);
    if (queueId == -1)
    {
        printf("Queue get ");
        exitFailure();
    }

    if (msgctl(queueId, IPC_RMID, NULL) > -1)
    {
        printf("\nMessage queue deleted successfully\n");
    }
    else
    {
        perror("\nQueue Not deleted\n");
    }
    exit(EXIT_SUCCESS);
}