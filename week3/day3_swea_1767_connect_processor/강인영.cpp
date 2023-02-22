/*
1. map입력 받기 -> 가장 자리에 위치한 core들은 connnected맵에 표시(못가는곳)
2. 벡터에 core 위치만 저장 -> 하나씩 빼내어서 선 만들어주기
  2-1. link 함수 -> 상,하,좌,우 중에서 가장 짧게 방해 없이 그릴 수 있는 전선인가? => check 함수
	2-1-1. 만약 check함수를 통해 가능한 경로가 생기면 draw 함수로 전선 그리기
	2-1-2. 만약 check함수를 통해 불가능한 경로(-1리턴)이면 그냥 넘어가기
  
  제 방법은 틀렸어요...! 여러분 재귀를 써야합니다..
*/

#include <iostream>
#include <vector>
using namespace std;

struct Core {
	int y;
	int x;
};
int T;
int N;
int map[12][12];
int connected[12][12];
vector<Core>v;

//상, 하, 좌, 우
int dir[4][2] = {
	-1,0,
	1,0,
	0,-1,
	0,1,
};

int connectedProcessor = -21e8;
int connectedLine = 0;

int tmpProcessorCnt;
int tmpLineCnt;
int check(int y, int x) {
	int minDist = 21e8;
	int minDir = -1;
	int flag;
	for (int i = 0; i < 4; i++) {
		flag = 0;
		int dy = dir[i][0];
		int dx = dir[i][1];

		int ny = y + dy;
		int nx = x + dx;
		int cnt = 0;
		while (ny >= 0 && nx >= 0 && ny < N && nx < N) {
			if (connected[ny][nx] == 1 && map[ny][nx] == 1) {
				flag = 1;
				break;
			}
			cnt++;
			ny += dy;
			nx += dx;
		}
		//if (cnt != 0 && minDist > cnt && flag == 0) {
		if (flag == 0) {
			//minDist = cnt;
			//minDir = i;
			tmpProcessorCnt++;
			tmpLineCnt += cnt;
		}
	}
	if (connectedProcessor < tmpProcessorCnt) {
		connectedProcessor = tmpProcessorCnt;
		connectedLine = tmpLineCnt;
	}

	return minDir;
}

void draw(int y, int x, int d) {
	int dy = dir[d][0];
	int dx = dir[d][1];

	int ny = y + dy;
	int nx = x + dx;

	while (ny >= 0 && nx >= 0 && ny < N && nx < N) {
		connected[ny][nx] = 1;
		ny += dy;
		nx += dx;
	}
}

void link(int y, int x) {
	int goDir = check(y, x);
	if (goDir != -1)
		draw(y, x, goDir);
}

int main() {
	cin >> T;
	int t = 0;
	int ans = 0;
	while (t < T) {
		cin >> N;

		//map 입력 받기
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] == 1 && (i == 0 || i == N - 1 || j == 0 || j == N - 1)) {
					connected[i][j] = 1;
				}
				else if (map[i][j] == 1) {
					Core core;
					core.y = i;
					core.x = j;
					v.push_back(core);
				}
			}
		}


		//for (int j = 0; j < v.size(); j++) {
		for (int i = 0; i < v.size(); i++) {
			Core core = v[i];
			connected[core.y][core.x] = 1;
			link(core.y, core.x);
			//connected맵에 연결된 core개수와 전선 길이 합산 후 비교
			cout << "----연결확인-----" << endl;
			for (int q = 0; q < N; q++) {
				for (int p = 0; p < N; p++) {
					cout << connected[q][p] << " ";
				}cout << endl;
			}
		}
		//}



		cout << "#" << t << " " << ans << endl;
	}

	return 0;
}
