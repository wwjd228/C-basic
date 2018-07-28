#include "mylib.h"

static _header_t base;
static _header_t *freep = NULL;

static inline _header_t *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    _header_t *up;
    if ( nu < NALLOC )
        nu = NALLOC;
    cp = sbrk(nu * sizeof(_header_t));
    if ( cp == (char *) -1 )
        return NULL;
    up = (_header_t *) cp;
    up ->s.size = nu;
    myfree((void *) (up + 1));
    return freep;
}

void *mycalloc(unsigned n, unsigned size)
{
    unsigned nb = n * size;
    char *p;

    if ( (p = mymalloc(nb)) != NULL ) {
        while ( --nb )
            p[nb] = 0;
    }

    return (void *)p;
}

void *mymalloc(unsigned nbytes)
{
    _header_t *p, *prevp;
    _header_t *morecore(unsigned);
    unsigned nunits;
    nunits = (nbytes + sizeof(_header_t) - 1) / sizeof(_header_t) + 1;
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for ( p = prevp ->s.ptr ; ; prevp = p, p = p ->s.ptr ) {
        if (p ->s.size >= nunits) {
            if ( p ->s.size == nunits ) {
                prevp ->s.ptr = p ->s.ptr;
            }
            else {
                p ->s.size -= nunits;
                p += p ->s.size;
                prevp ->s.size = nunits;
            }

            freep = prevp;
            return (void *)(p + 1);
        }

        if ( p == freep ) {
            if ( (p = morecore(nunits)) == NULL )
                return NULL;
        }
    }
}

void myfree(void *ap)
{
    _header_t *bp, *p;

    bp = (_header_t *)ap - 1;
    for ( p = freep ; !(bp > p && bp < p ->s.ptr) ; p = p->s.ptr )
        if ( p >= p ->s.ptr && (bp > p || bp < p ->s.ptr) )
            break;

    if ( bp + bp ->s.size == p ->s.ptr ) {
        bp ->s.size += p ->s.ptr ->s.size;
        bp ->s.ptr = p ->s.ptr ->s.ptr;
    } else
        bp ->s.ptr = p ->s.ptr;
    if ( p + p ->s.size == bp ) {
        p ->s.size += bp ->s.size;
        p ->s.ptr = bp ->s.ptr;
    } else
        p ->s.ptr = bp;

    freep = p;
}
