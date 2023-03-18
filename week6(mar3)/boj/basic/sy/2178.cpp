#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

using pi = pair<int, int>;

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int N, M;
int MAP[110][110];

int bfs(int y, int x) {
    queue<pi> q;
    q.push({ y, x });

    int visited[110][110] = { 0, };
    visited[y][x] = 1;

    while (!q.empty())
    {
        auto now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.first + ydir[i];
            int nx = now.second + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                continue;
            if (visited[ny][nx])
                continue;
            if (!MAP[ny][nx])
                continue;

            visited[ny][nx] = visited[now.first][now.second] + 1;
            q.push({ ny, nx });
        }
    }
    return visited[N - 1][M - 1];
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            char tmp;
            cin >> tmp;
            MAP[i][j] = tmp - '0';
        }

    int ans = bfs(0, 0);
    cout << ans;
    return 0;
}
