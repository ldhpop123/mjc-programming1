#include <stdio.h>
#define PRICE 10000

int main(void) {
    int age, discount, fee;
    printf("나이를 입력해주세여 : ");
    scanf("%d", &age);

    if (0 <= age && 65 <= age) {
        discount = (int)(PRICE*0.1);
    } else if (age <= 6) {
        discount = PRICE;
    } else if (age <= 18) {
        discount = (int)(PRICE*0.2);
    } else {
        discount = 0;
    }

    fee = PRICE - discount;
    printf("입장료는 %d원입니다.", fee);

    return 0;
}