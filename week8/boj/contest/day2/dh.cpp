#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

// 방향 1 2 3 4 -> 상 하 좌 우

// 상어에 대한 정보를 모두 struct를 만들어서 한번에 관리
struct Shark {
    int x;
    int y;
    int dir; // 상어의 현재 방향
    vector<int>priority[5]; 
    // priority[1]: 현재 방향이 위 쪽일때 다음 방향 우선순위
    // priority[2]: 현재 방향이 위 쪽일때 다음 방향 우선순위
    int flag;
    // flag가 0이면 상어가 존재 1이면 쫓겨났으므로 냄새 체크해줄필요 없다
};


int MAP[3][21][21];

//vector<int>MAP[21][21]; // 맵에 정보를 저장한다 -> 처음에 이렇게 했는데 push_back으로 값을 넣어줘야해서 안됨
// 맵에 존재하는 상어, 냄새가 없어지는 시간, 냄새가 몇번 상어의 것인지 순으로 저장
// MAP[0][x][y], MAP[1][x][y], MAP[2][x][y]
int N, M, k;
Shark shark[450];

int dx[] = { 0, -1, 1, 0, 0 };
int dy[] = { 0, 0, 0, -1, 1 };


int Check()
{
    for (int i = 2; i <= M; i++)
    {
        if (shark[i].flag == 0) return 0; // 1번을 제외한 상어 하나라도 있으면 조건 성립X
    }
    return 1;
}


void smellSet(int t) // t는 현재시간
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            MAP[1][i][j] -= 1;

    for (int i = 1; i <= M; i++)
    {
        if (shark[i].flag == 1) continue; // 이미 쫓겨난 상어

        int x = shark[i].x;
        int y = shark[i].y;
        MAP[1][x][y] = k;
        MAP[2][x][y] = i;
    }
}

void Move(int t) // 상어 움직이기
{
    for (int i = 1; i <= M; i++) {
        if (shark[i].flag == 1) continue;
        int x = shark[i].x;
        int y = shark[i].y;
        MAP[0][x][y] = 0; // 현재 상어들의 위치 없애줘야
    }

    for (int i = 1; i <= M; i++) {
        if (shark[i].flag == 1) continue;

        int x = shark[i].x;
        int y = shark[i].y;
        int d = shark[i].dir;

        // 자기 냄새 위치에 대한 정보 기억
        int storeX = -1; // 처음에 0으로 초기화했는데 좌표가 0일수도 있다
        int storeY = -1;
        int storeDir = -1;
       
        int flag = 0;

        for (int j = 0; j < shark[i].priority[d].size(); j++) // 상어마다 정해진 우선순위 방향대로 움직이기
        {
            if (shark[i].flag == 1) continue; // 쫓겨난 상어는 고려X
            int ndir = shark[i].priority[d][j];
            int nx = x + dx[ndir];
            int ny = y + dy[ndir];
            if (nx >= 0 && ny >= 0 && nx < N && ny < N) {
                if (MAP[1][nx][ny] <= 0)
                {
                    flag = 1; // 주변이 이미 냄새가 뿌려져 있는 경우 따로 봐주기 위해
                    if (MAP[0][nx][ny] == 0) { // 그 칸에 상어가 없다 -> 그냥 이동 가능
                        MAP[0][nx][ny] = i;
                    }
                    else { // 0이 아닌 그 번호의 상어가 존재한다
                        if (MAP[0][nx][ny] < MAP[0][x][y])
                            MAP[0][nx][ny] = i;
                        else {
                            shark[i].flag = 1;
                            continue;
                        }
                    }
                    shark[i].x = nx;
                    shark[i].y = ny;
                    shark[i].dir = ndir;
                    break;
                }
                else // 가려는 방향의 칸에 다른 상어의 냄새가 뿌려져있다
                {
                    if (MAP[2][nx][ny] == i) 
                    {
                        if (storeX == -1)   // 우선순위 방향대로 보다가 가장 먼저 자기 냄새를 발견했을 때 
                        {
                            storeX = nx;
                            storeY = ny;
                            storeDir = ndir;
                        } // 이렇게 저장해두고 사방이 냄새로 뿌려져있을때 (flag=0일 때) 이 좌표로 이동시킨다
                    }
                }
            }
        }

        if (flag == 0)
        {
            MAP[0][storeX][storeY] = i;
            shark[i].x = storeX;
            shark[i].y = storeY;
            shark[i].dir = storeDir;
        }
    }
}


int main() {
    cin >> N >> M >> k;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> MAP[0][i][j];
            int num = MAP[0][i][j]; // 상어 번호
            if (MAP[0][i][j] != 0) { // 상어가 존재한다
                shark[num].x = i;
                shark[num].y = j;
            }
            MAP[1][i][j] = 0;
            MAP[2][i][j] = 0;
        }
    }



    for (int i = 1; i <= M; i++) {
        int d;
        cin >> d;
        shark[i].dir = d;
    }

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= 4; j++) {
            int arr[4];
            cin >> arr[0] >> arr[1] >> arr[2] >> arr[3];
            for (int k = 0; k < 4; k++)
            {
                shark[i].priority[j].push_back(arr[k]);
                // 각 방향마다 우선순위 방향 저장
            }
        }
    }

   

    int res = 0;

    for (int t = 0; t <= 1000; t++) {

        
        if (Check()) {
            res = t;
            break;
        }
        smellSet(t);
        
        Move(t);
       
    }
    if (res != 0)
        cout << res << endl;
    else
        cout << -1 << endl;
}