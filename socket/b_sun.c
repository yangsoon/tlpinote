#include "tlpi_hdr.h"
#include <sys/socket.h>
#include <sys/un.h>

int main(){
		const char *SOCKNAME = "/tmp/mysock";
		int sfd;
		struct sockaddr_un addr;
		sfd = socket(AF_UNIX, SOCK_STREAM, 0);
		if (sfd == -1) {
			errExit("socket");
		}
		memset(&addr, 0, sizeof(struct sockaddr_un));
		addr.sun_family = AF_UNIX;
		strncpy(addr.sun_path, SOCKNAME, sizeof(addr.sun_path) - 1);
		if(bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
			errExit("bind");
}

