#include <stdio.h>

int main() {
    int num, abs;
    scanf("%d", &num);

    abs = num;
    if (num < 0) {
        abs = -num;
    }

    printf("%d", abs);
    return 0;
}