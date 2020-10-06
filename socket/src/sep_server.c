/*
 * IO流分离以及半关闭
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handler(char *msg);

int main(int argc, char **argv) {
  int serv_sockfd, clnt_sockfd;
  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t clnt_addrlen;
  char buf[BUF_SIZE];
  FILE *readfp, *writefp;

  if(argc != 2) {
	printf("usage: %s <port>\n", argv[0]);
	exit(1);
  }

  if((serv_sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
	error_handler("scoket() error");
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));
  if(bind(serv_sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	error_handler("bind() error");
  if(listen(serv_sockfd, 5) == -1)
	error_handler("listen() error");

  clnt_addrlen = sizeof(clnt_addr);
  if((clnt_sockfd = accept(serv_sockfd, (struct sockaddr*)&clnt_addr, &clnt_addrlen)) == -1)
	error_handler("accept() error");
  
  readfp = fdopen(clnt_sockfd, "r");
  writefp = fdopen(dup(clnt_sockfd), "w"); // dup to copy file descriptor
  
  fputs("FROM SERVER: Hi~ client?\n", writefp);
  fputs("I love all of the world\n", writefp);
  fputs("You are awesome!\n", writefp);
  fflush(writefp);
  shutdown(fileno(writefp), SHUT_WR);  // send EOF and half-close
  fclose(writefp);

  fgets(buf, sizeof(buf), readfp);
  fputs(buf, stdout);

  fclose(readfp);
  return 0;
}

void error_handler(char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}
