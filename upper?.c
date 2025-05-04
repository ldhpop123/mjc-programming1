#include <stdio.h>

int main(void) {
    char alpha;
    printf("알파벳 하나를 입력해주세요 : ");
    scanf("%c", &alpha);

    if ('A' <= alpha && alpha <= 'Z') {
        printf("대문자 입니다.");
    } else if ('a' <= alpha && alpha <= 'z') {
        printf("소문자 입니다.");
    } else { 
        printf("알파벳이 아닙니다."); 
    }

    return 0;
}