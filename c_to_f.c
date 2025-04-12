#include <stdio.h>

int main() {
    int C;
    double F;
    scanf("%d", &C);
    F = (9*C)/5.0 + 32;
    printf("%lf", F);
    return 0;
}