/* logservice.c -- implementation of the log service */
#include "logservice.h"

int logServiceInit()
{
	int id = -1; //Make no assumptions
    key_t key = ftok("logServer.o", 'S');
    id = msgget(key, 0666);
    return id;
}

int logMessage(int serviceId, char*message)
{
	int rv = -1;
    struct message payload;
    payload.type = 5;
    strncpy(payload.message, message, MSGCHARS);
    payload.message[MSGCHARS - 1] = '\0';

    msgsnd(serviceId, &message, sizeof(message), 0);

    return rv;
}
