/*
부서의 업무 조직 - 완전이진트리
부서장(루트) - 각 직원(왼쪽 & 오른쪽 부하 직원) - 말단 직원(부하X)
모든 말단 직원부터 부서장까지의 거리 동일
조직도 트리 높이 : H
업무 R일동안 진행

1. 말단 직원들만 K개의 순서가 정해진 업무 가짐
2. 각 날짜에 남은 업무가 있으면, 말단 직원은 하나의 업무를 처리해서 상사에게 올림
3. 다른 직원들도, 대기하는 업무가 있는 경우 업무를 올라온 순서대로 하나 처리해서 상사에게 올림
4. 단, 홀수 번째 날짜에는 왼쪽 부하 직원이 올린 업무를, 짝수 번째 날짜에는 오른쪽 부하 직원이 올린 업무 처리
부서장이 처리한 일은 완료된 것.
업무 올리는 것은 모두 동시 진행.
그날 올린 업무는 다음날 상사가 처리.
*/

#include <iostream>
#include <queue>
using namespace std;

int H, K, R;
queue<int>q[11][1025];

int main() {
	cin >> H >> K >> R;
	int val;
	for (int i = 0; i < pow(2, H); i++) {
		cin >> val;
		q[H+1][i].push(val);
	}

	for (int t = 0; t <= R; t++) {

		for (int l = 0; l < H; l++) {
			int num = pow(2, l);
			if (!q[l][num].empty()) {
				if (t % 2 == 1) {
					//홀수 - 왼쪽 직원 처리
					//자식 계산 필요 num -> child
					int lchild = l;
					int task = q[l + 1][lchild].front();
					q[l + 1][lchild].pop();
					q[l][num].push(task);
				}
				else {
					//짝수 - 오른쪽 직원 처리
					//자식 계산 필요 num -> child
					int rchild = l;
					int task = q[l + 1][rchild].front();
					q[l + 1][rchild].pop();
					q[l][num].push(task);
				}
			}
		}
	}

	//부모에서 자식이 가진 일을 그냥 받아서 처리하는 방식으로?
}
