#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 6805
#define IP	"10.30.242.211"
#define MX_SIZE 4096

int main(int argc, char **argv)
{
	int num = atoi(argv[1]);
	char buff[MX_SIZE];
	int n;
	int err;
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in	srv_addr, client_addr;
	socklen_t		size;
	
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(PORT);
	inet_aton(IP, &srv_addr.sin_addr);
	size = sizeof(srv_addr);

	for (int i = 0; i < num; ++i) {
		err = connect(fd, (struct sockaddr *)&srv_addr, size);
		if (err)
			printf("error\n");
		printf("%d: connected %d\n", getpid(), err);
		close(fd);
		fd = socket(AF_INET, SOCK_STREAM, 0);
	}

	printf("good by\n");
/*	n = read(fd, buff, MX_SIZE);
	buff[n] = 0;
	printf("client got: %s\n", buff);*/
}
