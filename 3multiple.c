#include <stdio.h>

int main(void) {
    int target;
    printf("하나의 정수를 입력해 주세요 : ");
    scanf("%d", &target);

    if (target % 3) {
        printf("%d는 3의 배수가 아닙니다.", target);
    } else {
        printf("%d는 3의 배수가 맞습니다.", target);
    }

    // printf("%d은 3의 배수가 %s", target, target % 3 == 0 ? "맞습니다" : "아닙니다");

    return 0;
}