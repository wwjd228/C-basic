int filecopy(FILE *fout, FILE *fin)
{
    char c;
    while ((c = getc(fin)) != EOF)
        putc(c, fout);
    return ferror(fout) ? EOF : 0;
}


