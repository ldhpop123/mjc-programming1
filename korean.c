#include <stdio.h>

int main(void) {
    int koreanScore;
    scanf("%d", &koreanScore);

    if (0 <= koreanScore && koreanScore <= 100) {
        printf("올바른 점수입니다.");
    } else {
        printf("잘못된 점수입니다.");
    }

    return 0;
}