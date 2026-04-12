#include <stdio.h>
#include "vector.h"

int main(void) {
    printf("=== Step 4: Static & Shared Libraries ===\n\n");

    Vec3 a = {1.0, 2.0, 3.0};
    Vec3 b = {4.0, 5.0, 6.0};

    printf("a      = "); vec3_print(a);
    printf("b      = "); vec3_print(b);
    printf("a + b  = "); vec3_print(vec3_add(a, b));
    printf("a * 2  = "); vec3_print(vec3_scale(a, 2.0));
    printf("dot(a,b) = %.2f\n",   vec3_dot(a, b));
    printf("|a|      = %.4f\n",   vec3_length(a));
    return 0;
}
