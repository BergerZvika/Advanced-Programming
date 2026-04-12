#include <stdio.h>
#include <string.h>
#include "string_utils.h"

int main(void) {
    printf("=== Step 3: Headers in Separate Include Directory ===\n\n");

    char word[] = "hello world";
    printf("Original : %s\n", word);
    str_to_upper(word);
    printf("Upper    : %s\n\n", word);

    char rev[] = "CMake is great";
    printf("Before reverse : %s\n", rev);
    str_reverse(rev);
    printf("After reverse  : %s\n\n", rev);

    printf("'l' count in 'hello world' : %d\n",
           str_count_char("hello world", 'l'));
    return 0;
}
