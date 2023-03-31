#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <unordered_map>
using namespace std;

// 설계 
// Box : id, weight, belt : 몇 번 벨트에 있나, prev, next
// belt 
// broken : 고장 여부, head, tail
// um  
// key : id
// value : Box
// 더블 링크드리스트 구현 문제
// 이게 왜 되는걸까


struct Box {
	int id, w, belt;
	Box* prev;
	Box* next;

	Box() {
		id = -1, w = -1, belt = -1;
		prev = NULL, next = NULL;
	}
};

struct Belt {
	int broken;
	Box* head;
	Box* tail;

	Belt() {
		broken = 0;
		head = new Box();
		tail = new Box();
		head->next = tail, tail->prev = head;
		tail->next = NULL, head->prev = NULL;
	}
};

Box box[100000];
Belt belt[10];
int q, qry, n, m;
unordered_map<int, Box*> um;

bool empty(int idx) {
	// head의 다음이 tail이면 비었다!
	return belt[idx].head->next == belt[idx].tail;
}

void push_back(int idx, Box* b) {
	um[b->id] = b;

	// tail의 앞이 가장 마지막
	// next는 tail
	Box* prev = belt[idx].tail->prev;
	Box* next = belt[idx].tail;

	// 내가 넣을 값의 앞은 prev
	// 내가 넣을 값의 뒤는 next
	b->prev = prev;
	b->next = next;

	// prev의 다음은 내가 넣을 값 
	// 뒤에 넣는 거니까
	prev->next = b;
	// next의 이전값도 내가 넣을값
	next->prev = b;
}

void pop_front(int idx) {
	// 해당 벨트가 비었으면 return
	if (empty(idx))
		return;
	// 이게 내가 빼야할 값
	// 가장 앞에 있는 값
	Box* now = belt[idx].head->next;
	// 키를 지워주고
	um.erase(now->id);

	// 앞을 삭제하는 것
	// head 가 prev
	// head의 다음 다음이 next
	// 난 head 다음, 즉, 가장 앞의 값을 지울거니까!
	Box* prev = belt[idx].head;
	Box* next = belt[idx].head->next->next;

	prev->next = next;
	next->prev = prev;

	now->prev = NULL;
	now->next = NULL;
}

// 공장 설립 
void q100() {
	
	scanf("%d %d", &n, &m);
	int id[100000];
	int w[100000];
	int de = 1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &id[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &w[i]);
	}

	int idx = 0;
	// m개의 벨트에 물건을 넣을건데
	// n/m개씩 들어간다
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n / m; j++) {
			box[idx].id = id[idx];
			box[idx].w = w[idx];
			box[idx].belt = i;

			push_back(i, &box[idx]);

			idx++;
		}
	}
}

// 물건 하차 -> 가장 앞에있는 물건이 w보다 작으면 뺀다
int q200() {
	int sum = 0;
	int w;
	scanf("%d", &w);

	for (int i = 0; i < m; i++) {
		// 비었거나 고장났으면 continue
		if (empty(i) || belt[i].broken)
			continue;
		Box* now = belt[i].head->next;
		// 입력받은 무게보다 작으면 하차
		if (now->w <= w) {
			sum += now->w;
			pop_front(i);
		}
		// 아니면 뒤로 보낸다
		else {
			pop_front(i);
			push_back(i, now);
		}
	}

	return sum;
}

// 물건 제거
int q300() {
	int id;
	scanf("%d", &id);

	// 해당 id를 가진 물건이 없다면 -1 return
	if (um.find(id) == um.end())
		return -1;
	// 있다면 지우자!
	Box* now = um[id];
	Box* prev = now->prev;
	Box* next = now->next;

	prev->next = next;
	next->prev = prev;

	now->prev = NULL;
	now->next = NULL;

	// key 값 삭제
	um.erase(id);
	return id;
}

// 물건 확인
int q400() {
	int id;
	scanf("%d", &id);

	// 해당 id를 가진 물건이 없다면 -1 return
	if (um.find(id) == um.end())
		return -1;
	// 있다면 벨트 번호 출력
	Box* now = um[id];
	
	Box* prev = now->prev;
	Box* start = belt[now->belt].head->next;
	Box* end = belt[now->belt].tail->prev;

	// 상자가 있는 경우, 해당 상자 위에 있는 모든 상자를 전부 앞으로 가져온다
	// 순서 유지
	if (now != start) {
		now->prev = belt[now->belt].head;
		belt[now->belt].head->next = now;

		start->prev = end;
		end->next = start;

		prev->next = belt[now->belt].tail;
		belt[now->belt].tail->prev = prev;
	}
	return now->belt + 1;
}

// 벨트 고장
int q500() {
	int b_num;
	scanf("%d", &b_num);
	b_num--;
	// 이미 고장났으면 -1 return
	if (belt[b_num].broken)
		return -1;
	// 아니면 고장났다
	belt[b_num].broken = 1;
	// 비어있지 않으면
	if (!empty(b_num)) {
		int tgt = (b_num + 1) % m;
		// 고장나지 않은 벨트를 찾는다
		while (belt[tgt].broken)
		{
			tgt = (tgt + 1) % m;
		}
		// 고장나지 않은 벨트의 tail의 prev
		Box* prev = belt[tgt].tail->prev;
		// 고장난 벨트의 head의 다음에서 시작
		Box* start = belt[b_num].head->next;
		// 고장난 벨트의 tail의 앞에서 끝
		Box* end = belt[b_num].tail->prev;

		// 물건을 옮기자
		for (auto i = start; i != belt[b_num].tail; i = i->next)
			i->belt = tgt;

		// 고장나지 않은 벨트의 뒤에 고장난 벨트의 시작 연결
		prev->next = start;
		// 고장난 벨트의 시작의 이전은 고장나지 않은 벨트의 끝과 연결
		start->prev = prev;

		// end 뒤에 tail, tail 앞에 end
		end->next = belt[tgt].tail;
		belt[tgt].tail->prev = end;

		// 고장난 벨트를 치우자!
		belt[b_num].head->next = belt[b_num].tail;
		belt[b_num].tail->prev = belt[b_num].head;
	}
	return b_num + 1;
}

int main() {
	scanf("%d", &q);

	while (q--)
	{
		scanf("%d", &qry);
		// 공장 설립
		if (qry == 100)
			q100();
		// 물건 하차
		else if (qry == 200) 
			printf("%d\n", q200());
		
		// 물건 제거
		else if (qry == 300) 
			printf("%d\n", q300());
		
		// 물건 확인
		else if (qry == 400)
			printf("%d\n", q400());
		// 벨트 고장
		else if (qry == 500) 
			printf("%d\n", q500());
	}

	return 0;
}
