#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(void){
	int listenfd = 0;
	int connfd = 0;
	int n = 0;

	struct sockaddr_in serv_addr;

	char sendBuff[1024];
	char recvBuff[1024];

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("socket retrieve success\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	serv_addr.sin_port = htons(5000);    

	bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

	if(listen(listenfd, 10) == -1){
		printf("Failed to listen\n");
		return -1;
	}

	while(1){
		connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request

		strcpy(sendBuff, "Message from server");
		write(connfd, sendBuff, strlen(sendBuff));

		while(strcmp(recvBuff,"exit") != 0){
			memset(recvBuff, '\0', sizeof(recvBuff));
			n = read(connfd,recvBuff,255);
			if (n < 0){
				printf("Error\n");
			}
			printf("%s\n",recvBuff);
			if( n < 0){
				printf("\n Read Error \n");
			}
		}
		printf("Closing connection\n");
		close(connfd);
		sleep(1);
	}
	return 0;
}