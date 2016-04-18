#include <stdio.h>
#include <stdlib.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include <unistd.h>
#include "inc/http.h"

int getHttp(char* content,long contentSize,char* site,char* file, int verbose)
{
    char response[BUFFER_LIMIT];

    char *source;
    int sockfd,err;
    struct addrinfo *p,hints,*res;
    char request[1000];
    int bytes,received;

    char port[] = "80";



    sprintf(request,"GET %s HTTP/1.1\r\nHost: %s\r\n\r\n",file,site);

    //printf("%s\n\n",request);

    memset(&hints,0,sizeof hints);

    hints.ai_socktype=SOCK_STREAM;

    hints.ai_family=AF_UNSPEC;

    if ((err = getaddrinfo(site,port, &hints, &res)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        return -1;
    }

    for(p=res; p!=NULL; p=p->ai_next)
    {
        if( ( sockfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol) ) == -1)
        {
            printf("Socket error !!!\n");
            return(-1);
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("client: connect");
            continue;
        }
    }

    if(send(sockfd,request,strlen(request),0) < strlen(request))
    {
        perror("Send Error!!\n");
    }

    freeaddrinfo(res);

    received = 0;
    do
    {
        // HANDLE RESPONSE CHUCK HERE BY, FOR EXAMPLE, SAVING TO A FILE.
        //memset(response, '\0', sizeof(response));
        bytes = recv(sockfd, response, BUFFER_LIMIT, 0);

        if (bytes < 0)
            printf("ERROR reading response from socket");
        if (bytes == 0)
            break;
        response[bytes] = '\0';
        received+=bytes;
        if (received < contentSize)
        {
            strcat(content, response);
            if(verbose)
                printf("RECIVED %4d BYTES\n",bytes);
        }
        else
        {
            return -1;
        }
    }
    while (1);

    close(sockfd); // we dont need it any more

    //printf("LARGO : %ld - RECEIVED: %d\n\n",strlen(content),received);
    //printf("%s",content); // for debugging purposes



    //source = strstr(response,SOURCE_START_IDENTIFIER);

    if(source == NULL)
    {
        //source = strstr(response,SOURCE_START_IDENTIFIER2);
    }
    //printf("%s\n",source);
    return(0);
}
