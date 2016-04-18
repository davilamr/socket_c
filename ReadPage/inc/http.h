#define BUFFER_LIMIT 2048
#define SOURCE_START_IDENTIFIER "<!DOCTYPE"
#define SOURCE_START_IDENTIFIER2 "<html>" 		//this is the name of the identifier that the

int getHttp(char* content,long contentSize,char* site,char* file, int verbose);
