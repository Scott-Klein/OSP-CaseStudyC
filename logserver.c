/* logserver.c -- implementation of the log server */
#include <signal.h>
#include "logservice.h"

void finish();
void exitFailure(char* failType);

int main()
{
    signal(SIGINT, finish);
    struct message buffer;
    buffer.type = 1;
    printf("Generating Key\n");

    key_t key = KEY;
    if (key == -1)
    {
        exitFailure("Key failure");
    }

    int queueId = msgget(key, 0666 | IPC_EXCL | IPC_CREAT);
    if (queueId == -1)
    {
        exitFailure("Message Queue failure");
    }
    printf("Attached to queue %d\n", queueId);
    while (1)
    {
        printf("\nWaiting for message\n");
        if (msgrcv(queueId, &buffer, sizeof(buffer.message), 0, 0) == -1)
        {
            exitFailure("Message receive failure");
        }
        printf("Message recieved from process: %ld\n", buffer.type);
        printf("Message contents: %s\n", buffer.message);
    }

    finish();
}

void exitFailure(char* failType)
{
    perror("Message");
    exit(EXIT_FAILURE);
}

void finish()
{
    key_t key = KEY;
    int queueId = msgget(key, 0666);
    if (queueId == -1)
    {
        exitFailure("Message Queue failure");
    }
    if (msgctl(queueId, IPC_RMID, NULL) > -1)
    {
        printf("\nMessage queue deleted successfully\n");
    }
    else
    {
        exitFailure("Queue deletion fail");
    }
    exit(EXIT_SUCCESS);
}

