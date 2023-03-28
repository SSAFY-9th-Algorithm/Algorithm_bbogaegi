#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int ydir[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int xdir[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

int N, M, K;

int board[11][11]; // 양분
int A[11][11];
vector<int> MAP[11][11]; 
int res;

void input() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> A[i][j];
            board[i][j] = 5;
        }
    }

    for (int i = 0; i < M; i++) {
        int y, x, z;
        cin >> y >> x >> z;
        MAP[y][x].push_back(z);
    }
}

void solve() {
    for (int i = 0; i < K; i++) {
        // 봄 -> 자신의 나이만큼 양분을 먹고, 나이가 1 증가
        // 그런데 양분이 부족하면 나무가 죽는다
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                // 그 칸에 나무가 없으면 continue
                if (MAP[i][j].size() == 0)
                    continue;

                int die = 0;
                vector<int> tmp;

                sort(MAP[i][j].begin(), MAP[i][j].end());

                // 이제 나무를 키울건데
                for (int k = 0; k < MAP[i][j].size(); k++) {
                    int age = MAP[i][j][k];
                    // 양분이 충분하면 양분을 먹고 나무가 자란다!
                    if (board[i][j] >= age) {
                        board[i][j] = board[i][j] - age;
                        tmp.push_back(age + 1);
                    }
                    // 양분이 부족하면 이 나무는 죽는다!
                    // 죽은 나무는 나중에 양분이 된다!
                    else
                        die += (age / 2);
                }
                // 맵을 비우고 자란 애들을 다시 담아준다
                MAP[i][j].clear();
                for (int k = 0; k < tmp.size(); k++)
                    MAP[i][j].push_back(tmp[k]);

                // 여름 -> 이제 해당 칸의 양분을 아까 죽은 나무의 나이/2 만큼 더해주자!
                board[i][j] = board[i][j] + die;
            }
        }
        // 가을 -> 번식하는 나무는 나이가 5의 배수이어야 하며, 
        // 인접한 8개의 칸에 나이가 1인 나무
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                // 그 칸에 나무가 없으면 continue
                if (MAP[i][j].size() == 0)
                    continue;

                for (int k = 0; k < MAP[i][j].size(); k++) {
                    int age = MAP[i][j][k];

                    if (age % 5 != 0)
                        continue;
                    // 8방향 번식
					for (int d = 0; d < 8; d++) {
						int ny = i + ydir[d];
						int nx = j + xdir[d];

						if (ny >= 1 && nx >= 1 && ny <= N && nx <= N)
							MAP[ny][nx].push_back(1);
					}
                    
                }
            }
        }
        // 겨울 -> 땅에 양분을 추가
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                board[i][j] += A[i][j];
    }

    for (int i = 1; i <= N; i++) 
        for (int j = 1; j <= N; j++) 
            res += MAP[i][j].size();
}


int main(void) {
    fastIO;

    input();
    solve();
    cout << res << '\n';

    return 0;
}
