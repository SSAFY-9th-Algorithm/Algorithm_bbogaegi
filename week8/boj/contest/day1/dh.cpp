#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;


int N, M, K;
int Energy[11][11];
int A[11][11];
vector<int> MAP[11][11];


int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };


void Spring() {

    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){

            if (MAP[i][j].size() == 0) continue;
            int Die = 0;

            vector<int>tmp; // 나이를 먹고 넣어줄 벡터

            sort(MAP[i][j].begin(), MAP[i][j].end());

            for (int k = 0; k < MAP[i][j].size(); k++){
                //cout << MAP[i][j][1];
                int Age = MAP[i][j][k];
                if (Energy[i][j] >= Age) {
                    Energy[i][j] -= Age;
                    tmp.push_back(Age + 1);
                }

                else
                    Die += (Age / 2);
            }

            MAP[i][j].clear();

            for (int k = 0; k < tmp.size(); k++)
                MAP[i][j].push_back(tmp[k]); // 나이를 다시 맵에 넣어주기

            Energy[i][j] += Die;
        }
    }
}

void Fall() {

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (MAP[i][j].size() == 0) continue;

            for (int k = 0; k < MAP[i][j].size(); k++) {

                int Age = MAP[i][j][k];
                if (Age % 5 == 0) { // 5의 배수
                    for (int a = 0; a < 8; a++) {

                        int nx = i + dx[a];
                        int ny = j + dy[a];

                        if (nx >= 1 && ny >= 1 && nx <= N && ny <= N)
                            MAP[nx][ny].push_back(1);

                    }

                }

            }

        }

    }
}


void Winter() {

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {

            Energy[i][j] = Energy[i][j] + A[i][j];
        }
    }
}


int main() {
    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) {
            cin >> A[i][j];
            Energy[i][j] = 5;
        }

    for (int i = 0; i < M; i++) {
        int x, y, z;
        cin >> x >> y >> z;

        MAP[x][y].push_back(z);
    }

    for (int i = 0; i < K; i++) {

        Spring();
        Fall();
        Winter();
    }



    int Answer = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {

            Answer = Answer + MAP[i][j].size();
        }

    }


    cout << Answer << endl;
}









