#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

/*
N x N 크기 (4 ~ 10)
사람 수 (1 ~ 10)
계단 2개 (1 ~ 10)
=> 모든 것들은 좌표가 겹치지 않음

계단은 한 번에 3명씩 이동 가능
계단을 내려가는 시간 + 1을 해줘야함
(도착해서 내려가기 시작하는 데에 1분 소요)
-> 계단마다 해당 계단까지 이동하는 데 걸리는 시간 기준으로
사람 정보 + 시간 정보 오름차순 정렬

사람들에 대한 visited를 만들어서 계단 진입 여부를 확인한 후,
앞쪽부터 사람 넣기
*** => 한 계단만을 이용하는게 더 시간이 적을 수도 있음
	-> 계단에 넣기 전에 해당 계단으로 갔을 때 제일 오래걸리는 친구와 값 비교해주기
-> 짧은 계단을 0번인덱스로, 긴 계단을 1번 인덱스로 넣어주자
*/

struct Person {
	int idx;
	int y;
	int x;

	// 초기 세팅값은 대기 시간을 제외함
	int dist1; // 1번 계단으로 가는 데 걸리는 시간
	int dist2; // 2번 계단으로 가는 
	int total1; // 1번 계단으로 가는 데 걸리는 시간 + 계단 타고 내려가는데 걸리는 시간
	int total2; // 2번 계단으로 가는 데 걸리는 시간 + 계단 타고 내려가는데 걸리는 시간
};

struct Stair {
	int y;
	int x;
	int cost;
};

int N; // 4 ~ 10
int numOfPerson; // 1~10

int visited[11]; // 사람 최대 10명

Stair stairs[2];

int mat[11][11];

// 사람 정보는 항상 1부터 채워진다.
Person people[11];
Person stair1[11];
Person stair2[11];

int sidx1; // 1번 계단 들어간 번호
int sidx2; // 2번 계단 들어간 번호
int backIdx1; // 1번 계단 이용 시 제일 오래걸리는 사람
int backIdx2; // 2번 계단 이용 시 제일 오래걸리는 사람

void reset() {
	memset(visited, 0, sizeof(visited));
	memset(mat, 0, sizeof(mat));
	memset(stairs, 0, sizeof(stairs));
	memset(people, 0, sizeof(people));
	memset(stair1, 0, sizeof(stair1));
	memset(stair2, 0, sizeof(stair2));

	numOfPerson = 1;
	sidx1 = 1;
	sidx2 = 1;
}

void setDist() {
	for (int i = 1; i <= numOfPerson; i++) {
		Person now = people[i];
		now.dist1 = abs(now.y - stairs[0].y) + abs(now.x - stairs[0].x) + 1;
		now.dist2 = abs(now.y - stairs[1].y) + abs(now.x - stairs[1].x) + 1;
		now.total1 = abs(now.y - stairs[0].y) + abs(now.x - stairs[0].x) + stairs[0].cost;
		now.total2 = abs(now.y - stairs[1].y) + abs(now.x - stairs[1].x) + stairs[1].cost;
		people[i] = now;
	}
}

bool cmpStair1(Person p1, Person p2) {
	return p1.dist1 < p2.dist1;
}

bool cmpStair2(Person p1, Person p2) {
	return p1.dist2 < p2.dist2;
}

void input() {
	Stair temp[2] = { 0, };
	int tIdx = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> mat[i][j];
			if (mat[i][j] == 1) {
				people[numOfPerson] = { numOfPerson, i, j };
				numOfPerson++;
			}
			else if (mat[i][j] > 1 && mat[i][j] <= 10) { // 계단이라면
				temp[tIdx++] = { i, j, mat[i][j]}; // 계단에 진입 후 1분 기다려야하므로
			}
		}
	}
	if (temp[0].cost < temp[1].cost) {
		stairs[0] = temp[0];
		stairs[1] = temp[1];
	}
	else {
		stairs[0] = temp[1];
		stairs[1] = temp[0];
	}
	setDist();
	memcpy(stair1, people, sizeof(people));
	memcpy(stair2, people, sizeof(people));
	sort(stair1 + 1, stair1 + numOfPerson, cmpStair1);
	sort(stair2 + 1, stair2 + numOfPerson, cmpStair2);
	backIdx1 = numOfPerson - 1;
	backIdx2 = numOfPerson - 1;
}

bool chkVisited() {
	for (int i = 1; i < numOfPerson; i++) {
		if (!visited[i])
			return false;
	}
	return true;
}

int solution() {
	vector<int> v1; // s1로 진입한 사람
	vector<int> v2; // s2로 진입한 사람
	int delay1 = 0;
	int delay2 = 0;
	int t1 = 0;
	int t2 = 0;
	// 모든 사람이 계단을 내려갈때까지 반복
	while (!chkVisited()) {
		// 방문한 사람 다음부터 봐야하므로
		while (visited[stair1[sidx1].idx]) {
			sidx1++;
		}
		while (visited[stair2[sidx2].idx]) {
			sidx2++;
		}
		while (visited[stair1[backIdx1].idx]) {
			backIdx1--;
		}
		while (visited[stair2[backIdx2].idx]) {
			backIdx2--;
		}
		Person s1 = stair1[sidx1];
		Person s2 = stair2[sidx2];
		Person b1 = stair1[backIdx1];
		Person b2 = stair2[backIdx2];
		
		if (s1.total1 <= b2.total2) {
			if (s1.total1 <= people[s1.idx].total2) {
				int flag = 0;
				visited[s1.idx] = 1;
				sidx1++;
				if (v1.size() >= 3) { // 이때부터 대기자가 생기기 시작
					int temp = stair1[v1[v1.size() - 3]].total1;
					if (sidx1 >= numOfPerson)
						flag = 1;
					delay1 = temp - (stair1[sidx1 - flag].total1 - stairs[0].cost);
					if (delay1 < 0)
						delay1 = 0;
					else {
						for (int i = sidx1 - flag; i <= numOfPerson; i++) {
							stair1[i].total1 += delay1;
							people[stair1[i].idx].total1 = stair1[i].total1;
						}
					}
				}
				t1 = stair1[sidx1 - 1].total1;
				v1.push_back(sidx1 - 1);
			}
		}
		if (s2.total2 <= b1.total1) {
			if (s2.total2 <= people[s2.idx].total1) {
				int flag = 0;
				visited[s2.idx] = 2;
				sidx2++;
				if (v2.size() >= 3) { // 이때부터 대기자가 생기기 시작
					int temp = stair2[v2[v2.size() - 3]].total2;
					if (sidx2 >= numOfPerson)
						flag = 1;
					delay2 = temp - (stair2[sidx2 - flag].total2 - stairs[1].cost);
					if (delay2 < 0)
						delay2 = 0;
					else {
						for (int i = sidx2 - flag; i <= numOfPerson; i++) {
							stair2[i].total2 += delay2;
							people[stair2[i].idx].total2 = stair2[i].total2;
						}
					}
				}
				t2 = stair2[sidx2 - 1].total2;
				v2.push_back(sidx2 - 1);
			}
		}
	}
	return max(t1, t2);
}

int main(void) {
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		cout << "#" << tc << " " << solution() + 1 << '\n';
	}
}
