#include <stdio.h>

#define MAX(a, b) (a > b ? a : b)
#define sqrt(x) (x) * (x)
#define wrong_sqrt(x) x * x
#define str(exp) #exp
#define expcat(exp1, exp2) (exp1 ## exp2)

int main(void)
{
    int i = 7, j = 8, k = 10;
    int min = 0, max = 9;
#ifdef WRONG
    printf("wrong sqrt ");
    printf(str(#define wrong_sqrt(x) x * x));

    // marco must use (), or it will cause wrong result in some cases.
    printf(" wrong_sqrt(7) = %d\n", wrong_sqrt(7));
    printf("wrong argurement sqrt(i++) = %d\n", sqrt(i++));
    printf("wrong argurement MAX(j++, k++) = %d\n", MAX(j++, k++));
#else
    printf("sqrt ");
    printf(str(define sqrt(x) (x * x)));
    printf(" sqrt(7) = %d\n", sqrt(7));
#endif
    printf("sqrt(expcat(m, in), expcat(ma, x)) = %d\n"\
            , MAX(expcat(m, in), expcat(ma, x)));
    return 0;
}
