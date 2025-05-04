#include <stdio.h>
#define HOURLY_PAY 12000

int main(void) {
    // 입력변수
    int employee_num, age, working_sec, family; // 사원번호, 나이, 근무시간, 가족
    char department; // 부서코드
    int credit_card, check_card; // 신용카드 채크카드

    // 중간변수
    int leftsec; //분값 계산을 위한 left sec
    int base_hour;

    // 출력변수
    int working_H, working_M, working_S; // 근무시간(시간) 근무시간(분) 
    int working_over, working_overH, working_overM, working_overS; // 초과근무시간(시간) (분)
    double income_amount, tax, after_tax, refund = 0; // 소득액, 세금, 세후, 환급금
    char department_string[50];

    // 입력
    printf("사원번호를 입력해주세요 (두 자리 정수) : ");
    scanf("%d", &employee_num);
    printf("나이를 입력해주세요 : ");
    scanf("%d", &age);
    printf("부서코드를 입력해주세요 : ");
    scanf(" %c", &department);
    printf("근무시간 (초 단위 입력)");
    scanf("%d", &working_sec);
    printf("부양 가족수를 입력해주세요 : ");
    scanf("%d", &family);
    printf("신용카드 사용액을 입력해주세요 : ");
    scanf("%d", &credit_card);
    printf("체크카드 사용액을 입력해줴요 : ");
    scanf("%d", &check_card);

    // - processing - 

    // 최대인정 근무시간 
    if (65 <= age) {
        base_hour = 3;
    } else if (55 <= age) {
        base_hour = 5;
    } else if (25 <= age) {
        base_hour = 9;
    } else if (18 <= age) {
        base_hour = 7;
    } else if (0 <= age) {
        base_hour = 0;
        // 고용 불가
    }

    // 고용불가가 아니라면
    if (base_hour) {
        // 근무시간 (올림 처리)
        if (working_sec > 0 && base_hour) {
            working_H = working_sec / 3600;
            leftsec = working_sec % 3600;
            working_M = leftsec / 60;
            working_S = leftsec % 60;
        }

        if (working_sec > 3600 * base_hour) {
            working_over = (working_sec - 3600) * base_hour;
            income_amount = HOURLY_PAY * base_hour;
            if (working_sec) {
                working_overH = working_over / 3600;
                leftsec = working_over % 3600;
                working_overM = leftsec / 60;
                working_overS = leftsec % 60;
                income_amount += 100 * working_overM;
                if (working_overS) {
                    income_amount += 100;
                }
            }
        } else {
            income_amount = ((float)working_sec / 3600) * HOURLY_PAY;
        }

        // 소득액에 따른 세율
        if (70000 <= income_amount) {
            tax = income_amount * 0.15;
        } else if (30000 <= income_amount) {
            tax = income_amount * 0.1;
        } else if (0 <= income_amount) {
            tax = income_amount * 0.05;
        }
        
        // 환급금
        refund += family * 2000;
        if (credit_card > income_amount * 0.3) {
            refund += credit_card * 0.1;
        }
        if (check_card > income_amount * 0.3) {
            refund += credit_card * 0.2;
        }
        after_tax = income_amount - tax + refund;

        //부서코드
        if (department == 'a' || department == 'A') {
            char department_string[] = "인사";
        } else if (department == 'b' || department == 'B') {
            char department_string[] = "재무";
        } else if (department == 'c' || department == 'C') {
            char department_string[] = "영업";
        } else if (department == 'd' || department == 'D') {
            char department_string[] = "마케팅";
        } else if (department == 'e' || department == 'E') {
            char department_string[] = "연구개발";
        }

        // 출력
        printf("\n%d번 사원 급여정보입니다.\n", employee_num);
        printf("%d시간 %d분 %d초 근무자로 %d시간 %d분 %d초를 초과한 %s부서 직원입니다.\n", 
            working_H, working_M, working_S, working_overH, working_overM, working_overS, department_string);
        printf("세전 급여액은 %.1f원, 세금은 %.1f원, 환급금은 %.1f원이므로 세후 급여액은 %.1f원입니다.\n",
            income_amount, tax, refund, after_tax);
    } else {
        printf("고용불가");
    }
    


    return 0;
}