#include "api.h"
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

int parser(const char *string_of_numbers, uint64_t *out_number)
{
    char *endptr = NULL;
    errno = 0;

    unsigned long long val = strtoull(string_of_numbers, &endptr, 0);

    if (endptr == string_of_numbers || *endptr != '\0')
    {
        fprintf(stderr, "Error: Invalid number format '%s'\n", string_of_numbers);
        return 1;
    }

    if (errno == ERANGE)
    {
        fprintf(stderr, "Error: Number '%s' exceeds 64-bit capacity\n", string_of_numbers);
        return 1;
    }

    *out_number = (uint64_t)val;
    return 0;
}

BigNum *init(BigNum *ptr_to_big_integer_struct)
{
    ptr_to_big_integer_struct->capacity = INTIALCAPACITY;
    uint64_t *ptr_to_heap = malloc((ptr_to_big_integer_struct->capacity) * sizeof(uint64_t));
    if (ptr_to_heap == NULL)
    {
        return NULL;
    }
    ptr_to_big_integer_struct->size = 0;
    ptr_to_big_integer_struct->limbarray = ptr_to_heap;
    return ptr_to_big_integer_struct;
}

/* Unified printing function for any base from 2 to 36 */
void print_limbs(const BigNum *ptr_to_big_integer_struct, uint32_t base)
{
    if (base < 2 || base > 36)
    {
        fprintf(stderr, "Error: Base must be between 2 and 36\n");
        return;
    }

    uint64_t size = ptr_to_big_integer_struct->size;
    uint64_t *ptr_to_heap = ptr_to_big_integer_struct->limbarray;

    if (!size)
    {
        printf(base == 16 ? "0x0\n" : "0\n");
        return;
    }

    /* Fast path for native hex */
    if (base == 16)
    {
        printf("0x");
        for (int64_t i = (int64_t)size - 1; i >= 0; i--)
        {
            printf("%016lx", ptr_to_heap[i]);
        }
        printf("\n");
        return;
    }

    /* Radix division for non-power-of-two bases (e.g., base 10) */
    BigNum copy;
    init(&copy);
    for (uint64_t i = 0; i < size; i++)
    {
        bignum_append_u64(&copy, ptr_to_heap[i]);
    }

    size_t max_digits = (size * 64) + 64;
    char *digits = malloc(max_digits);
    if (!digits)
    {
        bignum_free(&copy);
        return;
    }

    const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    size_t digit_count = 0;

    while (copy.size > 0)
    {
        __uint128_t rem = 0;
        for (int64_t i = (int64_t)copy.size - 1; i >= 0; i--)
        {
            __uint128_t cur = (rem << 64) | copy.limbarray[i];
            copy.limbarray[i] = (uint64_t)(cur / base);
            rem = cur % base;
        }

        digits[digit_count++] = charset[rem];

        while (copy.size > 0 && copy.limbarray[copy.size - 1] == 0)
        {
            copy.size--;
        }
    }

    for (int64_t i = (int64_t)digit_count - 1; i >= 0; i--)
    {
        putchar(digits[i]);
    }
    putchar('\n');

    free(digits);
    bignum_free(&copy);
}

void bignum_set_u64(BigNum *ptr_to_big_integer_struct, uint64_t value)
{
    if (value == 0)
    {
        ptr_to_big_integer_struct->size = 0;
        return;
    }
    ptr_to_big_integer_struct->limbarray[0] = value;
    ptr_to_big_integer_struct->size = 1;
}

void bignum_free(BigNum *ptr_to_big_integer_struct)
{
    if ((ptr_to_big_integer_struct->limbarray) == NULL)
        return;
    free(ptr_to_big_integer_struct->limbarray);
    ptr_to_big_integer_struct->size = 0;
    ptr_to_big_integer_struct->limbarray = NULL;
}

void bignum_append_u64(BigNum *ptr_to_big_integer_struct, uint64_t value)
{
    if ((ptr_to_big_integer_struct->size) >= ((ptr_to_big_integer_struct->capacity)))
    {
        uint64_t temp_capacity = ptr_to_big_integer_struct->capacity * 2;
        uint64_t *temp_ptr = realloc(ptr_to_big_integer_struct->limbarray, temp_capacity * (sizeof(uint64_t)));
        if (!temp_ptr)
            return;

        ptr_to_big_integer_struct->limbarray = temp_ptr;
        ptr_to_big_integer_struct->capacity = temp_capacity;
    }
    ptr_to_big_integer_struct->limbarray[(ptr_to_big_integer_struct->size)++] = value;
}

