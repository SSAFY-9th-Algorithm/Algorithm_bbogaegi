#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int y, x;
};

int ydir[] = { -1,1,0,0,-1,-1,1,1 };
int xdir[] = { 0,0,-1,1,-1,1,1,-1 };

int N, M;
int MAP[55][55];
vector<Node> shark;

int bfs(int y, int x) {
    queue<Node>q;
    q.push({ y, x });

    int visited[55][55] = { 0, };
    visited[y][x] = 1;

    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 8; i++) {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                continue;
            if (visited[ny][nx])
                continue;

            if (MAP[ny][nx] == 1) {
                return visited[now.y][now.x];
            }

            visited[ny][nx] = visited[now.y][now.x] + 1;
            q.push({ ny, nx });
        }
        //cout << '\n';
        //for (int i = 0; i < N; i++) {
        //    for (int j = 0; j < M; j++)
        //        cout << visited[i][j] << ' ';
        //    cout << '\n';
        //}
    }
    
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < M; j++) 
            cin >> MAP[i][j];
    int res = -21e8;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!MAP[i][j]) {
                int tmp = bfs(i, j);
                if (tmp > res) res = tmp;
            }
        }
    }
    cout << res;
    return 0;
}
