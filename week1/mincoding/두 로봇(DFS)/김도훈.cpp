#include <iostream>
#include <vector> 
using namespace std;

// ������(a)���� ������(b)���� ���� �Ÿ��� cost���� �ִ� cost�� ���� ���� �� �ʿ� ����
// ���� N���϶� ��ΰ� ������ N-1�̰� ��� ����� ���� �ϳ��̹Ƿ� ���� ������ �Ѱ����̴�.


struct Edge {
    int to;
    int cost;
};


vector<Edge>al[100001];
int N;
int a, b;   // �ʱ� ��ġ
int visited[100001];
int sum = 0;
int MIN = 21e8;
int MAX = -21e8;

void dfs(int now) {
    if (now == b) {
        if (sum < MIN)
            MIN = sum - MAX;
        return;
    }

    for (int i = 0; i < al[now].size(); i++) {
        Edge next = al[now][i];
        if (visited[next.to] == 1)
            continue;

       
        sum += next.cost;   // ���� ���� cost�� ��� ���� ��
        if (next.cost > MAX)
            MAX = next.cost;    // ���� ������ �ʿ� ���� cost�� ���� ���� ��
        visited[next.to] = 1;
        dfs(next.to);
        visited[next.to] = 0;
        sum -= next.cost;
    }
}

int main() {
    cin >> N >> a >> b;

    for (int i = 0; i < N - 1; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;

        al[from].push_back({ to, cost });
        al[to].push_back({ from, cost });
    }


    visited[a] = 1;
    dfs(a);
    cout << MIN << endl;
    return 0;
}