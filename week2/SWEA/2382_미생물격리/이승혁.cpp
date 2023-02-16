// 3 일 동안 계속 1~2시간 정도 설계 포기 설계 포기 반복
// 포기한 이유와 해결 방법 => 이동시키는건 괜찮은데, 한 곳으로 모이는 애들을 비교하고 다시 갱신하는 과정이
// 헷갈리고 딱히 방안이 떠오르지 않았다.
// queue에 이동할 좌표를 담아서 걔들만 꺼내서 효율적으로 해야겠다 생각했는데 이동할 애들이 0,0 3명이면 꺼내서 비교할 방법이 없음
// 있다고 해도 너무 복잡할 것 같았다. 그래서 하다가 포기, DAT할까 하다가 포기, for문으로 다 돌려볼까 하다가 포기(시간을 고려하다보니 오래걸릴까?해서)
// 구조체를 배열로 만드는걸 생각도 못하고 있었다.

// + 오늘 퇴근 전에 효정이가 일단 때려박어봐? 쑤셔박어봐? 해서 오늘은 일단 펜으로 하지 말고 컴퓨터로 두드려야겠다
// 라고 하면서 그냥 해봤다. 

// 강사님 스타일대로 reset, input, solve, output 나누고 입력부터 하나하나 채워나가고
// 강사님도 중간에 프린트 해보면서 잘 되고있나 확인하길래(왠지 그 과정 하면 코드 못짜는 사람 같아서 안했음)
// 해봤더니 훨씬 자신감? 생겨서 뒷단 짜는게 속도가 붙었다. 40분? 만에 처음부터 끝까지 짠 것 같다. 나한텐 나름 빨리 짠 듯.
// 다음엔 설계를 더 잘 할 수 있을 것 같다. 


#include <iostream>
#include <vector>

using namespace std;

// 미생물 군집 구조체
struct cluster {
	int y, x;
	int amount;
	int direction;
};
// 미생물 좌표 구조체
struct Coords {
	int y, x;
};

cluster arr[1000]; // 미생물 군집 리스트
 //MicroMove 함수에서 이동할, 갱신된 좌표를 가진 구조체 인덱스 보유
vector<int> coord[100][100];

// 1:상 2:하 3:좌 4:우
int DA[5][2] = { {0,0},{-1,0},{1,0},{0,-1},{0,1} };
// 1->2, 2->1, 3->4, 4->3 방향 변경
int Dchange[5] = { 0,2,1,4,3 };
int N, M, K; // N : 셀 크기, M : 격리 시간 , K : 미생물 군집 수



// 미생물 구조 갱신 함수
void MicroMove() {
	int MicroCNT[100][100] = { 0, };

	for (int i = 0; i < K; i++) {
		cluster now = arr[i];
		//cout << i << "번 군집 " << now.y << "," << now.x << "에서 " << now.amount << " 마리 "<<now.direction<<"방향 이동\n";
		// 미생물 없다면 패스
		if (now.amount == 0)continue;

		int ny = now.y + DA[now.direction][0];
		int nx = now.x + DA[now.direction][1];
		// 범위 계산
		// 계산 후에 끝(0 or N-1)이 된다면 방향을 바꾼다.
		if (ny == 0 || ny == N - 1 || nx == 0 || nx == N - 1) {
			now.direction = Dchange[now.direction];
			now.amount /= 2;
		}
		now.y = ny;
		now.x = nx;
		//cout << i << "번 군집 " << ny << "," << nx << "로 " << now.amount << " 마리 " << now.direction << "방향 이동\n";
		arr[i] = now;
		// isValid에서 검증할 ny nx 
		coord[ny][nx].push_back(i);
	}


};

// 미생물 위치 확정 함수
void isValid() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (coord[i][j].size() > 1) {
				// i,j 좌표로 올 군집이 2개 이상
				int temp_amount = 0;
				int MAX_amount = -21e8;
				int MAX_direction = 0;
				for (int vnum = 0; vnum < coord[i][j].size(); vnum++) {
					cluster now = arr[coord[i][j][vnum]];
					temp_amount += now.amount;
					// 현재 양이 지금까지 최대 양보다 크다면
					// 방향을 현재 스트럭쳐의 방향으로 바꾼다.
					if (now.amount > MAX_amount) {
						MAX_amount = now.amount;
						MAX_direction = now.direction;
					}
					// 현재의 어마운트도 0으로 바꾼다. 나중에 최종 한마리만 남기기 위해 벡터 첫번째 인덱스 애를
					// temp_amount로 할당해서 1개만 남기기
					now.amount = 0;
					arr[coord[i][j][vnum]] = now;
				}
				arr[coord[i][j][0]] = { i,j,temp_amount,MAX_direction };
			}
		}
	}
	memset(coord, 0, sizeof(coord));
};


int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		//reset
		memset(arr, 0, sizeof(arr));
		// input()
		cin >> N >> M >> K;
		for (int i = 0; i < K; i++) {
			cluster micro;
			cin >> micro.y >> micro.x >> micro.amount >> micro.direction;
			arr[i] = micro;
		}
		// solve
		for (int t = 1; t <= M; t++) {
			// arr에 담긴 군집 요소들을 이동/갱신 시킨다.
			MicroMove();
			// 해당 구조체가 자기 좌표에 들어갈 수 있는지 확인하는 작업
			isValid();
			//cout << t << "번 이동 후\n";
			//for (int i = 0; i < K; i++) {
			//	cout << i << "번째 군집의 좌표 : " << arr[i].y << " " << arr[i].x << " , 미생물 수: " << arr[i].amount << " 다음 방향 : " << arr[i].direction << '\n';
			//}
		}

		// output
		int sum = 0;
		for (int i = 0; i < K; i++) {
			if (arr[i].amount > 0)sum += arr[i].amount;
		}
		cout << "#" << tc << " " << sum << '\n';

	}

}
