#include <stdio.h>


int main() {
    printf("계산기 만들어보기\n 1. 더하기\n 2. 뺴기\n 3. 곱하기\n 4. 나누기\n 번호를 입력해주세요: ");
    int select;
    scanf("%d", &select);
    int x, y;
    printf("첫번쨰 숫자: ");
    scanf("%d", &x);
    printf("두번쨰 숫자: ");
    scanf("%d", &y);
    switch (select)
    {
    case 1:
        printf("결과는 %d + %d = %d", x, y , x+y);
        break;
    case 2:
        printf("결과는 %d - %d = %d", x, y , x-y);
        break;
    case 3:
        printf("결과는 %d * %d = %d", x, y , x*y);
        break;
    case 4:
        printf("결과는 %d / %d = %d", x, y , x/y);
        break;
    
    default:
        printf("선택한 메뉴가 존재하지 않습니다.");
        break;
    }

    return 0;
}
