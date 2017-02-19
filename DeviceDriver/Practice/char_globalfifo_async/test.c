#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>

#define FIFO_CLEAR 0x1
#define BUFFER_LEN 20

/*接收到异步读信号后的动作*/
void input_handler(int signum)
{
	printf("receive a signal from globalfifo,signalnum:%d\n",signum);
}

int main()
{
	int fd, oflags;
	fd = open("/dev/globalfifo", O_RDWR, S_IRUSR | S_IWUSR);
	if (fd != - 1) {
		//启动信号驱动机制
		signal(SIGIO, input_handler); //让 input_handler()处理 SIGIO 信号
		fcntl(fd, F_SETOWN, getpid()); //指定一个进程与文件进行关联。这样内核才知道向哪个进程发消息。
		oflags = fcntl(fd, F_GETFL); // get the flag
		fcntl(fd, F_SETFL, oflags | FASYNC); //设置文件ｆｌａｇ，设置文件ＦＡＳＹＮＣ标志，使能异步通知。这样内核就能依据该文件，发出信号了
		while(1) {
			sleep(100);
		}
	} else {
		printf("device open failure\n");
	}
}
