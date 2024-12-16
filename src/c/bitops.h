#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

static inline uint8_t bitsizeof_u64(uint64_t v) {
    return sizeof(v) * 8;
}

static inline uint8_t bitsizeof_u32(uint32_t v) {
    return sizeof(v) * 8;
}

static inline uint8_t bitsizeof_u16(uint16_t v) {
    return sizeof(v) * 8;
}

static inline uint8_t bitsizeof_u8(uint8_t v) {
    return sizeof(v) * 8;
}

#define bitsizeof(x) \
_Generic( (x), \
    uint64_t: bitsizeof_u64, \
    uint32_t: bitsizeof_u32, \
    uint16_t: bitsizeof_u16, \
    uint8_t: bitsizeof_u8 \
)(x)

static inline bool bitop_u64_check_set(uint64_t v, uint8_t pos) {
    return (v >> pos) & 1ul;
}

static inline bool bitop_u32_check_set(uint32_t v, uint8_t pos) {
    return (v >> pos) & 1u;
}

static inline bool bitop_u16_check_set(uint16_t v, uint8_t pos) {
    return (v >> pos) & 1u;
}

static inline bool bitop_u8_check_set(uint8_t v, uint8_t pos) {
    return (v >> pos) & 1u;
}

static inline bool bitop_ptr_u64_check_set(uint64_t* addr, uint8_t pos) {
    uint64_t* p = addr + (pos / bitsizeof(*addr));
    return (*p >> (pos % bitsizeof(*addr))) & 1ul;
}

static inline bool bitop_ptr_u8_check_set(uint8_t* addr, uint8_t pos) {
    uint8_t* p = addr + (pos / bitsizeof(*addr));
    return (*p >> (pos % bitsizeof(*addr))) & 1u;
}

#define bitop_check_set(x, pos) \
_Generic( (x), \
    uint64_t*: bitop_ptr_u64_check_set, \
    uint8_t*: bitop_ptr_u8_check_set, \
    uint64_t: bitop_u64_check_set, \
    uint32_t: bitop_u32_check_set, \
    uint16_t: bitop_u16_check_set, \
    uint8_t: bitop_u8_check_set, \
    default: bitop_u64_check_set \
)(x, pos)

static inline bool unittest_bitop_check_set(void)
{
    uint64_t u64 = 1ul << 30;
    assert(bitop_check_set(u64, 30));
    assert(!bitop_check_set(u64, 29));
    assert(bitop_check_set(&u64, 30));

    uint16_t u16 = 1u << 12;
    assert(bitop_check_set(u16, 12));
    assert(!bitop_check_set(u16, 1));
    
    uint8_t u8x8[8] = {1,1,0,0, 0,0,0,8};
    assert(bitop_check_set(u8x8, 0));
    assert(bitop_check_set(u8x8, 8));
    assert(bitop_check_set(u8x8, 56+3));

    return true;    
}

__attribute__((warn_unused_result))
static inline uint64_t bitop_u64_set_bit(uint64_t v, uint8_t pos) {
    return v | (1ul << pos);
}

__attribute__((warn_unused_result))
static inline uint32_t bitop_u32_set_bit(uint32_t v, uint8_t pos) {
    return v | (1u << pos);
}

__attribute__((warn_unused_result))
static inline uint16_t bitop_u16_set_bit(uint16_t v, uint8_t pos) {
    return v | (1u << pos);
}

__attribute__((warn_unused_result))
static inline uint8_t bitop_u8_set_bit(uint8_t v, uint8_t pos) {
    return v | (1u << pos);
}

static inline uint64_t bitop_ptr_u64_set_bit(uint64_t* addr, uint8_t pos)
{
    uint64_t* p = addr + (pos / bitsizeof(*addr));
    *p |= bitop_u64_set_bit(0, pos);
    return *p;
}

static inline uint8_t bitop_ptr_u8_set_bit(uint8_t* addr, uint8_t pos)
{
    uint8_t* p = addr + (pos / bitsizeof(*addr));
    *p |= bitop_u8_set_bit(0, pos);
    return *p;
}

#define bitop_set_bit(x, pos) \
_Generic( (x), \
    uint64_t*: bitop_ptr_u64_set_bit, \
    uint8_t*: bitop_ptr_u8_set_bit, \
    uint64_t: bitop_u64_set_bit, \
    uint32_t: bitop_u32_set_bit, \
    uint16_t: bitop_u16_set_bit, \
    uint8_t: bitop_u8_set_bit, \
    default: bitop_u64_set_bit \
)(x, pos)

