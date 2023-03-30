#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

// 실수한 부분
// 1. NxM인데 NxN인줄 알고 범위 확인할때 N이라 써서 예제 테케 틀림
// 2. visited 만들때 무슨 정신인지 크기를 20x20 으로 만들어서 예제 테케 틀림
// 3. isConnected 함수 만들때 현재 내 위치의 방향을 보는거라 갈 수 있는 타입은 
//    반대 방향인데 같은 방향으로 해서 예제 테케 틀림
// 

// 설계
// bfs로 시작 위치부터 갈 수 있는 칸을 한칸씩 탐색하며 카운트
// 전체 q가 빌때 까지가 아닌 탈출 시간만큼만 반복 탐색
// 한번에 갈 수 있는 칸씩 봐야하기 때문에 -> 바이러스 처럼
// q.size만큼만 반복문을 돌리며
// 현재 터널에서 갈 수 있는 방향을 모두 탐색
// 갈 수 있으면 q에 담고 위 작업 반복

struct Node {
    int y;
    int x;
};

int N, M; // 세로, 가로
int MAP[55][55];
int sy, sx; // 시작 위치
int L; // 탈출 소요 시간
int ans;

// 상 우 하 좌
int ydir[] = { -1,0,1,0 };
int xdir[] = { 0,1,0,-1 };

// 각 터널 type 별 갈 수 있는 방향
vector<int> type_dir[8] = {
    {},
    {0,1,2,3},
    {0,2},
    {1,3},
    {0,1},
    {1,2},
    {2,3},
    {0,3}
};

// 초기화
void INIT() {
    memset(MAP, 0, sizeof(MAP));
    ans = 0;
}

// 입력
void input() {
    cin >> N >> M >> sy >> sx >> L;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> MAP[i][j];
}

// 현재 위치의 방향과 다음 갈 터널의 타입을 확인하여 갈 수있으면 return true
bool isConnected(int type, int dir) {
    if (dir == 0)
        return type == 1 || type == 2 || type == 5 || type == 6;
    else if(dir == 1)
        return type == 1 || type == 3 || type == 6 || type == 7;
    else if(dir == 2)
        return type == 1 || type == 2 || type == 4 || type == 7;
    else {
        return type == 1 || type == 3 || type == 4 || type == 5;
    }

}

void bfs(int y, int x) {
    queue<Node>q;
    q.push({ y, x });

    int visited[55][55] = { 0, };
    visited[y][x] = 1;

    // 탈출에 소요된 시간 만큼만 탐색
    for (int ti = 0; ti < L; ti++) {
        int cursize = q.size();
        // 현재 q 크기만큼만 탐색
        for (int i = 0; i < cursize; i++) {
            ans++; 

            Node now = q.front();
            q.pop();

            // 현재 내 터널에서 갈 수 있는 방향만큼 반복 탐색
            for (int dir : type_dir[MAP[now.y][now.x]]) {
                int ny = now.y + ydir[dir];
                int nx = now.x + xdir[dir];

                // 범위 확인
                if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                    continue;

                // 방문 확인
                if (visited[ny][nx] == 1)
                    continue;

                // 터널이 아니면 통과
                if (MAP[ny][nx] == 0)
                    continue;

                // 갈 수 없는 터널이면 통과
                if (!isConnected(MAP[ny][nx], dir))
                    continue;

                visited[ny][nx] = 1;
                q.push({ ny, nx });
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        // reset
        INIT();
        // input
        input();
        // solve
        bfs(sy, sx);
        // output
        cout << '#' << tc << ' ' << ans << '\n';
    }

    return 0;
}
