#include <iostream>
using namespace std;

int testcase;

int num[12];    // 계산할 숫자 입력 ( 3 ~ 12 )
int oper[4];   // 연산자 입력 ( '+', '-', '*', '/' )
int n;
int now;
int MIN = 21e8;
int MAX = -21e8;

// 연산하는 함수
int calc(int a, int b, int oper) {

    if (oper == 0) return a + b;
    else if (oper == 1) return a - b;
    else if (oper == 2) return a * b;
    else if (oper == 3) return a / b;

}

void dfs(int sum, int level) {

    // 모든 연산자가 수행되면 종료 -> 최대 , 최소
    if (level == n - 1) { // n-1: 연산자 개수
        if (sum < MIN)
            MIN = sum;
        if (sum > MAX)
            MAX = sum;
        return;
    }


    for (int i = 0; i < 4; i++) {

        if (oper[i] > 0) {    // 연산자를 앞에부터 확인 -> 0이 아니면 연산자가 존재한다고 보고 계산을 하도록 설계 -> 계산 후 그 연산자에 해당하는 숫자는 -1시켜준다.
            // 그렇게해서 연산자 개수가 0이 되면 다음 연산자로 넘어감
            oper[i] -= 1;
            dfs(calc(sum, num[level + 1], i), level + 1);   // i = 0, 1, 2, 3 ---> '+', '-', '*', '/'
            oper[i] += 1; // 복구 

        }
    }
}

int main(int argc, const char* argv[]) {

    cin >> testcase;
    for (int t = 1; t <= testcase; t++) {

        cin >> n;
        // 모든 값, 배열 초기화
        MIN = 21e8;
        MAX = -21e8;
        for (int i = 0; i < 4; i++) {
            oper[i] = { 0 };
        }
        for (int i = 0; i < n; i++) {
            num[i] = { 0 };
        }


        for (int i = 0; i < 4; i++) {
            cin >> oper[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> num[i];
        }


        dfs(num[0], 0);

        cout << "#" << t << " " << MAX - MIN << "\n";
    }

    return 0;
}