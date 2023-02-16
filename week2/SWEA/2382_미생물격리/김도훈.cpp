#include <iostream>
#include <vector>
using namespace std;

// 군집에 대한 정보를 벡터를 이용하여 입력을 받는다.
// -> 세로위치, 가로위치, 미생물 수, 이동방향 (상: 1, 하: 2, 좌: 3, 우: 4)
// 



struct Info {
	int y, x;
	int cnt;
	int dir;
};

int N, M, K;	// 셀 개수, 격리 시간, 미생물 군집 개수
				// K줄만큼 입력을 받는다
// 군집 정보 저장
vector<Info>v;
int dy[4] = { -1, 1, 0, 0 };	// 일단 방햑벡터 만들어놓기
int dx[4] = { 0, 0, -1, 1 };	// -> 순서대로 상, 하, 좌, 우
								// 				1	2	3	4 <--인덱스 역할 
int visited[100][100];
int sum[100][100];

int main()
{
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {

		int res = 0;
		v.clear();
		
		// 입력
		cin >> N >> M >> K;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				visited[i][j] = 0;
				sum[i][j] = 0;
			}
		}

		for (int i = 0; i < K; i++) {
			int y, x, cnt, dir;
			cin >> y >> x >> cnt >> dir;
			// 입력 받고 바로 군집 저장 벡터v에 넣어주기
			v.push_back({ y, x, cnt, dir });
		}


		for (int i = 0; i < M; i++) {	// M시간동안 진행
			for (int j = 0; j < K; j++) {	// 각 군집의 이동을 보자.
				// 군집의 이동 --> dy[v[j].dir]  dx[v[j].dir]만큼 이동한다.
				Info now = v[j];

				if (now.cnt == 0) continue;	// 군집의 미생물 수가 0이되면 사라진다

				now.y = now.y + dy[now.dir];
				now.x = now.x + dx[now.dir];

				// #1 이동했을 때 약품이 칠해져있는 칸에 도착하면
				if (now.y == 0 || now.x == 0 || now.y == N - 1 || now.x == N - 1) {
					now.cnt = now.cnt / 2;	// 미생물 수가 반으로 줄고
					// 방향이 반대로 된다
					// 1 -> 2
					// 3 -> 4
					// 2 -> 1
					// 4 -> 3	// 홀수, 짝수 다르다
					now.dir = -1 + (now.dir % 2) * 2;
				}

				// 이동이 끝나고 방문여부를 visited에 저장
				if (now.cnt > 0)
					visited[now.y][now.x] += 1;

				// 군집의 정보를 업데이트
				v[j] = now;
			}
			//	#2 이동했는데 겹치는 군집이 있다 -> visited[][]값이 1초과이다
			for (int j = 0; j < K; j++) {
				Info next = v[j];
				
				int MAX = 0;
				int idx = 0;
				//if (visited[next.y][next.x] == 1) {
					sum[next.y][next.x] += next.cnt;
				//}
				if (visited[next.y][next.x] > 1) {
					
					// 미생물의 개수 가장 많은 군집찾기
					if (next.cnt > MAX) {
						MAX = next.cnt;
						idx = j;
					}
					//sum[next.y][next.x] += next.cnt;
					next.cnt = 0;
					
				}
				v[idx].cnt = MAX;
			}

		}

		for (int p = 0; p < N; p++) {
			for (int q = 0; q < N; q++) {
				res += sum[p][q];
			}
		}
		cout << "#" << tc << " " << res << endl;
	}

	return 0;
}
