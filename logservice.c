/* logservice.c -- implementation of the log service */
#include "logservice.h"

int logServiceInit()
{
    int id = -1; //Make no assumptions
    key_t key = KEY;

    id = msgget(key, 0666);
    if (id == -1)
    {
        perror("Queue attach fail");
        exit(EXIT_FAILURE);
    }
    printf("attached to queue id %d\n", id);
    return id;
}

int logMessage(int serviceId, char *message)
{
    int splitCount = 0;
    while (strlen(message) > MSGCHARS)
    {
        char *fragment;
        strncpy(fragment, message, MSGCHARS);
        logMessage(serviceId, fragment);
        message = &message[MSGCHARS - 1];
        printf("Message fragment %d sent.\n", ++splitCount);
    }

    struct message payload;
    payload.type = getpid();
    strncpy(payload.message, message, MSGCHARS);
    payload.message[MSGCHARS - 1] = '\0';

    if (msgsnd(serviceId, &payload, sizeof(payload.message), 0) == -1)
    {
        exitFail("Message not sent");
    }
    return 1; // this line can only be hit if message successfully sent.
}

void exitFail(char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

void recursiveSplit(int serviceId, char *message)
{
    while (strlen(message) > MSGCHARS)
    {
        char *fragment;
        strncpy(fragment, message, MSGCHARS);
        logMessage(serviceId, fragment);
        message = &message[MSGCHARS - 1];
        printf("Recursive splitting");
    }
}