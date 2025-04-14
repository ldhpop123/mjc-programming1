#include <stdio.h>

int main() {
    int target;
    scanf("%d", &target);

    if (target < 0) {
        target = -target;
    }

    printf("%d", target);
    return 0;
}