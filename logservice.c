/* logservice.c -- implementation of the log service */
#include "logservice.h"

int logServiceInit()
{
    int id = -1; //Make no assumptions
    key_t key = 1234;

    id = msgget(key, 0666);
    if (id == -1)
    {
        perror("Queue attach fail");
        exit(EXIT_FAILURE);
    }
    printf("attached to queue id %d\n", id);
    return id;
}

int logMessage(int serviceId, char*message)
{
    int rv = -1;
    struct message payload;
    payload.type = 1;
    strncpy(payload.message, message, MSGCHARS);
    payload.message[MSGCHARS - 1] = '\0';

    printf("PAYLOAD MESSAGE IS : %s\n", payload.message);

    rv = msgsnd(serviceId, &payload, sizeof(payload.message), 0);
    if (rv == -1)
    {
        printf("Couldnt' add message to queue");
        perror("Error Queueing");
        exit(EXIT_FAILURE);
    }
    if (rv == 0)
    {
        printf("Call to msgsnd apparently succeeded\n");
    }

    return rv;
}
