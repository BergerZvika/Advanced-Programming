#include <stdio.h>
#include "math_utils.h"

int main(void) {
    printf("=== Step 2: Multiple Source Files ===\n");
    printf("3 + 4     = %d\n",      add(3, 4));
    printf("3 * 4     = %d\n",      multiply(3, 4));
    printf("2 ^ 10    = %.0f\n",    power(2.0, 10));
    printf("5 ^ 3     = %.0f\n",    power(5.0, 3));
    return 0;
}
