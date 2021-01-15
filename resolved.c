#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

/* Buffer max size */
#define SIZE 100

/* Use `%s` for strings, and `%d` for integers */
/* don't use `&` with `int *` decleared values while using `printf` */
/* dont' forget about `==` one `=` can stop the if statement */
/* avoiding buffer overflow issues by setting the buffer size the same as the get size on `fgets` */

void getip(void *hostname , void *ip);
int main(int argc , char **argv) {
    int socket_in;
    struct sockaddr_in server;

    socket_in = socket(AF_INET , SOCK_STREAM , 0);
    
    /* printf("%d\n" , socket_in); */
    /* printf("%s\n" , HOST); */
    
    if (socket_in == -1) {
        printf("Cound't create socket.\n");
        return -1;
    } else {
        if (argv[1] == NULL){
            printf("You didn't select a file\n");
            return -1;
        } else {
            if (access(argv[1] , F_OK) == 0){
                /* The file exists. */
            } else {
                printf("This file doesn't exists: %s\n" , argv[1]);
                return -1;
            }
        }

        /* Reading the file and creating the loop */
        FILE *file = fopen(argv[1] , "r");
        char ip[SIZE];
        char currentline[SIZE];

        /* While loop for everyline on the file */
        while (fgets(currentline, sizeof(currentline), file) != NULL) {
            /* Define new socket for every host */
            socket_in = socket(AF_INET , SOCK_STREAM , 0);

            /* Eveything fine. */
            currentline[strcspn(currentline, "\n")] = 0;
            getip(currentline , ip);

            server.sin_addr.s_addr = inet_addr(ip);
            server.sin_family = AF_INET;
            server.sin_port = htons(80);

            /* set the ip to blank after connection */
            strcpy(ip , " ");

            if (connect( socket_in , (struct sockaddr *) & server , sizeof(server) ) < 0){
                /* printf("Connection error while tring to access: %s\n" , currentline); */
                /* doing nothing where it can't connect to the host to print clear results */
            } else {
                /* Connection has been created */
                /* printf("Connection has been created to: %s\n" , currentline); */
                printf("%s\n" , currentline);
            }
        }
    }

    return 1;
}

void getip(void *hostname , void *ip)
{
    /* Removing all return values so this function can be used as a void */
	struct hostent *he;
	struct in_addr **addr_list;
	int i;

    if ((he = gethostbyname(hostname)) == NULL) 
	{
		/* nothing here just a comment. */
        	/* printf("%s\n" , hostname); */
        	return;
	}

	addr_list = (struct in_addr **) he->h_addr_list;
	
	for(i = 0; addr_list[i] != NULL; i++) 
	{
		strcpy(ip , inet_ntoa(*addr_list[i]) );
		return;
	}
	
	return;
}
