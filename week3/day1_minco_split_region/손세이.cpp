#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

// 잘못된 접근
// 처음에 마을과 연결되었는지 확인할 때 간선의 개수가 마을보다 많을 수 있음을 간과해서 오답이 나옴...
// Edge 케이스 처리

int N; // 마을의 개수
int MAP[9][9]; // 마을의 연결 정보 저장
int P[9]; // 각 마을의 유권자 수 저장
int used[9];
vector<int>path;
int res = 21e8;
int sum;
int total;
int M;

// 초기화
void INIT() {
    memset(MAP, 0, sizeof(MAP));
    memset(P, 0, sizeof(P));
    memset(used, 0, sizeof(used));
    path.clear();
    total = 0;
    sum = 0;
    res = 21e8;
}

// 연결 여부 확인
bool isConnected() {
	int acnt = 0, bcnt = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		for (int j = i + 1; j < path.size(); j++) {
			int y = path[i];
			int x = path[j];
			if (MAP[y][x] == 1) acnt++;
		}
	}
	for (int i = 1; i <= N - 1; i++) {
		for (int j = i + 1; j <= N; j++) {
			if (used[i] == 0 && used[j] == 0) {
				if (MAP[i][j] == 1) bcnt++;
			}
		}
	}
	if (path.size() > 1 && acnt >= path.size() - 1 && bcnt >= N - path.size() - 1) return true;
	if (path.size() == 1 && bcnt >= N - path.size() - 1) return true;

    return false;
}

void dfs(int level) {
    if (res == 0)
        return;

    if (level == M) {
        if (isConnected()) {
            int Bcnt = total - sum;
            res = min(res, abs(sum - Bcnt));
            /*for (int i = 0; i < path.size(); i++)
                cout << path[i] << ' ';
            cout << '\n';*/
        }
        return;
    }

    for (int next = 1; next <= N; next++) {
        if (used[next] == 1)
            continue;

        path.push_back(next);
        sum += P[next];
        used[next] = 1;

        dfs(level + 1);

        used[next] = 0;
        sum -= P[next];
        path.pop_back();
    }
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        // reset
        INIT();
        // input
        cin >> N;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                cin >> MAP[i][j];
        for (int i = 1; i <= N; i++) {
            cin >> P[i];
            total += P[i];
        }
        // solve
        for (int i = 1; i <= N / 2; i++) {
            M = i;
            memset(used, 0, sizeof(used));
            used[0] = 1;
            dfs(0);
        }
        // output
        cout << '#' << tc << ' ';
        if (res == 21e8) cout << "0\n";
        else cout << res << '\n';
    }

    return 0;
}
