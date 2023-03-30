#include <iostream>
using namespace std;

int testcase;

int num[12];    // ����� ���� �Է� ( 3 ~ 12 )
int oper[4];   // ������ �Է� ( '+', '-', '*', '/' )
int n;
int now;
int MIN = 21e8;
int MAX = -21e8;

// �����ϴ� �Լ�
int calc(int a, int b, int oper) {

    if (oper == 0) return a + b;
    else if (oper == 1) return a - b;
    else if (oper == 2) return a * b;
    else if (oper == 3) return a / b;

}

void dfs(int sum, int level) {

    // ��� �����ڰ� ����Ǹ� ���� -> �ִ� , �ּ�
    if (level == n - 1) { // n-1: ������ ����
        if (sum < MIN)
            MIN = sum;
        if (sum > MAX)
            MAX = sum;
        return;
    }


    for (int i = 0; i < 4; i++) {

        if (oper[i] > 0) {    // �����ڸ� �տ����� Ȯ�� -> 0�� �ƴϸ� �����ڰ� �����Ѵٰ� ���� ����� �ϵ��� ���� -> ��� �� �� �����ڿ� �ش��ϴ� ���ڴ� -1�����ش�.
            // �׷����ؼ� ������ ������ 0�� �Ǹ� ���� �����ڷ� �Ѿ
            oper[i] -= 1;
            dfs(calc(sum, num[level + 1], i), level + 1);   // i = 0, 1, 2, 3 ---> '+', '-', '*', '/'
            oper[i] += 1; // ���� 

        }
    }
}

int main(int argc, const char* argv[]) {

    cin >> testcase;
    for (int t = 1; t <= testcase; t++) {

        cin >> n;
        // ��� ��, �迭 �ʱ�ȭ
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