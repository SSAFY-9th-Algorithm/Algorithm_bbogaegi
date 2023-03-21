//#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int N, M;
int MAP[9][9];

vector <pair<int, int>> cctv;

int ydir[] = { -1,0,1,0 };
int xdir[] = { 0,-1,0,1 };

int ans = 21e8;

// 감시 영역을 채울건데
// ch로 감시 중인 영역을 채울거임
void checkArea(int y, int x, int d, int em, int ch) { 
	while (true) 
	{
		y += ydir[d]; 
		x += xdir[d];
		if (y < 0 || y >= N || x < 0 || x >= M || MAP[y][x] == 6) 
			break;
		
		if (MAP[y][x] == em) 
			MAP[y][x] = ch;
	}
}

void cctvtype(int y, int x, int d, int em, int ch) { 
	// 1
	if (MAP[y][x] == 1) { 
		checkArea(y, x, d, em, ch);
	}
	// 2
	else if (MAP[y][x] == 2) { 
		checkArea(y, x, d, em, ch);
		checkArea(y, x, (d + 2) % 4, em, ch);
	}
	// 3
	else if (MAP[y][x] == 3) { 
		checkArea(y, x, d, em, ch);
		checkArea(y, x, (d + 1) % 4, em, ch);
	}
	// 4
	else if (MAP[y][x] == 4) { 
		checkArea(y, x, d, em, ch);
		checkArea(y, x, (d + 1) % 4, em, ch);
		checkArea(y, x, (d + 3) % 4, em, ch);
	}
}

void dfs(int now) { 
	if (now == cctv.size()) {
		int area = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (MAP[i][j] == 0) 
					area++;
			}
		}
		if (ans > area) 
			ans = area;
	}
	else {
		int y = cctv[now].first; 
		int x = cctv[now].second;

		for (int i = 0; i < 4; i++) {
			// 내가 현재 now번째 cctv를 확인 중이면
			// 감시 영역은 -(now + 1)로 채워두자
			cctvtype(y, x, i, 0, -(now + 1)); 
			dfs(now + 1);
			// 복구
			cctvtype(y, x, i, -(now + 1), 0); 
		}
	}
}

int main() {
	//fastIO;

	//cin >> N >> M;
	scanf("%d %d", &N, &M);
	cctv.clear();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			//cin >> MAP[i][j];
			scanf("%d", &MAP[i][j]);
			if (MAP[i][j] >= 1 && MAP[i][j] <= 5) {
				cctv.push_back({ i, j }); // CCTV 위치 저장
			}
		}
	}

	for (int i = cctv.size() - 1; i >= 0; i--) {
		int y = cctv[i].first; 
		int x = cctv[i].second;
		// 5번 타입은 4방향 다보는 경우 1가지
		if (MAP[y][x] == 5) { 
			for (int n = 0; n < 4; n++) 
				// 영향을 주지 않는 값으로 채워 두자
				checkArea(y, x, n, 0, -10);
			cctv.erase(cctv.begin() + i); 
		}
	}

	dfs(0); 

	//cout << ans;
	printf("%d", ans);
	return 0;
}
