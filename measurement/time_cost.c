#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>

#define ITERATIONS 1000000

int main(void)
{
    struct timeval tval_start = { 0 }, tval_end = { 0 };
    char buf[4] = { 0 };
    double total_s = 0;
    double total_time = 0;
    double cost = 0.0;
    char str[20] = { 0 };
    int fd = 0;
    int pipefd1[2], pipefd2[2];
    cpu_set_t set;

    if (gettimeofday(&tval_start, NULL)) {
        perror("gettimeofday() failed\n");
        exit(-1);
    }
    for (int i = 0; i < ITERATIONS; i++) {
        read(STDIN_FILENO, buf, 0U);
    }
    if (gettimeofday(&tval_end, NULL)) {
        perror("gettimeofday() failed\n");
        exit(-1);
    }

    printf("Calculating system call time cost:\n");
    printf("start time s = %ld, us = %ld\n", tval_start.tv_sec, tval_start.tv_usec);
    printf("end time s = %ld, us = %ld\n", tval_end.tv_sec, tval_end.tv_usec);

    total_s = (double)tval_end.tv_sec + ((double)tval_end.tv_usec / 1000000);
    total_s =
        total_s - ((double)tval_start.tv_sec + ((double)tval_start.tv_usec / 1000000));
    total_time = total_s * 1000000;
    cost = (double)total_time / (double)ITERATIONS;
    printf("total time = %lf (us)\n", total_time);
    printf("system call cost = %lf (us)\n\n", cost);

    fd = open("cost.txt", O_WRONLY);
    if (fd == -1) {
        perror("open failed.\n");
        exit(1);
    }
    sprintf(str, "%lf\n", cost);
    write(fd, str, strlen(str));

    printf("Calculating context switch time:\n");
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    if ((-1 == pipe(pipefd1)) || (-1 == pipe(pipefd2))) {
        perror("pipe");
        exit(-1);
    }
    if (0 == fork()) {
        char buf_p1 = '\0';

        if (0 != sched_setaffinity(getpid(), sizeof(set), &set)) {
            perror("sched_getaffinity failed!\n");
            exit(-1);
        }
        close(pipefd1[1]); /* close pipe1 unused write end */
        close(pipefd2[0]); /* Close pipe2 unused read end */

        if (gettimeofday(&tval_start, NULL)) {
            perror("gettimeofday() failed\n");
            exit(-1);
        }
        for (int i = 0; i < ITERATIONS; i++) {
            /* read() will block until data is available. */
            read(pipefd1[0], &buf_p1, 1);
            write(pipefd2[1], "1", 1);
        }

        if (gettimeofday(&tval_end, NULL)) {
            perror("gettimeofday() failed\n");
            exit(-1);
        }

        printf("start time s = %ld, us = %ld\n", tval_start.tv_sec, tval_start.tv_usec);
        printf("end time s = %ld, us = %ld\n", tval_end.tv_sec, tval_end.tv_usec);

        total_s = (double)tval_end.tv_sec + ((double)tval_end.tv_usec / 1000000);
        total_s =
            total_s - ((double)tval_start.tv_sec + ((double)tval_start.tv_usec / 1000000));
        total_time = total_s * 1000000;
        cost = (double)total_time / (double)ITERATIONS;
        printf("total time = %lf (us)\n", total_time);
        printf("context cost = %lf (us)\n", cost / 2.0); /* 1 -> 2 -> 1 switch twice */

        sprintf(str, "%lf", (cost / 2.0));
        write(fd, str, strlen(str));
        close(pipefd1[0]);
        close(pipefd2[1]);
        exit(0);
    } else if (0 == fork()) {
        char buf_p2 = '\0';

        if (0 != sched_setaffinity(getpid(), sizeof(set), &set)) {
            perror("sched_getaffinity failed!\n");
            exit(-1);
        }
        close(pipefd1[0]); /* Close pipe1 unused read end */
        close(pipefd2[1]); /* Close pipe2 unused write end */
        for (int i = 0; i < ITERATIONS; i++) {
            write(pipefd1[1], "2", 1);
            /* read() will block until data is available. */
            read(pipefd2[0], &buf_p2, 1);
        }
        close(pipefd1[1]);
        close(pipefd2[0]);
        exit(0);
    } else {
        pid_t cpid = wait(NULL);
        if (-1 == cpid) {
            perror("wait");
            exit(-1);
        }
    }

    close(fd);
    return 0;
}
