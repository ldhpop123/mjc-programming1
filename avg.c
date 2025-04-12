#include <stdio.h>

int main() {
    int math, korean, english;
    scanf("%d %d %d", &math, &korean, &english);
    printf("%lf", (math+korean+english)/3.0);
    return 0;
}