#include <stdio.h>

// 소득
#define HOURLY_PAY 12000 // 시급
#define EXTRA_PAY_PER_MIN 100 // 초과된 분만큼 급여

// 세율 범위
#define TAX_CUT_LOW 30000 // 세율 low 범위 지정
#define TAX_CUT_HIGH 70000 // 세율 high 범위 지정

// 범위에 따른 세율
#define TAX_RATE_LOW 0.05 // low 일떄 세율
#define TAX_RATE_MID 0.10 // mid 일때 세율
#define TAX_RATE_HIGH 0.15 // high 일떄 세율

// 환급
#define FAMILY_REFUND 2000 // 가족당 환급금
#define CARD_REFUND_LIMIT 0.3 // 카드 사용액이 소득의 ?초과시 환급가능
#define CREDIT_CARD_RATE 0.1 // 신용카드로 초과시 신용카드 사용액의 ?환급
#define CHECK_CARD_RATE 0.2 // 체크카드로 초과시 산용카드 사용액의 ?환급

int main(void) {
    // 입력변수
    int employee_num, age, working_sec, family; // 사원번호, 나이, 근무시간, 가족
    char department; // 부서코드
    int credit_card, check_card; // 신용카드 채크카드

    // 중간변수
    int leftsec; //분값 계산을 위한 left sec
    int base_hour = 0;

    // 출력변수
    int working_H, working_M, working_S; // 근무시간(시간) 근무시간(분) 
    int working_over, working_overH, working_overM, working_overS; // 초과근무시간(시간) (분)
    double income_amount = 0, tax = 0, after_tax = 0, refund = 0; // 소득액, 세금, 세후, 환급금
    char department_string[20] = {0};

    // 입력
    printf("사원번호를 입력해주세요 (두 자리 정수) : ");
    scanf("%d", &employee_num);
    printf("나이를 입력해주세요 : ");
    scanf("%d", &age);
    printf("부서코드를 입력해주세요 : ");
    scanf(" %c", &department);
    printf("근무시간 (초 단위 입력) : ");
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
        printf("고용불가입니다.");
        return 1; // 프로그램 종료
    }

    // =======================
    // 부서코드 처리 영역
    // =======================
    if (department == 'a' || department == 'A') {
        department_string[0] = '인';
        department_string[1] = '사';
        department_string[2] = '\0';
    } else if (department == 'b' || department == 'B') {
        department_string[0] = '재';
        department_string[1] = '무';
        department_string[2] = '\0';
    } else if (department == 'c' || department == 'C') {
        department_string[0] = '영';
        department_string[1] = '업';
        department_string[2] = '\0';
    } else if (department == 'd' || department == 'D') {
        department_string[0] = '마';
        department_string[1] = '케';
        department_string[2] = '팅';
        department_string[3] = '\0';
    } else if (department == 'e' || department == 'E') {
        department_string[0] = '연';
        department_string[1] = '구';
        department_string[2] = '개';
        department_string[3] = '발';
        department_string[4] = '\0';
    } else {
        // 해당 부서가 없을 때
        printf("해당 부서가 존재하지 않습니다.");
        return 1; // 프로그램 종료
    }

    // 근무시간 (올림 처리)
    if (working_sec > 0) {
        working_H = working_sec / 3600;
        leftsec = working_sec % 3600;
        working_M = leftsec / 60;
        working_S = leftsec % 60;
    }

    if (working_sec > 3600 * base_hour) {
        // 최대근무 시간 만큼 계산
        working_over = working_sec - 3600 * base_hour;
        income_amount = HOURLY_PAY * base_hour;

        // 초과 근무시간 계산
        working_overH = working_over / 3600;
        leftsec = working_over % 3600;
        working_overM = leftsec / 60;
        working_overS = leftsec % 60;

        // 초과 근무시간 분급(올림처리) 
        income_amount += EXTRA_PAY_PER_MIN * working_overM;
        if (working_overS) {
            income_amount += EXTRA_PAY_PER_MIN;
        }
    } else { 
        // 촤대 근무시간 보다 같거나 적다면
        income_amount = ((double)working_sec / 3600) * HOURLY_PAY;
    }

    // 소득액에 따른 세율
    if (TAX_CUT_HIGH <= income_amount) {
        tax = income_amount * TAX_RATE_HIGH;
    } else if (TAX_CUT_LOW  <= income_amount) {
        tax = income_amount * TAX_RATE_MID;
    } else if (0 <= income_amount) {
        tax = income_amount * TAX_RATE_LOW;
    }
    
    // 환급금
    refund += family * FAMILY_REFUND;
    if (credit_card > income_amount * CARD_REFUND_LIMIT) {
        refund += credit_card * CREDIT_CARD_RATE;
    }
    if (check_card > income_amount * CARD_REFUND_LIMIT) {
        refund += credit_card * CHECK_CARD_RATE;
    }
    // 세후 급여액
    after_tax = income_amount - tax + refund;

    // 출력
    printf("\n%d번 사원 급여정보입니다.\n", employee_num);
    printf("%d시간 %d분 %d초 근무자로 %d시간 %d분 %d초를 초과한 %s부서 직원입니다.\n", 
        working_H, working_M, working_S, working_overH, working_overM, working_overS, department_string);
    printf("세전 급여액은 %.1f원, 세금은 %.1f원, 환급금은 %.1f원이므로 세후 급여액은 %.1f원입니다.\n",
        income_amount, tax, refund, after_tax);

    return 0;
}