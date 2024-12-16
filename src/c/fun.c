#include <assert.h>
#include "fun.h"
#include "bitops.h"

int fun(int a)
{
    char m1[32]={}, m2[32];
    __builtin_memcpy(m2, m1, sizeof(m1));
    assert(sizeof(m1) == 32);

    return a + 1;
}

