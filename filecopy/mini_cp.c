#include <stdio.h>
#include "filecopy.h"

int main(int argc, char **argv)
{
    FILE *destfp, *srcfp;
    char *prog = argv[0];

    if (argc < 3) {
        fprintf(stderr, "%s: Missing file operand\n", prog);
        return EOF;
    }
    else if (argc == 3) {
        if ((srcfp = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, argv[1]);
            return EOF;
        }
        if ((destfp = fopen(argv[2], "w")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, argv[2]);
            return EOF;
        }
        else {
            filecopy(destfp, srcfp);
            fclose(srcfp);
            fclose(destfp);
        }
    }

    else
        puts("Not support multi file yet!");

    return 0;
}
