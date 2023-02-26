#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

/*
N x N 크기의 정사각형 모양의 방
밥을 빨리 먹기 위해 최대한 빠른 시간 내에 내려가야 함
방 안의 사람들은 P로 계단 입구를 S

이동 완료 시간은 모든 사람들이 계단을 내려가 아래 층으로 이동을 완료한 시간
	-> 계단 입구까지 이동 시간 + 계단을 내려가는 시간

#1. 계단 입구까지 이동 시간 = | PR - SR | + | PC - SC |
#2. 계단을 내려가는 시간: 계단 입구에 도착한 후부터 계단을 완전히 내려갈 때까지의 시간
	입구에 도착하고 1분 후부터 내려갈 수 있음
	계단 위에는 최대 3명까지만 올라가있을 수 있음
	이미 3명이 계단을 내려가고 있으면 그 중 한 명이 계단을 완전히 내려갈 때까지 계단 입구에서 대기

	계단마다 길이 K가 주어지며 계단에 올라간 후 완전히 내려가는 데 K분이 걸림
	초기 입력으로 주어지는 사람의 위치와 계단 입구의 위치는 서로 겹치지 않음
	1은 사람을, 2 이상은 계단의 입구를 나타내며 그 값은 계단의 길이를 의미

---------------------------------------------------------------------------------
설계
#1. 계단의 입구는 항상 2개 이므로 이 위치에서부터 각 사람들 사이의 거리를 구함
	=> Flood Fill
#2. 각 사람마다 두 계단을 이용하는 시간을 각각 구하되, 한 계단 당 3명의 사람만 있을 수 있음
	-> 시간이 제일 빨리 걸리는 순서로 계단에 집어넣기
	=> DFS?
*/
struct Node {
	int y;
	int x;
};

struct Person {
	int idx;
	int y;
	int x;
	int s1Cost; // 계단 1로 내려갔을 때의 비용
	int s2Cost; // 계단 2로 내려갔을 때의 비용
};

struct cmp1 {
	bool operator()(Person p1, Person p2) {
		return p1.s1Cost > p2.s1Cost;
	}
};

struct cmp2 {
	bool operator()(Person p1, Person p2) {
		return p1.s2Cost > p2.s2Cost;
	}
};

int N; // 방의 한 변의 길이 4 ~ 10
int people; // 사람의 수 1 ~ 10

Node stair[2]; // 계단의 입구는 반드시 2개, 위치 겹치지 x
int K; // 계단의 길이 2 ~ 10
int visited[10]; // 이 사람이 계단으로 진입했는가?
int mat[10][10];
Person person[10];
priority_queue<Person, vector<Person>, cmp1> s1;
priority_queue<Person, vector<Person>, cmp2> s2;

void reset() {
	memset(visited, 0, sizeof(visited));
	memset(stair, 0, sizeof(stair));
	memset(mat, 0, sizeof(mat));
	people = 0;
}

void input() {
	int sidx = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> mat[i][j];
			if (mat[i][j] == 0)
				continue;
			if (mat[i][j] == 1) {
				person[people] = {people, i, j, 0 };
				people++;
			}
			else if (mat[i][j] > 1)
				stair[sidx++] = { i, j };
		}
	}
	for (int i = 0; i < people; i++) {
		person[i].s1Cost = abs(stair[0].y - person[i].y) + abs(stair[0].x - person[i].x);
		person[i].s2Cost = abs(stair[1].y - person[i].y) + abs(stair[1].x - person[i].x);
		s1.push(person[i]);
		s2.push(person[i]);
	}
}
