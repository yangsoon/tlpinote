#include "us_xfr.h"
#define BACKLOG 5

int main(int argc, char *argv[]){
		struct sockaddr_un addr;
		int sfd, cfd;
		ssize_t numRead;
		char buf[BUF_SIZE];
		/* socket(int domain, int type, int protocol)
		domain 指定socket通信域 type socket类型 流/数据报 protocol 一般使用0 */
		sfd = socket(AF_UNIX, SOCK_STREAM, 0);
		if (sfd == -1)
			errExit("socket");

		if (strlen(SV_SOCK_PATH) > sizeof(addr.sun_path) - 1) {
			fatal("Server socket path too long");
		}

		if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT) {
			errExit("remove");
		}

		memset(&addr, 0, sizeof(struct sockaddr_un));
		addr.sun_family = AF_UNIX;
		strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

		if(bind(sfd, (struct sockaddr *) &addr, sizeof(addr.sun_path)) == -1){
			errExit("bind");
		}

		if(listen(sfd, BACKLOG) == -1)
			errExit("listen");

		while(1){
			cfd = accept(sfd, NULL, NULL);
			if (cfd == -1){
				errExit("accept");
			}
			while((numRead = read(cfd, buf, BUF_SIZE)) > 0) {
				if(write(STDOUT_FILENO, buf, numRead) != numRead)
					fatal("fail write");
			}

			if (numRead == -1)
				errExit("read");

			if(close(cfd) == -1)
				errMsg("close");
		}
}
