/**
 * Write a program that uses UNIX system calls to ''ping-pong'' a byte between two processes
 * over a pair of pipes, one for each direction. The parent should send a byte to the child;
 * the child should print "<pid>: received ping", where <pid> is its process ID, write the 
 * byte on the pipe to the parent, and exit; the parent should read the byte from the child, 
 * print "<pid>: received pong", and exit. Your solution should be in the file user/pingpong.c.
 */

#include "kernel/types.h"
#include "user/user.h"

int
main()
{
    int fds[2];
    char buf = 'T';

    pipe(fds);

    int pid = fork();
    if (pid == 0)
    {
        // inside child
        read(fds[1], (void *)buf, sizeof(buf));
        printf("%d: received ping\n", pid);
        buf = 't';
        write(fds[1], (void *)buf, sizeof(buf));
        exit(0);
    }
    else
    {
        // inside parent
        wait((int*) 0);
        write(fds[0], (void *)buf, sizeof(buf));
        read(fds[0], (void *)buf, sizeof(buf));
        printf("%d: received pong\n", pid);
        exit(0);
    }

    exit(0);
}