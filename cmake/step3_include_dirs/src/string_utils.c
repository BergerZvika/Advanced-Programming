#include "string_utils.h"
#include <string.h>
#include <ctype.h>

void str_reverse(char *s) {
    int n = (int)strlen(s);
    for (int i = 0; i < n / 2; i++) {
        char tmp       = s[i];
        s[i]           = s[n - 1 - i];
        s[n - 1 - i]   = tmp;
    }
}

int str_count_char(const char *s, char c) {
    int count = 0;
    while (*s)
        if (*s++ == c) count++;
    return count;
}

void str_to_upper(char *s) {
    while (*s) {
        *s = (char)toupper((unsigned char)*s);
        s++;
    }
}
