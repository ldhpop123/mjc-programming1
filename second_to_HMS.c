#include <stdio.h>

int main() {
    int second, H, M;
    scanf("%d", &second);
    printf("%d초는", second);
    
    H = second/3600; second -= 3600*H;
    M = second/60; second -= 60*M;
    
    printf("%d시간 %d분 %d초 입니다.", H, M,  second);

    return 0;
}