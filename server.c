#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <netdb.h>

#define MAXLINE 1024 
#define BUFFER 1024 
// Driver code 
int main(int argc, char *argv[]) { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char message[BUFFER];
    struct sockaddr_in servaddr, cliaddr; 
    
    char *hostaddrp;
     if(argc < 2) {  
        printf(" error");  
        exit(1);  
} 
 
 uint16_t port = atoi( argv[ 1 ] ); 
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);; 
    servaddr.sin_port = htons(port); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int len, n; 
  
    len = sizeof(cliaddr);  //len is value/resuslt 
    while (1) {
    bzero(buffer, MAXLINE);    
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len); 

    printf("server received  message %c%cfrom client: %s\n", MAXLINE, n, (char *)buffer); 
    
     printf ("enter your message: ") ;
     if (fgets(message, BUFFER, stdin) != NULL) {
    sendto(sockfd, (const char *)message, strlen(message),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len); 
     }
    }
    printf("Hello message sent.\n");  
      
    return 0; 
}
