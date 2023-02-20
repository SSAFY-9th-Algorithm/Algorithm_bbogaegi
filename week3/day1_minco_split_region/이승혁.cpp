#################미해결 문제########################
#################미해결 문제########################
#################미해결 문제########################
#################미해결 문제########################
#################미해결 문제########################
#################미해결 문제########################

## 1. 지역을 어떻게 나누지? ( 1/234, 12/34, 123/4, 13/24, 14/23, 2, 134, ... ) 
## 2. 1, 234 -> for i=0;i<path.size()-1;i++, j=i+1; j<path.size(); j++ , MAP[i][j]!=0 break(연결 못한다는 뜻)

아..풀고싶어라..


#include <iostream>
#include <vector>
using namespace std;

int N;
int visited[4];
int parent[8];
int nparent[8];
vector<int>path;

// #1. 지역을 나눈다 -> 재귀를 통해 마을을 선택
// 1-1 -> 4개의 경우 1000 1100 1110 1111 .... 이런식?
// #2. 가능한지 확인한다 -> 연결 -> 나누어진 마을(1끼리, 0끼리) 이어질 수 있는지 확인한다.
// #3. 가능하다면 마을의 합의 차를 구한다.


void dfs(int level) {
	if (level == N) {
		for (int i = 0; i < path.size(); i++) {
			cout << path[i] << " ";
		}
		cout << '\n';
		return;
	}

	for (int i = 0; i < N; i++) {
		if (visited[i] == 1)continue;
		if (path.size() > 1 && path[path.size() - 2] > i) continue;
		path.push_back(i);
		visited[i] = 1;
		
		dfs(level + 1);

		path.pop_back();
		visited[i] = 0;

	}

}


int main() {
	N = 4;
	int MAP[4][4] =
	{ {0, 0, 1, 0,},
	 {0, 0, 1, 0,},
	 {1, 1, 0, 1,},
	 {0, 0, 1, 0,} };

	 int w[4]={6, 7, 4, 8,};

	 for (int i = 0; i < N; i++)parent[i] = i;

	 for (int i = 0; i < N; i++) {
		 for (int j = i + 1; j < N; j++) {
			 if (MAP[i][j] == 1);
			 parent[j] = i;
		 }
	 }

	 dfs(0);

}
