#include <stdio.h>
#include "api.h"

int main(void)
{
    BigNum n1, n2, sum;
    init(&n1);
    init(&n2);
    init(&sum);

    // Any length decimal string directly:
    bignum_from_str(&n1, "13423423432434234234234324543454534534534543434343499999999999999", 10);
    bignum_from_str(&n2, "99999999999999999999999999999999999999999943434343349999999999999", 10);

    bignum_add(&n1, &n2, &sum);
    bignum_add(&sum, &sum, &sum);

    printf("Sum (Decimal): ");
    print_limbs(&sum, 10);

    printf("Sum (Hex):     ");
    print_limbs(&sum, 16);

    bignum_free(&n1);
    bignum_free(&n2);
    bignum_free(&sum);

    return 0;
}
