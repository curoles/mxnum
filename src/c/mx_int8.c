#include "mx_int8.h"
#include <assert.h>
#include "bitops.h"

bool unittest_max_32_ints(void)
{
    int16_t max = max_4_ints(int16_t, 1, 100, -120, -1234);
    assert(max == 1234);

    int16_t i[32] = {1, -1, 45, 123, -8145, 77, 4500, 6700, 967, -333,
        -11111, 4, -444, 553, -789, 0, -4, -555};
    max = max_32_ints(i);
    assert(max == 11111);
    return max == 11111;
}

bool unittest_max_exp_32_ints(void)
{
    assert(clrsb((int32_t)0) == 31);
    assert(clrsb((int32_t)(1<<10)) == 20);
    assert(clrsb(-(int32_t)(1<<10)) == 21);
    uint8_t mexp = max_exp_4_ints(int32_t, (1<<10), (1<<2), (1<<3), (1<<8));
    assert(mexp == 11);
    mexp = max_exp_4_ints(int32_t, (1<<10), -(1<<2), -(1<<11), (1<<8));
    assert(mexp == 12);
    mexp = max_exp_4_ints(int16_t, (1<<10), -(1<<2), -(1<<13), (1<<8));
    assert(mexp == 14);
 
    return true;
}
