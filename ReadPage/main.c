#include <stdio.h>
#include <stdlib.h>
#include "inc/http.h"

#define RECV_LIMIT 5242880 //5Mb

int main(int argc , char *argv[])
{
    char content[RECV_LIMIT+1];

    //getHttp(content,"www.w3.org","/Protocols/rfc2616/rfc2616-sec5.html",1);
    //getHttp(content,"www.tutorialspoint.com", "/c_standard_library/c_function_memset.htm",1);
    getHttp(content,RECV_LIMIT,"www.mocky.io", "/v2/571504b40f0000522349059d",1); //https://www.mockaroo.com


    printf("%s",content);

    return 0;

}
