#include <stdio.h>

int main(void) {
    int num;
    printf("하나의 정수를 입력해주세요 : ");
    scanf("%d", &num);

    if (num != 0) {
        printf("%d는 %s입니다.", num, 0 < num ? "양수" : "음수");
    } else {
        printf("%d는 0입니다.");
    }

    return 0;
}