static inline bool unittest_bitop_set_bit(void)
{
    uint64_t u64 = bitop_set_bit((uint64_t)0, 30);
    assert(bitop_check_set(u64, 30));
    bitop_set_bit(&u64, 15);
    assert(bitop_check_set(&u64, 15));

    uint16_t u16 = 3;
    u16 = bitop_set_bit(u16, 12);
    assert(bitop_check_set(u16, 12));
    assert(bitop_check_set(u16, 1));

    return true;    
}

__attribute__((warn_unused_result))
static inline uint64_t bitop_u64_clear_bit(uint64_t v, uint8_t pos) {
    return v & ~bitop_u64_set_bit(0, pos);
}

__attribute__((warn_unused_result))
static inline uint32_t bitop_u32_clear_bit(uint32_t v, uint8_t pos) {
    return v & ~bitop_u32_set_bit(0, pos);
}

__attribute__((warn_unused_result))
static inline uint16_t bitop_u16_clear_bit(uint16_t v, uint8_t pos) {
    return v & ~bitop_u16_set_bit(0, pos);
}

__attribute__((warn_unused_result))
static inline uint8_t bitop_u8_clear_bit(uint8_t v, uint8_t pos) {
    return v & ~bitop_u8_set_bit(0, pos);
}

static inline uint64_t bitop_ptr_u64_clear_bit(uint64_t* addr, uint8_t pos)
{
    uint64_t* p = addr + (pos / bitsizeof(*addr));
    *p &= ~bitop_u64_set_bit(0, pos);
    return *p;
}

static inline uint8_t bitop_ptr_u8_clear_bit(uint8_t* addr, uint8_t pos)
{
    uint8_t* p = addr + (pos / bitsizeof(*addr));
    *p &= ~bitop_u8_set_bit(0, pos);
    return *p;
}

#define bitop_clear_bit(x, pos) \
_Generic( (x), \
    uint64_t*: bitop_ptr_u64_clear_bit, \
    uint8_t*: bitop_ptr_u8_clear_bit, \
    uint64_t: bitop_u64_clear_bit, \
    uint32_t: bitop_u32_clear_bit, \
    uint16_t: bitop_u16_clear_bit, \
    uint8_t: bitop_u8_clear_bit, \
    default: bitop_u64_clear_bit \
)(x, pos)

static inline bool unittest_bitop_clear_bit(void)
{
    uint64_t u64 = ~0ul;
    assert(bitop_check_set(u64, 15));
    u64 = bitop_clear_bit(u64, 15);
    assert(!bitop_check_set(u64, 15));
    bitop_clear_bit(&u64, 14);
    assert(!bitop_check_set(u64, 14));

    uint16_t u16 = 3;
    u16 = bitop_clear_bit(u16, 0);
    assert(bitop_check_set(u16, 1));
    assert(!bitop_check_set(u16, 0));

    return true;    
}

__attribute__((warn_unused_result))
static inline uint64_t bitop_u64_toggle_bit(uint64_t v, uint8_t pos) {
    return v ^ bitop_u64_set_bit(0, pos);
}

__attribute__((warn_unused_result))
static inline uint32_t bitop_u32_toggle_bit(uint32_t v, uint8_t pos) {
    return v ^ bitop_u32_set_bit(0, pos);
}

__attribute__((warn_unused_result))
static inline uint16_t bitop_u16_toggle_bit(uint16_t v, uint8_t pos) {
    return v ^ bitop_u16_set_bit(0, pos);
}

__attribute__((warn_unused_result))
static inline uint8_t bitop_u8_toggle_bit(uint8_t v, uint8_t pos) {
    return v ^ bitop_u8_set_bit(0, pos);
}

static inline uint64_t bitop_ptr_u64_toggle_bit(uint64_t* addr, uint8_t pos)
{
    uint64_t* p = addr + (pos / bitsizeof(*addr));
    *p ^= bitop_u64_set_bit(0, pos);
    return *p;
}

static inline uint32_t bitop_ptr_u32_toggle_bit(uint32_t* addr, uint8_t pos)
{
    uint32_t* p = addr + (pos / bitsizeof(*addr));
    *p ^= bitop_u32_set_bit(0, pos);
    return *p;
}

static inline uint16_t bitop_ptr_u16_toggle_bit(uint16_t* addr, uint8_t pos)
{
    uint16_t* p = addr + (pos / bitsizeof(*addr));
    *p ^= bitop_u16_set_bit(0, pos);
    return *p;
}

static inline uint8_t bitop_ptr_u8_toggle_bit(uint8_t* addr, uint8_t pos)
{
    uint8_t* p = addr + (pos / bitsizeof(*addr));
    *p ^= bitop_u8_set_bit(0, pos);
    return *p;
}

