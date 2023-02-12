#include <iostream>
#include <vector> 
using namespace std;

// 시작점(a)에서 목적지(b)까지 가는 거리의 cost에서 최대 cost의 길은 굳이 갈 필요 없다
// 방이 N개일때 통로가 무조건 N-1이고 방과 방사이 길이 하나이므로 길은 무조건 한가지이다.


struct Edge {
    int to;
    int cost;
};


vector<Edge>al[100001];
int N;
int a, b;   // 초기 위치
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

       
        sum += next.cost;   // 가는 길의 cost를 모두 더한 값
        if (next.cost > MAX)
            MAX = next.cost;    // 굳이 지나갈 필요 없는 cost가 가장 높은 값
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