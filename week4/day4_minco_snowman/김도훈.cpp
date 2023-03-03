#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// bfs(Flood Fill) 이용하여 풀었음
// K(Limit)를 1에서부터 키워가면서 보는데 조건을 만족하면 그 순간 K가 답이다 

// 설계 흐름
// #1. 맨앞의 열에서 맨 아래부터 위로 보면서 1을 발견하면 그 위치에서 K만큼 위의 좌표도 1인지 확인한다.
//      -> 1이면 그 사이 값들을 -1로 채워준다. (나중에 -1은 밟고 갈 수 있음을 의미)

// #2. 그렇게 전부 확인해주고 맵을 재완성한다.

// #3. 그 맵을 기반으로 눈사람에서 출발해서 보석까지 갈 수 있는지 확인한다
//      -> Flood Fill로 맵에서 현재 위치 이웃한 좌표값이 1이거나 -1이면 갈 수 있다
//      -> 최종적으로 보석의 좌표값이 1이되면 1보석까지 갈 수 있음을 확일할 수 있다
//      -> 이 때 좌우로 움직일 때 1은 1으로만, -1은 -1로만 움직일 수 있다
//          (-1은 실제로 맵에서는 땅이 아니기 때문)

struct Node {
    int y;
    int x;
};

int N, M;
int MAP[51][51];
int sy, sx, ey, ex; // (sy, sx) 눈사람위치, (ey, ex) 보석 위치
int K = 1;
int tmp[51][51];

void bfs(int y, int x) {
    queue<Node>q;
    q.push({ y, x });
    int visited[51][51] = { 0, };
    visited[y][x] = 1;

    int dy[4] = { -1, 1, 0, 0 };
    int dx[4] = { 0, 0, -1, 1 };

    while (!q.empty()) {
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                continue;
            if (visited[ny][nx] != 0)
                continue;
            if (MAP[ny][nx] == 0)
                continue;
            // 좌우로 움직일때는 현재 값과 다음값이 같을때만 움직일 수 있음
            if (i == 2 && (MAP[ny][nx] != MAP[now.y][now.x]))
                continue;
            if (i == 3 && (MAP[ny][nx] != MAP[now.y][now.x]))
                continue;

            visited[ny][nx] =  1;
            q.push({ ny,nx });
        }
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            tmp[i][j] = visited[i][j]; // tmp에 저장
        }
    }


}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == 2) {
                sy = i; // 눈사람 좌표 저장
                sx = j;
            }
            if (MAP[i][j] == 3) {
                ey = i; //보석 좌표 저장
                ex = j;
            }
        }
    }
 
    while (1) {
        for (int i = 0; i < M; i++) {
            for (int j = N - 1; j >= 0; j--) {
                if (MAP[j][i] == 2 || MAP[j][i] == 3)
                    MAP[j][i] = 1;  // bfs돌릴때 편하게 하기 위해 눈사람과 보석도 1로 바꿔준다
                if (MAP[j][i] == 1) {
                    if ((j - K) < 0) continue;
                    if (MAP[j - K][i] == 1) { // 이 부분이 1을 발견하면 그 위로 K만큼 떨어진 위치에도 1인지 확인하는 부분
                        // 1과 1사이를 -1로 바꿔서 점프해서 갈 수 있다는 것을 표시
                        for (int a = j - 1; a > j - K; a--)
                            MAP[a][i] = -1;
                    }
                }
            }
        }

        bfs(sy, sx);

        if (tmp[ey][ex] == 1) {
            cout << K << endl;
            break;
        }
        K++;
    }


}
