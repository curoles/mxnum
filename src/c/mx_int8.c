#include "mx_int8.h"
#include <assert.h>

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
    return true;
}
