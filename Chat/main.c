#include <stdio.h>
#include <stdlib.h>
#include "inc/client.h"
#include "inc/server.h"


int main()
{
    //runServer(1200);
    runClient("127.0.0.1",1200);
    printf("Hello world!\n");
    return 0;
}
