#pragma once

#include <stdint.h>
#include <stdbool.h>

#define max_4_ints(T, a, b, c, d) ({ \
    const T _a = ((a) < 0)? -(a) : (a); const T _b = ((b) < 0)? -(b) : (b); \
    const T _c = ((c) < 0)? -(c) : (c); const T _d = ((d) < 0)? -(d) : (d); \
    const T ab = (_a > _b) ? _a : _b; \
    const T cd = (_c > _d) ? _c : _d; \
    (ab > cd) ? ab : cd; })

#define max_8_ints(T, a, b, c, d, e, f, g, h) ({ \
    const T i1 = max_4_ints(T, a, b, c, d); \
    const T i2 = max_4_ints(T, e, f, g, h); \
    (i1 > i2) ? i1 : i2; })

static inline
int64_t max_32_i64(const int64_t* i) {
    return max_4_ints(int64_t,
        max_8_ints(int64_t, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7]),
        max_8_ints(int64_t, i[8], i[9], i[10], i[11], i[12], i[13], i[14], i[15]),
        max_8_ints(int64_t, i[16], i[17], i[18], i[19], i[20], i[21], i[22], i[23]),
        max_8_ints(int64_t, i[24], i[25], i[26], i[27], i[28], i[29], i[30], i[31]));
}

static inline
int32_t max_32_i32(const int32_t* i) {
    return max_4_ints(int32_t,
        max_8_ints(int32_t, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7]),
        max_8_ints(int32_t, i[8], i[9], i[10], i[11], i[12], i[13], i[14], i[15]),
        max_8_ints(int32_t, i[16], i[17], i[18], i[19], i[20], i[21], i[22], i[23]),
        max_8_ints(int32_t, i[24], i[25], i[26], i[27], i[28], i[29], i[30], i[31]));
}

static inline
int16_t max_32_i16(const int16_t* i) {
    return max_4_ints(int16_t,
        max_8_ints(int16_t, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7]),
        max_8_ints(int16_t, i[8], i[9], i[10], i[11], i[12], i[13], i[14], i[15]),
        max_8_ints(int16_t, i[16], i[17], i[18], i[19], i[20], i[21], i[22], i[23]),
        max_8_ints(int16_t, i[24], i[25], i[26], i[27], i[28], i[29], i[30], i[31]));
}

#define max_32_ints(x) \
_Generic( (x), \
    int64_t*: max_32_i64, \
    int32_t*: max_32_i32, \
    int16_t*: max_32_i16 \
)(x)

bool unittest_max_32_ints(void);
bool unittest_max_exp_32_ints(void);