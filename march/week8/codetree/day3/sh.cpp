#include <iostream>
#include <queue>
using namespace std;

struct player { int y, x, dir, stat, gunsum; };
player players[31];

priority_queue<int>playersguns[31];
priority_queue<int>GUNS[21][21];

int ydir[] = { -1,0,1,0 }, xdir[] = { 0,1,0,-1 }, res[31];
int N, M, k;

void input() {
    cin >> N >> M >> k;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int n; cin >> n; GUNS[i][j].push(n);
        }
    }

    for (int i = 1; i <= M; i++)
    {
        player now;
        cin >> now.y >> now.x >> now.dir >> now.stat;
        now.gunsum = 0;
        players[i] = now;

    }
}

void move(int type, int idx) {

    int nowy = players[idx].y;
    int nowx = players[idx].x;
    if (!type)
    {
        int d = players[idx].dir;
        while (1) {
            int ny = nowy + ydir[d];
            int nx = nowx + xdir[d];
            if (ny <1 || nx<1 || ny>N || nx>N)
            {
                if (d == 2)d = 0;
                else if (d == 0)d = 2;
                else if (d == 1)d = 3;
                else if (d == 3)d = 1;
                continue;
            }

            players[idx].dir = d;
            players[idx].y = ny;
            players[idx].x = nx;
            break;
        }
    }
    else {
        int d = players[idx].dir;
        while (1) {
            int ny = nowy + ydir[d];
            int nx = nowx + xdir[d];
            if (ny <1 || nx<1 || ny>N || nx>N)
            {
                d++;
                if (d > 3)d = 0;
                continue;
            }
            int flag = 0;

            for (int i = 1; i <= M; i++) {
                if (i == idx)continue;
                if (players[i].y == ny && players[i].x == nx)
                {
                    d++;
                    if (d > 3)d = 0;
                    flag = 1;
                    break;
                }
            }
            if (flag)continue;
            //벗어나지 않았다. 갈 수 있다
            players[idx].dir = d;
            players[idx].y = ny;
            players[idx].x = nx;

            if (!GUNS[ny][nx].empty())
            {
                playersguns[idx].push(GUNS[ny][nx].top());
                players[idx].gunsum += GUNS[ny][nx].top();
                GUNS[ny][nx].pop();
            }
            break;
        }
    }

}

void fromGround(int idx) {
    int py = players[idx].y;
    int px = players[idx].x;
    if (players[idx].gunsum)
    {

        int ownMax = playersguns[idx].top();
        int mapMax = GUNS[py][px].top();

        if (mapMax > ownMax) {

            while (!playersguns[idx].empty()) {
                int now = playersguns[idx].top(); playersguns[idx].pop();
                GUNS[players[idx].y][players[idx].x].push(now);
            }
            GUNS[players[idx].y][players[idx].x].pop();

            playersguns[idx].push(mapMax);
            players[idx].gunsum = mapMax;
        }
    }
    // 없으면 바로 획득
    else
    {
        int gun = GUNS[py][px].top(); GUNS[py][px].pop();
        players[idx].gunsum += gun;
        playersguns[idx].push(gun);
    }

}

void fight(int p1, int p2) {
    int p1sum = players[p1].gunsum + players[p1].stat;
    int p2sum = players[p2].gunsum + players[p2].stat;
    int winner, loser;

    if (p1sum == p2sum) {
        if (players[p1].stat > players[p2].stat) {
            winner = p1;
            loser = p2;
        }
        else {
            winner = p2;
            loser = p1;
        }
    }
    else if (p1sum > p2sum) {
        winner = p1;
        loser = p2;
    }
    else {
        winner = p2;
        loser = p1;
    }

    res[winner - 1] += abs(p1sum - p2sum);

    int py = players[loser].y;
    int px = players[loser].x;
    // 패자 총 버리기
    while (!playersguns[loser].empty()) {
        GUNS[py][px].push(playersguns[loser].top());
        playersguns[loser].pop();
        players[loser].gunsum = 0;
    }

    // 패자 이동
    move(1, loser);

    // 승자 총 교환
    int wy = players[winner].y;
    int wx = players[winner].x;
    if (!GUNS[wy][wx].empty() && players[winner].gunsum)
    {
        fromGround(winner);
    }
    else if (!GUNS[wy][wx].empty() && !players[winner].gunsum)
    {
        players[winner].gunsum = GUNS[wy][wx].top();
        playersguns[winner].push(GUNS[wy][wx].top()); GUNS[wy][wx].pop();

    }
}


void solution() {
    for (int i = 1; i <= M; i++) {
        player now = players[i];
        // 이동
        move(0, i);

        int flag = 1;
        // 전투 여부확인
        for (int j = 1; j <= M; j++) {
            if (j == i)continue;
            // 같은 위치라면 싸운다
            if (players[i].y == players[j].y && players[i].x == players[j].x)
            {
                flag = 0; fight(i, j);
            }
        }
        // 전투 X 
        if (flag)
        {
            // 총 있는지 확인
            if (!GUNS[players[i].y][players[i].x].empty())
                fromGround(i);
        }
    }
}

int main() {

    input();
    for (int i = 0; i < k; i++) solution();
    for (int i = 0; i < M; i++)cout << res[i] << " ";
}
