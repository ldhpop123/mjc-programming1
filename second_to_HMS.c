#include <stdio.h>

int main() {
    int second; // 입력변수 
    int leftsec; // 중간변수 (intermediate variable)
    int H, M, S; // 출력변수
    scanf("%d", &second);
    
    H = second/3600;
    leftsec = second%3600;
    M = leftsec/60;
    S = leftsec%60;
    
    printf("%d초는 %d시간 %d분 %d초 입니다.", second, H, M, S);

    return 0;
}