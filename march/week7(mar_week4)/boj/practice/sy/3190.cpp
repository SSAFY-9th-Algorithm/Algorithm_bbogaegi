#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;

/*
8
3
5 4
5 8
2 5
6
7 D
11 D
15 D
18 D
19 D
20 D
*/

struct Qry {
    int time;
    char dir;
};

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int leftrotate[] = { 2,3,1,0 };
int rightrotate[] = { 3,2,0,1 };

int N;
int MAP[110][110];
int K, L;
queue<Qry> q;

int simul() {
    int ty = 1, tx = 1, num = 1;
    queue<pair<int, int>> pos;
    int y = 1, x = 1, dir = 3;
    int time = 0, t = 0;
    char d;
    while (1)
    {
        int de = 1;
        time++;
        // 먼저 뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다.
        int ny = y + ydir[dir];
        int nx = x + xdir[dir];
        // 벽 또는 자기자신의 몸과 부딪히면 게임 종료
        if ((ny < 1 || nx < 1 || ny >= N + 1 || nx >= N + 1) || MAP[ny][nx] >= num)
            break;
        // 만약 이동한 칸에 사과가 있다면, 
        if (MAP[ny][nx] == -1)
            // 그 칸에 있던 사과를 먹는다! 
            // 꼬리는 움직이지 않는다.
            MAP[ny][nx] = MAP[y][x] + 1;

        // 만약 이동한 칸에 사과가 없다면, 
        else {
            // 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다.
            // 즉, 몸길이는 변하지 않는다.
            if (MAP[y][x] != 1) {
                MAP[ty][tx] = 0;
                MAP[ny][nx] = MAP[y][x] + 1;
                num++;
                for (int i = 0; i < 4; i++) {
                    int dy = ty + ydir[i];
                    int dx = tx + xdir[i];

                    if (MAP[dy][dx] == num) {
                        ty = dy, tx = dx;
                        break;
                    }
                }
            }
            else {
                MAP[ny][nx] = 1;
                ty = ny, tx = nx;
                MAP[y][x] = 0;
            }
            
        }
        if (!q.empty() && t == 0) {
            t = q.front().time, d = q.front().dir;
            q.pop();
        }
        if (time == t) {
            t = 0;
            if (d == 'L') dir = leftrotate[dir];
            else dir = rightrotate[dir];
        }
        y = ny;
        x = nx;
    }
    return time;
}

int main() {
    fastIO;

    MAP[1][1] = 1;
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int y, x;
        cin >> y >> x;
        MAP[y][x] = -1;
    }
    cin >> L;
    for (int i = 0; i < L; i++) {
        int x;
        char c;
        cin >> x >> c;
        q.push({ x, c });
    }

    int ans = simul();

    cout << ans;
    return 0;
}
