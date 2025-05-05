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
#define CHECK_CARD_RATE 0.2 // 체크카드로 초과시 체크카드 사용액의 ?환급

int main(void) {
    // 입력변수
    int employee_num, age, working_sec, family; // 사원번호, 나이, 근무시간, 가족
    char department; // 부서코드
    int credit_card, check_card; // 신용카드 채크카드

    // 중간변수
    int leftsec; //분값 계산을 위한 left sec
    int base_hour = 0; // 최대 인정 근무시간을 저장
    int overtime_min; // 초과 근무 분(올림)
    double card_limit; // 카드 환급을 위한 소득액 초과제한 저장

    // 출력변수
    int working_H, working_M, working_S; // 근무시간(시간) (분) (초) 
    int working_over, working_overH, working_overM, working_overS; // 초과근무시간(시간) (분) (초)

    double income_amount = 0, tax = 0, after_tax = 0, refund = 0; // 소득액, 세금, 세후, 환급금

    // 입력 + 유효성 검사
    printf("사원번호를 입력해주세요 (두 자리 정수) : ");
    scanf("%d", &employee_num);
    printf("나이를 입력해주세요 : ");
    scanf("%d", &age);
    if (age < 18) { // 18세 미만이라면 고용 불가
        printf("고용불가입니다.\n");
        return 1; // 프로그램 종료
    }

    printf("부서코드를 입력해주세요 (알파벳 대문자 한 글자) : ");
    scanf(" %c", &department); // 버퍼 처리를 위해 한칸 띄어쓰기
    // =======================
    // 부서코드 유효성 검사
    // =======================
    if (! ('A' <= department && department <= 'E')) {
        // 해당 부서가 없을 때
        printf("해당 부서가 존재하지 않습니다.\n");
        return 1; // 프로그램 종료
    }

    printf("근무시간 (초 단위 입력) : ");
    scanf("%d", &working_sec);
    if (working_sec <= 0) {
        // 근무시간이 0과 같거나 작다면
        printf("근무를 하지않았거나 음수 입니다.\n");
        return 1; // 프로그램 종료
    }

    printf("부양 가족수를 입력해주세요 : ");
    scanf("%d", &family);
    printf("신용카드 사용액을 입력해주세요 : ");
    scanf("%d", &credit_card);
    printf("체크카드 사용액을 입력해줴요 : ");
    scanf("%d", &check_card);

    // - processing - 

    // 근무시간
    working_H = working_sec / 3600;
    leftsec = working_sec % 3600;
    working_M = leftsec / 60;
    working_S = leftsec % 60;

    // 최대인정 근무시간 (base_hour에 저장)
    if (65 <= age) {
        base_hour = 3;
    } else if (55 <= age) {
        base_hour = 5;
    } else if (25 <= age) {
        base_hour = 9;
    } else if (18 <= age) {
        base_hour = 7;
    }

    if (working_sec > 3600 * base_hour) { // 최대 인정근무 시간보다 근무시간이 많다면
        // 최대근무 시간 만큼 계산
        working_over = working_sec - 3600 * base_hour;
        income_amount = HOURLY_PAY * base_hour;

        // 초과 근무시간 계산
        working_overH = working_over / 3600;
        leftsec = working_over % 3600;
        working_overM = leftsec / 60;
        working_overS = leftsec % 60;

        // 초과 근무시간 분급(올림처리)
        overtime_min = (working_over + 59) / 60; 
        income_amount += EXTRA_PAY_PER_MIN * overtime_min;

    } else {  // 촤대 근무시간 보다 같거나 적다면
        income_amount = ((double)working_sec / 3600) * HOURLY_PAY;
        // income의 자료형은 double이고 캐스트연산자를 사용하여 실수 계산
    }

    // 소득액에 따른 세율
    if (TAX_CUT_HIGH <= income_amount) { // 세율 벙위에 맞는 세율 게산
        tax = income_amount * TAX_RATE_HIGH;
    } else if (TAX_CUT_LOW  <= income_amount) {
        tax = income_amount * TAX_RATE_MID;
    } else {
        tax = income_amount * TAX_RATE_LOW;
    }
    
    // 환급금
    if (family > 0) { // 부양 가족수가 음수 또는 0이 아니라면
        refund += family * FAMILY_REFUND;
    }
    // 카드 사용액에 제한을 걸고 초과한다면 카드 종류에 따라 환급율 적용
    card_limit = income_amount * CARD_REFUND_LIMIT;
    if (credit_card > card_limit) { // 신용카드
        refund += credit_card * CREDIT_CARD_RATE;
    }
    if (check_card > card_limit) { // 체크카드
        refund += check_card * CHECK_CARD_RATE;
    }
    
    // 세후 급여액
    after_tax = income_amount - tax + refund;

    // 출력
    printf("\n%d번 사원 급여정보입니다.\n", employee_num);
    printf("%d시간 %d분 %d초 근무자로 %d시간 %d분 %d초를 초과한", 
        working_H, working_M, working_S, working_overH, working_overM, working_overS);
    // =======================
    // 부서코드 처리 영역 (할 수 없이 if문으로 부서코드 처리)
    // =======================
    if (department == 'A'){
        printf(" 인사부 ");
    } else if (department == 'B') {
        printf(" 제무부 ");
    } else if (department == 'C') {
        printf(" 영업부 ");
    } else if (department == 'D') {
        printf(" 마케팅부 ");
    } else if (department == 'E') {
        printf(" 연구 및 개발부 ");
    }
    printf("직원입니다.\n세전 급여액은 %.1f원, 세금은 %.1f원, 환급금은 %.1f원이므로 세후 급여액은 %.1f원입니다.\n",
        income_amount, tax, refund, after_tax);

    return 0;
}