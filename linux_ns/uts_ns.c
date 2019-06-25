#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
UTS: Unix Time sharing
In short, the UTS namespace is about isolating hostnames.
The UTS namespace is used to isolate two specific elements of the system that relate to the uname system call. 
The UTS(UNIX Time Sharing) namespace is named after the data structure used to store information returned by 
the uname system call. Specifically, the UTS namespace isolates the hostname and the NIS domain name. NIS, 
an abbreviation of Network Information Service, is an outdated directory service.

*/ 

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); } while (0)

// 调用 clone 时执行的函数
static int childFunc(void *arg)
{
    struct utsname uts;
    char *shellname;
    // 在子进程的 UTS namespace 中设置 hostname
    if (sethostname(arg, strlen(arg)) == -1)
        errExit("sethostname");

    // 显示子进程的 hostname
    if (uname(&uts) == -1)
        errExit("uname");
    printf("uts.nodename in child:  %s\n", uts.nodename);
    printf("My PID is: %d\n", getpid());
    printf("My parent PID is: %d\n", getppid());
    // 获取系统的默认 shell
    shellname = getenv("SHELL");
    if(!shellname){
        shellname = (char *)"/bin/sh";
    }
    // 在子进程中执行 shell
    execlp(shellname, shellname, (char *)NULL);

    return 0;
}
// 设置子进程的堆栈大小为 1M
#define STACK_SIZE (1024 * 1024)

int main(int argc, char *argv[])
{
    char *stack;
    char *stackTop;        
    pid_t pid;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <child-hostname>\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    // 为子进程分配堆栈空间,大小为 1M
    stack = malloc(STACK_SIZE);
    if (stack == NULL)
        errExit("malloc");
    stackTop = stack + STACK_SIZE;  /* Assume stack grows downward */

    // 通过 clone 函数创建子进程
    // CLONE_NEWUTS 标识指明为新进程创建新的 UTS namespace
    pid = clone(childFunc, stackTop, CLONE_NEWUTS | SIGCHLD, argv[1]);
    if (pid == -1)
        errExit("clone");

    // 等待子进程退出
    if (waitpid(pid, NULL, 0) == -1)
        errExit("waitpid");
    printf("child has terminated\n");

    exit(EXIT_SUCCESS);
}