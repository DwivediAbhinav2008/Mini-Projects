#ifndef API_H
#define API_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define INTIALCAPACITY 4096

typedef struct {
    uint64_t *limbarray;
    uint64_t size;
    uint64_t capacity;
} BigNum;

/* Core lifecycle & memory management */
BigNum *init(BigNum *ptr_to_big_integer_struct);
void bignum_free(BigNum *ptr_to_big_integer_struct);

/* Limb manipulation & initializers */
void bignum_set_u64(BigNum *ptr_to_big_integer_struct, uint64_t value);
void bignum_append_u64(BigNum *ptr_to_big_integer_struct, uint64_t value);
void bignum_append_str(BigNum *ptr_to_big_integer_struct, const char *str_value);

/* Arbitrary-length string parser (base 2 to 36; pass 16 or 0 for hex) */
int bignum_from_str(BigNum *b, const char *str, uint32_t base);

/* Unified display (base 2 to 36; pass 16 for hex, 10 for decimal) */
void print_limbs(const BigNum *ptr_to_big_integer_struct, uint32_t base);

/* Arithmetic & Comparison */
void bignum_add(const BigNum *b1, const BigNum *b2, BigNum *result);
int bignum_cmp(const BigNum *b1, const BigNum *b2);

/* Helpers */
int parser(const char *string_of_numbers, uint64_t *out_number);

#endif /* API_H */
