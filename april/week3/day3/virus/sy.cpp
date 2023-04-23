#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
using namespace std;
const int BUFSIZE = 101*101;

// queue안 쓰고는 어떻게 구현하지?
// ????

struct Node {
	int data;
	Node* next;
};

Node LIST[BUFSIZE];
Node HEAD[101];
int bcnt;

int N, M;

void push(int idx, int d) {
	Node* nd = &LIST[bcnt++];
	nd->data = d;

	nd->next = HEAD[idx].next;
	HEAD[idx].next = nd;
}

void bfs(int start) {
	int cnt = 0;
	// queue 준비
	queue<int> q;
	q.push(start);
	// visited 준비
	int visited[101] = { 0, };
	visited[start] = 1;

	while (!q.empty()){ 
		int now = q.front();
		q.pop();

		for (Node* node = HEAD[now].next; node; node = node->next) {
			if (visited[node->data])
				continue;
			visited[node->data] = 1;
			cnt++;
			q.push(node->data);
		}
	}
	printf("%d\n", cnt);
}

int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		push(a, b);
		push(b, a);
	}

	bfs(1);
	return 0;
}
