#include <stdio.h>
#include "filecopy.h"

int main(int argc, char **argv)
{
    FILE *fp;
    char *prog = argv[0];

    if (argc == 1)
        filecopy(stdout, stdin);
    else {
        while (--argc > 0) {
            if ((fp = fopen(argv[argc], "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, argv[argc]);
                return EOF;
            }

            else {
                filecopy(stdout, fp);
                fclose(fp);
           }
        }
    }

    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        return EOF;
    }

    return 0;
}
