#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 6805
#define IP	"10.30.242.209"
#define MX_SIZE 1024

void dump(const unsigned char *data_buffer, const unsigned int length) {
	unsigned char byte;
	unsigned int i, j;
	for(i=0; i < length; i++) {
		byte = data_buffer[i];
		printf("%02x ", data_buffer[i]); // Display byte in hex.
		if(((i%16)==15) || (i==length-1)) {
			for(j=0; j < 15-(i%16); j++)
				printf(" ");
			printf("| ");
			for(j=(i-(i%16)); j <= i; j++) { // Display printable bytes from line.
				byte = data_buffer[j];
				if((byte > 31) && (byte < 127)) // Outside printable char range
					printf("%c", byte);
				else
					printf(".");
			}
			printf("\n"); // End of the dump line (each line is 16 bytes)
		} // End if
	}
}

int main()
{
	int			rcv_length;
	int			srv_fd, cl_fd;
	char			buffer[MX_SIZE];
	struct sockaddr_in	srv_addr, clt_addr;
	socklen_t		size;

	srv_fd = socket(AF_INET, SOCK_STREAM, 0);
	size  = sizeof(srv_addr);
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(PORT);
	inet_aton(IP, &srv_addr.sin_addr);
	
	bind(srv_fd, (struct sockaddr *)&srv_addr, size);
	listen(srv_fd, 5);
	while (1)	
	{
		cl_fd = accept(srv_fd, (struct sockaddr *)&clt_addr, &size);
		printf("server got connection from %s %d\n", inet_ntoa(clt_addr.sin_addr), ntohs(clt_addr.sin_port));
		send(cl_fd, "Hello, World!\n", 13, 0);
		rcv_length = recv(cl_fd, &buffer, MX_SIZE, 0);
		while (rcv_length > 0)
		{
			printf("RCV %d bytes\n", rcv_length);
			dump(buffer, rcv_length);
			rcv_length = recv(cl_fd, &buffer, MX_SIZE, 0);
		}
	}
	


}
