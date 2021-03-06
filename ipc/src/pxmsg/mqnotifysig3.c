#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mqueue.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#define error_handler(msg) \
  do {\
    printf("%s:%d %s, %s\n", __FILE__, __LINE__, #msg, strerror(errno)); \
	exit(1); \
  } while(0)

volatile sig_atomic_t mqflag;
static void sig_usr1(int);

int main(int argc, char **argv) {
  mqd_t mqd;
  void *buf;
  ssize_t n;
  sigset_t zeromask, newmask, oldmask;
  struct mq_attr attr;
  struct sigevent sigev;

  if(argc != 2) {
	printf("usage: %s <mqname>\n", argv[0]);
	exit(1);
  }
  if((mqd = mq_open(argv[1], O_RDONLY | O_NONBLOCK)) == -1)
	error_handler(mq_open() error);
  mq_getattr(mqd, &attr);
  if((buf = malloc(attr.mq_msgsize)) == NULL)
	error_handler(malloc() error);
  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigemptyset(&oldmask);
  sigaddset(&newmask, SIGUSR1);

  signal(SIGUSR1, sig_usr1);
  sigev.sigev_notify = SIGEV_SIGNAL;
  sigev.sigev_signo = SIGUSR1;
  mq_notify(mqd, &sigev);

  int i;
  for(i = 0; i < 3; ++i) {
	sigprocmask(SIG_BLOCK, &newmask, &oldmask); /* block SIGUSR1 signal */ 
	while(mqflag == 0)
	  sigsuspend(&zeromask);  /* pause, waiting for the previosly blocked SIGUSR1 signal to occur*/
	mqflag = 0; /* reset flag */

	mq_notify(mqd, &sigev); /* reregister first */
    while((n = mq_receive(mqd, buf, attr.mq_msgsize, NULL)) >= 0)
	  printf("read %ld bytes\n", (long)n);
	if(errno != EAGAIN) {
	  free(buf);
	  error_handler(mq_receive error);
	}
	sigprocmask(SIG_UNBLOCK, &newmask, NULL);
  }
  free(buf);
  return 0;
}

static void sig_usr1(int signo) {
  mqflag = 1;
  return;
}
