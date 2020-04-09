/* logclient.c -- implements a simple log service client */
#include "logservice.h"

int main(int argc,char**argv)
{
    int id = logServiceInit();
    logMessage(id, "Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. Operating Systems programming is cool. ");
    printf("Message sent successfully\n");
    return 0;
}