#define bitop_toggle_bit(x, pos) \
_Generic( (x), \
    uint64_t*: bitop_ptr_u64_toggle_bit, \
    uint32_t*: bitop_ptr_u32_toggle_bit, \
    uint16_t*: bitop_ptr_u16_toggle_bit, \
    uint8_t*: bitop_ptr_u8_toggle_bit, \
    uint64_t: bitop_u64_toggle_bit, \
    uint32_t: bitop_u32_toggle_bit, \
    uint16_t: bitop_u16_toggle_bit, \
    uint8_t: bitop_u8_toggle_bit, \
    default: bitop_u64_toggle_bit \
)(x, pos)

static inline bool unittest_bitop_toggle_bit(void)
{
    uint64_t u64 = ~0ul;
    assert(bitop_check_set(u64, 15));
    u64 = bitop_toggle_bit(u64, 15);
    assert(!bitop_check_set(u64, 15));
    bitop_toggle_bit(&u64, 14);
    assert(!bitop_check_set(u64, 14));

    uint16_t u16 = 3;
    u16 = bitop_toggle_bit(u16, 0);
    assert(bitop_check_set(u16, 1));
    bitop_toggle_bit(&u16, 10);
    assert(bitop_check_set(u16, 10));

    return true;    
}

__attribute__((warn_unused_result))
static inline uint64_t bitop_u64_set_bits(uint64_t v, uint64_t mask) {
    return v | mask;
}

__attribute__((warn_unused_result))
static inline uint32_t bitop_u32_set_bits(uint32_t v, uint32_t mask) {
    return v | mask;
}

__attribute__((warn_unused_result))
static inline uint16_t bitop_u16_set_bits(uint16_t v, uint16_t mask) {
    return v | mask;
}

__attribute__((warn_unused_result))
static inline uint8_t bitop_u8_set_bits(uint8_t v, uint8_t mask) {
    return v | mask;
}

__attribute__((warn_unused_result))
static inline uint64_t bitop_u64_clear_bits(uint64_t v, uint64_t mask) {
    return v & ~mask;
}

__attribute__((warn_unused_result))
static inline uint64_t bitop_u64_toggle_bits(uint64_t v, uint64_t mask) {
    return v ^ mask;
}

/** Count number of trailing zero bits in an integer.
 *
 */
#define ctz(x) \
_Generic( (x), \
    unsigned int: __builtin_ctz, \
    unsigned long: __builtin_ctzl, \
    default: __builtin_ctz \
)(x)

static inline bool unittest_ctz(void)
{
    uint64_t u64 = 3ul << 30;
    assert(ctz(u64) == 30);

    uint16_t u16 = 3u << 12;
    assert(ctz(u16) == 12);

    return true;    
}

/** Returns one plus the index of the least significant 1-bit of x,
 *  or if x is zero, returns zero.
 *
 */
#define ffs(x) \
_Generic( (x), \
    unsigned int: __builtin_ffs, \
    unsigned long: __builtin_ffsl, \
    default: __builtin_ffs \
)(x)

static inline bool unittest_ffs(void)
{
    uint64_t u64 = 3ul << 30;
    assert(ffs(u64) == 30+1);

    uint16_t u16 = 3u << 12;
    assert(ffs(u16) == 12+1);

    return true;    
}

static inline int clrsb16(int16_t i) {
    return __builtin_clrsb((int32_t)i) - 16;
}

#define clrsb(x) \
_Generic( (x), \
    int16_t: clrsb16, \
    int: __builtin_clrsb, \
    long: __builtin_clrsbl, \
    default: __builtin_clrsb \
)(x)

#define popcount(x) \
_Generic( (x), \
    unsigned int: __builtin_popcount, \
    unsigned long: __builtin_popcountl, \
    default: __builtin_popcountl \
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
    for (unsigned int __attribute__((unused)) pos = ctz(bits); bits; \
        bits &= bits - 1, pos = ctz(bits))

static inline bool unittest_for_each_bit(void)
{
    __auto_type b = 0b1011000u; typeof(b) cb = b;
    uint8_t count = 0;
    for_each_bit(b, pos) {
        count++;
    }
    assert(count == popcount(cb));
    return true;
}

static inline bool unittest_all_bitops(void)
{    
    assert(unittest_bitop_check_set());
    assert(unittest_bitop_set_bit());
    assert(unittest_bitop_clear_bit());
    assert(unittest_bitop_toggle_bit());
    assert(unittest_ctz());
    assert(unittest_ffs());
    assert(unittest_for_each_bit());

    return true;
}