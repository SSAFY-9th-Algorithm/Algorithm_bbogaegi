//행렬크기로 인해 오류 발생 코드
#include <iostream>
#include <queue>
using namespace std;

int N, M, K, P;
int mat[2000][2000];

void bfs(int start) {
    queue<int>q;
    q.push(start);

    int visited[200000] = { 0, };
    visited[start] = 1;

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        //cout << now << " ";

        for (int next = 0; next <= N; next++) {

            if (mat[now][next] == 0)
                continue;

            if (visited[next] == K+1)
                continue;

            q.push(next);
            
            visited[next] = visited[now] + 1;
        }
    }

    int flag = 1;
    for (int i = 0; i <= N; i++) {
        if (visited[i] - 1 == K) {
            flag = 0;
            cout << i << endl;
        }
    }
    if (flag == 1) cout << -1;

}

int main() {

    cin >> N >> M >> K >> P;

    for (int i = 0; i < M; i++) {
        int from, to;
        cin >> from >> to;

        mat[from][to] = 1;
    }

    bfs(P);

    return 0;
}
