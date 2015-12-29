#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(void){
	int sockfd = 0;
	int n = 0;
	char recvBuff[1024];
	char sendBuff[1024];
	struct sockaddr_in serv_addr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0){
		printf("\n Error : Could not create socket \n");
		return 1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
		printf("\n Error : Connect Failed \n");
		return 1;
	}

	n = read(sockfd,recvBuff,255);
	if (n < 0){
		printf("Error\n");
	} 
	printf("%s\n",recvBuff);
	printf("Kommet hit \n");
	while(1) {
		printf("Enter your message: ");
		fgets (sendBuff, 1024, stdin);
		strtok(sendBuff, "\n");
		write(sockfd, sendBuff, strlen(sendBuff));
	}

	return 0;
}