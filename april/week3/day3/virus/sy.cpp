#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
const int BUFSIZE = 101 * 101;

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
	int cnt = 0, sp = 0, ep = 0;
	// queue 준비
	int queue[101] = { 0, };
	queue[sp++] = start;
	// visited 준비
	int visited[101] = { 0, };
	visited[start] = 1;

	while (sp > ep) {
		int now = queue[ep++];

		for (Node* node = HEAD[now].next; node; node = node->next) {
			if (visited[node->data])
				continue;
			visited[node->data] = 1;
			cnt++;
			queue[sp++] = node->data;
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
