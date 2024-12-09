#pragma once

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