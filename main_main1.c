#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "stdlib.h"

typedef struct client {
	int id;
	char msg[110000];
} t_client;

t_client clients[100];


void fatal() {
	write(2, "fatal\n", 6);
	exit(1);
}

int listener_fd;

int port;
int main(int argc, char **argv) {
	if (argc != 2) {
		fatal();
	}
	port = atoi(argv[1]);
	// socket create and verification 
	if ((listener_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fatal();
	}
	struct sockaddr_in servaddr;
	int adr_len = sizeof (servaddr);
	bzero(&servaddr, sizeof(servaddr));
	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port);
  
	// Binding newly created socket to given IP and verification 
	if ((bind(listener_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
		fatal();
	}

	if (listen(listener_fd, 100) != 0) {
		fatal();
		exit(0); 
	}
	l	len = sizeof(cli);
	connfd = accept(listener_fd, (struct sockaddr *)&servaddr, &adr_len);
	if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n");
}