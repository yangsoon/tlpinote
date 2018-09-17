#include "ud_ucase.h"
#include <unistd.h>

int main(int argc, char *arg[]){
	struct sockaddr_un svaddr, claddr;
	int sfd, j;
	ssize_t numBytes;
	socklen_t len;
	char buf[BUF_SIZE];
	
	sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(sfd == -1){
		errExit("socket");
	}
	
	if (strlen(SV_SOCK_PATH) > sizeof svaddr.sun_path - 1){
		fatal("Server socket too lang");
	}
	
	if(remove(SV_SOCK_PATH) == -1 && errno!=ENOENT){
		errExit("remove");
	}

	memset(&svaddr, 0, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) - 1);

	if(bind(sfd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) == -1){
		errExit("bind");
	}

	while (1) {
		len = sizeof(struct sockaddr_un);
		numBytes = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &claddr, &len);

		sleep(2);

		if (numBytes == -1){
			errExit("recvfrom");
		}
		printf("Server received %ld bytes from %s\n", (long) numBytes, claddr.sun_path);
		
		for (j = 0; j < numBytes; j++){
			buf[j] = toupper((unsigned char) buf[j]);
		}

		// if (sendto(sfd, buf, numBytes, 0, (struct sockaddr *) &claddr, len) != numBytes){
		// 	fatal("sendto");
		// }
	}
}

