#include <iostream>
using namespace std;

int testcase;

int cost[4];    // 이용권 가격 입력 (1일권 / 1달권 / 3달권 / 1년권 )
int plan[13];   // 이용 계획 입력 ( 1월 ~ 12월 )
int now;
int MIN = 21e8;


void dfs(int month, int money) {

    // 1년이 다 되었을 때 종료 하면서 최솟값 구하기
    if (month > 12) {
        if (money < MIN)
            MIN = money;
        return;
    }

    // 이용 계획이 없는 달일경우 다음달로 넘어 간다.
    if (plan[month] == 0) {
        dfs(month + 1, money);
    }
    else { // 이용 계획이 하루라도 있을 때 이용권을 구매하는 경우의 수 세가지
        // 경우 1. 매일 1일 이용권을 구매하는 경우
        now = plan[month] * cost[0];
        dfs(month + 1, money + now);

        // 경우 2. 1달 이용권을 구매하는 경우
        now = cost[1];
        dfs(month + 1, money + now);

    }

    // 경우 3. 3달 이용권을 구매하는 경우
    if (month + 3 <= 12) {  // 3달이 모두 이번 해 안으로 끝난다. -> 최대 10월 11월 12월인 경우 까지
        now = cost[2];
        dfs(month + 3, money + now);
    }
    else if (month + 3 >= 13) { // 남은 달이 내년으로 넘어 가는 경우 -> 11월 12월 1월(13월) / 12월 1월 2월
        now = cost[2];
        dfs(month + 3, money + now);
    }

    // 1년권은 매년 1월에 사는 것이 아니라면 고려해줄 필요 X -> 1월에 이용계획 있을때만 구매해주고 넘어가자
    if (month == 1) {
        now = cost[3];
        dfs(month + 12, money + now);
    }
}

int main(int argc, const char* argv[]) {

    cin >> testcase;
    for (int t = 1; t <= testcase; t++) {

        for (int i = 0; i < 4; i++) {
            cin >> cost[i];
        }
        for (int i = 1; i <= 12; i++) {
            cin >> plan[i];
        }

        MIN = 21e8;
        dfs(1, 0);

        cout << "#" << t << " " << MIN << "\n";
    }

    return 0;
}