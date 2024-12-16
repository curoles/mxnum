#include "capi.h"
#include "bitops.h"
#include "mx_int8.h"

int capi_unittest_bitops(void) {
    return unittest_all_bitops();
}

int capi_unittest_max_32_ints(void) {
    return unittest_max_32_ints()
        && unittest_max_exp_32_ints();
}
