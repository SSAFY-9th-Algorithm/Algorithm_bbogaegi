#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <bits/stdc++.h>
using namespace std;

struct Player {
    int y, x, dir, stat;
    int gun, point;
  
    bool operator<(const Player& next) const {
        if (stat + gun != next.stat + next.gun) 
            return stat + gun < next.stat + next.gun;
        return stat < next.stat;
    }
};

int ydir[] = { -1,0,1,0 };
int xdir[] = { 0,1,0,-1 };

int N, M, K;
Player p[35];
priority_queue<int> MAP[21][21];

void input() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int n;
            cin >> n;
            if(n) MAP[i][j].push(n);
        }
    }
    for (int i = 1; i <= M; i++) {
        cin >> p[i].y >> p[i].x >> p[i].dir >> p[i].stat;
    }
}

void move(int i) {
    // i 번 사람 이동
    int d = p[i].dir;
    int ny = p[i].y + ydir[d];
    int nx = p[i].x + xdir[d];
    // 범위를 벗어나면 방향을 반대로 바꿔서 한칸 전진!
    if (nx < 1 || ny < 1 || nx > N || ny > N) {
        d ^= 2;
        p[i].dir ^= 2;

        ny = p[i].y + ydir[d];
        nx = p[i].x + xdir[d];
    }
    p[i].x = nx, p[i].y = ny;
}
int findPlayer(int y, int x, int i) {
    // y, x에 다른 플레이어가 있는지 찾는다
    for (int j = 1; j <= M; j++) {
        // 본인이면 continue
        if (i == j) continue;
        if (x == p[j].x && y == p[j].y) {
            return j;
        }
    }
    return 0;
}
void getWeapon(int i) {
    int x = p[i].x, y = p[i].y;
    if(!MAP[y][x].empty()) {
        p[i].gun = MAP[y][x].top();
        MAP[y][x].pop();
    }
}
void dropWeapon(int i) {
    int x = p[i].x, y = p[i].y;
    if(p[i].gun) 
        MAP[y][x].push(p[i].gun);
    p[i].gun = 0;
}
void loser(int i) {
    // 졌으면 들고 있던 무기를 해당 맵에 내려 놓고
    dropWeapon(i);
    // 현재 방향으로 갈건데
    int d = p[i].dir;
    int ny = p[i].y + ydir[d];
    int nx = p[i].x + xdir[d];
    // 빈 칸이 나올떄까지 90도 회전
    // 빈칸 -> 그 칸으로 한칸 전진
    while (nx < 1 || ny < 1 || nx > N || ny > N || findPlayer(ny, nx, i)) {
        d = (d + 1) % 4;

        ny = p[i].y + ydir[d];
        nx = p[i].x + xdir[d];
    }
    // 정보 업데이트
    p[i].dir = d;
    p[i].y = ny;
    p[i].x = nx;
    // 이동한 칸에 무기가 있으면 줍자!
    getWeapon(i);
}
void winner(int i) {
    dropWeapon(i);
    getWeapon(i);
}
void fight(int i, int j) {
    // i번 사람과 j번 사람이 싸운다
    int A = p[i].stat + p[i].gun;
    int B = p[j].stat + p[j].gun;
    // j번이 이겼다!
    if (p[i] < p[j]) {  
        p[j].point += (B - A);
        loser(i);
        winner(j);
    }
    // i번이 이겼다!
    else {
        p[i].point += (A - B);
        loser(j);
        winner(i);
    }
}
void solve() {
    // K라운드 동안 플레이어 한명씩 움직인다
    while (K--) {
        for (int i = 1; i <= M; i++) {
            // 일단 움직인다
            move(i);
            // 같은 위치에 있는 플레이어를 찾는다
            int j = findPlayer(p[i].y, p[i].x, i);
            // 플레이어가 있다면 싸운다
            if (j) 
                fight(i, j);
            // 만약 이동한 위치에 플레이어가 없으면 
            // 무기를 줍자
            else {  
                dropWeapon(i);
                getWeapon(i);
            }
        }
    }
    for (int i = 1; i <= M; i++) {
        cout << p[i].point << " ";
    }
}
int main() {
    input();
    solve();
    return 0;
}
