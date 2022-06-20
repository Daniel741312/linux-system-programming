#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

int main(int argc, char* argv[]) {
	//创建子进程，关闭父进程
	pid_t pid = fork();
	if (pid != 0) {
		exit(0);
	}
	//创建新会话
	int ret = setsid();
	//切换工作目录，防止当前目录被卸载
	chdir("/home/daniel");
	umask(0022);
	close(STDIN_FILENO);  //关闭标准输入
	int fd = open("/dev/null", O_RDWR);
	if (fd < 0) {
		perr_exit("open error");
	}
	//将标准输出和标准错误重定向到/dev/null
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	while (1)
		;
	return 0;
}