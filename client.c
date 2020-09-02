#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <netdb.h>  
#include "chat.h"
#define MAXLINE 1024 
#define BUFFER 1024  
// Driver code 
int main(int argc, char *argv[]) { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char message[BUFFER]; 
   struct hostent *hostp;
    char *hostaddrp;
    struct sockaddr_in     servaddr; 
   if(argc  != 3)  
   {  
       printf("Usage : %s Server-IP\n",argv[1]);  
       return 0;      
   } 
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  uint16_t port = atoi( argv[2] ); 
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(port); 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
      
    int n, len; 
     printf ("enter your message: ") ;
     if (fgets(message, BUFFER, stdin) != NULL) {
    sendto(sockfd, (const char *)message, strlen(message), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
     }
    printf("Hello message sent.\n"); 
          
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len); 
    buffer[MAXLINE] = '\0';
    printf("received  message %c %c from sever: %s\n", MAXLINE, n, (char *)buffer);  
  
    close(sockfd); 
    return 0; 
} 