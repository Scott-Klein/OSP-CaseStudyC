/* logclient.c -- implements a simple log service client */
#include "logservice.h"

int main(int argc,char**argv)
{
    printf("Init log service ...\n");
    int id = logServiceInit();

    printf("logging message...\n");
    logMessage(id, "Fuck this bullshit");
    return 0;
}

