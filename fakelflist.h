#pragma once
#include <list.h>
#include <nalloc.h>
#include <pthread.h>

typedef volatile struct lflist{
    list l;
    pthread_mutex_t mut;
} lflist;
#define LFLIST(self, elem)                      \
    {.l = LIST(&(self)->l, elem),               \
            .mut = PTHREAD_MUTEX_INITIALIZER}

typedef struct{
    uptr gen;
    lflist *host;
}stx;

typedef align(sizeof(dptr)) volatile struct{
    stx;
    lanchor lanc;
} flanchor;
#define FLANCHOR(list)                          \
    {.lanc = LANCHOR(list), .host = list}
#define FLANCHOR_GEN(_gen)                      \
    {.lanc = LANCHOR(NULL), .host = NULL, .gen=_gen}


typedef struct {
    flanchor *a;
    uptr gen;
}flx;

#define pudef (flx, "{%, %}", a->a, a->gen)
#include <pudef.h>
#define pudef (flanchor, "l:%, g:%", a->lanc, a->gen)
#include <pudef.h>
#define pudef (lflist, "list{%}", a->l)
#include <pudef.h>
