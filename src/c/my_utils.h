/** @file
 * @brief MTIA helpers and utilities.
 *
 * @copyright 2023-2024 Meta Platforms, Inc.
 *
 *
 */
#pragma once

#include "qemu/osdep.h"
#include <stdint.h>

/// Check if a bit is set in an integer.
static inline bool is_bit_set(uint64_t v, uint8_t pos) {
    return (v >> pos) & 1ul;
}

/// Check if a bit is set in an integer.
///
/// @see test_bit in qemu/include/qemu/bitops.h
static inline bool check_bit(uint64_t v, uint8_t pos) {
    return is_bit_set(v, pos);
}

/// Set a bit in an integer.
///
/// @see set_bit in qemu/include/qemu/bitops.h
static inline uint64_t with_set_bit(uint64_t v, uint8_t pos) {
    return v | (1ul << pos);
}

/// Clear a bit in an integer.
///
/// @see clear_bit in qemu/include/qemu/bitops.h
static inline uint64_t with_cleared_bit(uint64_t v, uint8_t pos) {
    return v & ~(1ul << pos);
}

/// Toggle a bit in an integer.
///
/// @see change_bit in qemu/include/qemu/bitops.h
static inline uint64_t with_toggled_bit(uint64_t v, uint8_t pos) {
    return v ^ (1ul << pos);
}

/** Count number of trailing zero bits in an integer.
 *
 */
#define ctz(x) _Generic( (x), \
                   unsigned int: __builtin_ctz, \
                   unsigned long: __builtin_ctzl, \
                   default: __builtin_ctz \
                )(x)

/** Returns one plus the index of the least significant 1-bit of x,
 *  or if x is zero, returns zero.
 *
 */
#define ffs(x) _Generic( (x), \
                   unsigned int: __builtin_ffs, \
                   unsigned long: __builtin_ffsl, \
                   default: __builtin_ffs \
                )(x)

/** For loop over each set bit in an integer.
 *
 * Example:
 * ```
 *   __auto_type b = 0b1011000u;
 *   for_each_bit(b, pos) {
 *       printf("pos=%u bits=%b\n", pos, b);
 *   }
 * ```
 * pos=3 bits=1011000
 * pos=4 bits=1010000
 * pos=6 bits=1000000
 */
#define for_each_bit(bits, pos) \
    for (unsigned int pos = ctz(bits); bits; \
        bits &= bits - 1, pos = ctz(bits))

/** IF-ELSE statement that returns a value.
 *
 * A compound statement enclosed in parentheses may appear as an expression in GNU C.
 *
 * Example:
 * ```
 * int x = 15;
 * enum Size {SMALL, MEDIUM, BIG};
 * enum Size sz = return_if (x < 10) {
 *     SMALL;
 * }
 * return_else_if (x < 20) {
 *     MEDIUM;
 * }
 * return_else {
 *     BIG;
 * }));
 * assert(sz == MEDIUM);
 * ```
 */
#define return_if(cond) (cond) ? (
#define return_else ):(
#define return_else_if(cond) ):( (cond) ? (

/// Repeat string N times.
static inline bool repeat_string(char* buf, size_t buf_len, const char* str,
    const char* delim, size_t times)
{
    size_t str_len = strlen(str), delim_len = strlen(delim);
    size_t required_len = (str_len + delim_len) * times;
    if (buf_len < required_len || times == 0) {
        return false;
    }

    strcpy(buf, str);
    buf_len -= str_len;

    for (size_t i = 1; i < times; i++) {
        strncat(buf, delim, buf_len);
        buf_len -= delim_len;
        strncat(buf, str, buf_len);
        buf_len -= str_len;
    }

    return true;
}
