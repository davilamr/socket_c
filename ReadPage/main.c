#include<stdio.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

#define RESPONSE_RECV_LIMIT 200000
#define BUFFER_LIMIT 8192
#define SOURCE_START_IDENTIFIER "<!DOCTYPE"
#define SOURCE_START_IDENTIFIER2 "<html>" 		//this is the name of the identifier that the


int main(int argc , char *argv[])
{


	//char response[RESPONSE_RECV_LIMIT + 1];  // + 1 is for null
	char* response = malloc(RESPONSE_RECV_LIMIT+1);
	char* buffer = malloc(BUFFER_LIMIT+1);

	char *source;
	int sockfd,newfd,err;
	char ip[INET6_ADDRSTRLEN];
	struct addrinfo *p,hints,*res;
	int len,len_s;
	int yes=1;
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	void *addr;
	char *ver;
	char request[1000];
	int n;

	char port[] = "80";
    char site[] = "www.w3.org";
    char file[] = "/Protocols/rfc2616/rfc2616-sec5.html";


	sprintf(request,"GET %s HTTP/1.1\r\nHost: %s\r\n\r\n",file,site);

	// print the request we are making

	printf("%s\n\n",request);

	memset(&hints,0,sizeof hints);

	hints.ai_socktype=SOCK_STREAM;

	hints.ai_family=AF_UNSPEC;

	if ((err = getaddrinfo(site,port, &hints, &res)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
		return 1;
	}

	for(p=res;p!=NULL;p=p->ai_next)
	{
		if( ( sockfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol) ) == -1)
		{
			printf("Socket error !!!\n");
			return(0);
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

	/*if( recv(sockfd,response,RESPONSE_RECV_LIMIT,0) == 0 )
	{
		perror("Recv : ");
		return(1);
	}*/

    n = 0;
    response[0] = '\0';
    do{
        n = read(sockfd,buffer,BUFFER_LIMIT);
        strcat(response,buffer);

    }while(n > 0);

	close(sockfd); // we dont need it any more

    printf("LARGO : %ld\n\n",strlen(response));

	printf("%s",response); // for debugging purposes



	//source = strstr(response,SOURCE_START_IDENTIFIER);

	if(source == NULL)
	{
		//source = strstr(response,SOURCE_START_IDENTIFIER2);
	}
	//printf("%s\n",source);
	return(0);
}
