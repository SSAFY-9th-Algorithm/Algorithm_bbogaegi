#include <iostream>
using namespace std;

int testcase;

int cost[4];    // �̿�� ���� �Է� (1�ϱ� / 1�ޱ� / 3�ޱ� / 1��� )
int plan[13];   // �̿� ��ȹ �Է� ( 1�� ~ 12�� )
int now;
int MIN = 21e8;


void dfs(int month, int money) {

    // 1���� �� �Ǿ��� �� ���� �ϸ鼭 �ּڰ� ���ϱ�
    if (month > 12) {
        if (money < MIN)
            MIN = money;
        return;
    }

    // �̿� ��ȹ�� ���� ���ϰ�� �����޷� �Ѿ� ����.
    if (plan[month] == 0) {
        dfs(month + 1, money);
    }
    else { // �̿� ��ȹ�� �Ϸ�� ���� �� �̿���� �����ϴ� ����� �� ������
        // ��� 1. ���� 1�� �̿���� �����ϴ� ���
        now = plan[month] * cost[0];
        dfs(month + 1, money + now);

        // ��� 2. 1�� �̿���� �����ϴ� ���
        now = cost[1];
        dfs(month + 1, money + now);

    }

    // ��� 3. 3�� �̿���� �����ϴ� ���
    if (month + 3 <= 12) {  // 3���� ��� �̹� �� ������ ������. -> �ִ� 10�� 11�� 12���� ��� ����
        now = cost[2];
        dfs(month + 3, money + now);
    }
    else if (month + 3 >= 13) { // ���� ���� �������� �Ѿ� ���� ��� -> 11�� 12�� 1��(13��) / 12�� 1�� 2��
        now = cost[2];
        dfs(month + 3, money + now);
    }

    // 1����� �ų� 1���� ��� ���� �ƴ϶�� ������� �ʿ� X -> 1���� �̿��ȹ �������� �������ְ� �Ѿ��
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