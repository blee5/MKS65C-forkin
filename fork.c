#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int pid;
    printf("Forking twice!\n");
    pid = fork();
    if (pid < 0)
    {
        printf("Error %d: %s\n", errno, strerror(errno));
    }
    if (pid)
    {
        pid = fork();
    }

    if (pid)
    {
        int status;
        int child_pid = wait(&status);
        printf("My child just died: its PID was %d and it slept for %d seconds.\n", child_pid, WEXITSTATUS(status));
        return 0;
    }
    else
    {
        int fd = open("/dev/urandom", O_RDONLY);
        if (fd < 0)
        {
            printf("Error %d: %s\n", errno, strerror(errno));
        }
        unsigned char n;
        if (read(fd, &n, sizeof(char)) < 0)
        {
            printf("Error %d: %s\n", errno, strerror(errno));
        }
        n = n % 15 + 5;
        printf("Hello, my PID is %d and I will be sleeping for %d seconds!\n", getpid(), n);
        sleep(n);
        printf("My PID is %d and I'm done sleeping, now I'm going to kill myself.\n", getpid());
        return n;
    }

}