void bignum_append_str(BigNum *ptr_to_big_integer_struct, const char *str_value)
{
    uint64_t val;
    if (parser(str_value, &val) == 0)
    {
        bignum_append_u64(ptr_to_big_integer_struct, val);
    }
}

/* Ingests an arbitrarily long numeric string in any base (2 to 36, or 0/16 for hex) */
int bignum_from_str(BigNum *b, const char *str, uint32_t base)
{
    if (!b || !str) return 1;

    /* Skip leading whitespace */
    while (isspace((unsigned char)*str)) str++;

    /* Auto-detect hex prefix */
    if ((base == 0 || base == 16) && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        str += 2;
        base = 16;
    }
    if (base == 0) base = 10;

    if (base < 2 || base > 36) return 1;

    /* Reset BigNum to 0 */
    b->size = 0;

    /* FAST-PATH: Direct 16-character slicing for base 16 */
    if (base == 16)
    {
        int len = (int)strlen(str);
        if (len == 0) return 0;

        char chunk[17];
        int end = len;
        while (end > 0)
        {
            int start = end - 16;
            if (start < 0) start = 0;
            int chunk_len = end - start;

            memcpy(chunk, str + start, chunk_len);
            chunk[chunk_len] = '\0';

            char *endptr = NULL;
            errno = 0;
            unsigned long long val = strtoull(chunk, &endptr, 16);
            if (endptr == chunk || *endptr != '\0' || errno == ERANGE)
            {
                b->size = 0;
                return 1;
            }

            bignum_append_u64(b, (uint64_t)val);
            end = start;
        }

        /* Drop trailing zero limbs */
        while (b->size > 0 && b->limbarray[b->size - 1] == 0)
        {
            b->size--;
        }
        return 0;
    }

    /* GENERAL RADIX: Horner's method (b = b * base + digit) */
    while (*str)
    {
        char c = *str++;
        uint32_t digit;
        if (c >= '0' && c <= '9') digit = c - '0';
        else if (c >= 'a' && c <= 'z') digit = c - 'a' + 10;
        else if (c >= 'A' && c <= 'Z') digit = c - 'A' + 10;
        else return 1; /* Invalid character */

        if (digit >= base) return 1;

        __uint128_t carry = digit;
        for (uint64_t i = 0; i < b->size; i++)
        {
            __uint128_t prod = ((__uint128_t)b->limbarray[i] * base) + carry;
            b->limbarray[i] = (uint64_t)prod;
            carry = prod >> 64;
        }
        if (carry > 0)
        {
            bignum_append_u64(b, (uint64_t)carry);
        }
    }

    return 0;
}

void bignum_add(const BigNum *b1, const BigNum *b2, BigNum *result)
{
    BigNum temp_result;
    init(&temp_result);
    uint64_t largest_size = b1->size;
    if (b2->size > b1->size)
    {
        largest_size = b2->size;
    }
    uint64_t carryover = 0;
    for (uint64_t i = 0; i < largest_size; i++)
    {
        uint64_t temp1 = 0, temp2 = 0;
        if (i < b1->size)
        {
            temp1 = b1->limbarray[i];
        }
        if (i < b2->size)
        {
            temp2 = b2->limbarray[i];
        }
        uint64_t sum = temp1 + temp2 + carryover;
        bignum_append_u64(&temp_result, sum);
        carryover = (sum < temp1) || (carryover && sum == temp1);
    }
    if (carryover)
    {
        bignum_append_u64(&temp_result, 1);
    }
    bignum_free(result);
    *result = temp_result;
}

int bignum_cmp(const BigNum *b1, const BigNum *b2)
{
    if (b1->size > b2->size)
    {
        return 1;
    }
    if (b2->size > b1->size)
    {
        return -1;
    }
    uint64_t size = b1->size;
    for (int64_t i = (int64_t)size - 1; i >= 0; i--)
    {
        if (b1->limbarray[i] > b2->limbarray[i])
        {
            return 1;
        }
        else if (b2->limbarray[i] > b1->limbarray[i])
        {
            return -1;
        }
    }
    return 0;
}
