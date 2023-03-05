/*
N개의 넓은 방 존재 - N-1개 통로 연결
같은 통로 두 번 이상 지나지 않음
통신을 위해 로봇은 동굴 내의 같은 통로 위에 위치해야함(통로의 양 끝)
=> vector와 visited 크기 주의(RuntimeError)
=> 이동하지 않아도 되는 경우 고려
*/

#include <iostream>
#include <vector>
using namespace std;

struct Edge {
	int to;
	int cost;
};

int n, r1, r2; //방개수, 로봇1위치, 로봇2위치
vector<Edge> v[100001]; //방 연결 & 비용 정보 
int visited[100001]; // 방문 확인
int sum;
int min_fee = 21e8; //최소한의 비용으로 연결
int max_dist = -21e8; //최대

void dfs(int now) {
	//연결 경로를 찾음
	if (now == r2) {
		min_fee = sum - max_dist; //지금까지의 연결 경로 중에서 최대로 긴 거리를 빼줘서 그 양 끝에 서 있는 것으로 결과 내기
		return;
	}

	for (int i = 0; i < v[now].size(); i++) {
		int next = v[now][i].to;
		int fee = v[now][i].cost;
		
		if (visited[next] == 1)
			continue;

		visited[next] = 1;
		sum += fee; //비용 합
		if (fee > max_dist) //길 중에서 비용이 최대인 녀석 따로 저장
			max_dist = fee;

		dfs(next); //이동

		//모든 경로 탐색을 위한 복구 작업
		sum -= fee; 
		visited[next] = 0;

	}
}

int main() {
	cin >> n >> r1 >> r2;
	int l, r, t;
	for (int i = 0; i < n - 1; i++) {
		cin >> l >> r >> t;
		v[l].push_back({ r, t });
		v[r].push_back({ l,t });
	}

	
	visited[r1] = 1;
	dfs(r1);
	
	//min_fee가 초기설정 그대로 라는 이야기는 업데이트가 안 되었다는 의미
	//이동할 필요가 없음
	if (min_fee == 21e8)
		cout << 0;
	else cout << min_fee;
	
}
