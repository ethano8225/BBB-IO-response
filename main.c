#include <stdio.h>
int main() {
    int var = 10;
    int *ptr = &var;
    *ptr = *ptr +1;
    printf("%p, %d", ptr, var);
    return 0;
}