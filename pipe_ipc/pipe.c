#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t r_cpid = 0, w_cpid = 0;
    char buf;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(-1);
    }

    if (-1 == pipe(pipefd)) {
        perror("pipe");
        exit(-1);
    }

    r_cpid = fork();
    if (r_cpid != 0) {
        /* r child does NOT fork */
        w_cpid = fork();
    }
    if ((-1 == w_cpid) || (-1 == r_cpid)) {
        perror("fork");
        exit(-1);
    } else if (0 == r_cpid) { /* Child reads from pipe */
        close(pipefd[1]); /* close unused write end */
        waitpid(w_cpid, NULL, 0);
        while (read(pipefd[0], &buf, 1) > 0) {
            write(STDOUT_FILENO, &buf, 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        exit(0);
    } else if (0 == w_cpid) { /* Chile write to pipe */
        close(pipefd[0]); /* Close unused read end */
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);
        exit(0);
    } else {
        pid_t cpid = wait(NULL);
        if (-1 == cpid) {
            perror("wait");
            exit(-1);
        }
    }

    return 0;
}
