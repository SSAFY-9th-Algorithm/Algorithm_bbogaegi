#include <stdio.h>
#include <algorithm>
using namespace std;

struct Node {
    int prev;
    int next;
    int val;
};

const int NODE_SIZE = 30000;

// TEST command
const int PUSH_BACK = 0;
const int PUSH_FRONT = 1;
const int INSERT = 2;
const int POP_BACK = 3;
const int POP_FRONT = 4;
const int ERASE = 5;

int test_cmd[NODE_SIZE][3];

struct MY_LIST {
    int HEAD = NODE_SIZE;
    int TAIL = NODE_SIZE + 1;
    int pos;
    Node node[NODE_SIZE + 2];

    MY_LIST() {
        pos = 0;
        // 가장 처음의 다음은 끝
        node[HEAD].next = TAIL;
        // 가장 끝의 이전은 처음
        node[TAIL].prev = HEAD;
    }

    void push_back(int data) {
        int prev = node[TAIL].prev;
        int next = node[prev].next; // TAIL

        // 해당 위치에 데이터 삽입
        node[pos].val = data;
        // 데이터를 넣은 위치의 이전은 prev
        // prev의 다음은 pos
        node[pos].prev = prev;
        node[prev].next = pos;
        // 현재 위치의 다음은 next
        // next의 이전은 pos
        node[pos].next = next;
        node[next].prev = pos;

        pos++;
    }

    void push_front(int data) {
        int next = node[HEAD].next;
        int prev = node[next].prev; // HEAD

        // 해당 위치에 데이터 삽입
        node[pos].val = data;
        // 데이터를 넣은 위치의 이전은 prev
        // prev의 다음은 pos
        node[pos].prev = prev;
        node[prev].next = pos;
        // 현재 위치의 다음은 next
        // next의 이전은 pos
        node[pos].next = next;
        node[next].prev = pos;

        pos++;
    }

    void insert(int p, int data) {
        int next = node[HEAD].next;

        for (int i = 0; i < p; i++) {
            next = node[next].next;
        }

        int prev = node[next].prev;

        // 해당 위치에 데이터 삽입
        node[pos].val = data;
        // 데이터를 넣은 위치의 이전은 prev
        // prev의 다음은 pos
        node[pos].prev = prev;
        node[prev].next = pos;
        // 현재 위치의 다음은 next
        // next의 이전은 pos
        node[pos].next = next;
        node[next].prev = pos;

        pos++;
    }

    void pop_back() {
        int tgt = node[TAIL].prev;

        int prev = node[tgt].prev;
        int next = node[tgt].next;

        node[prev].next = next;
        node[next].prev = prev;
    }

    void pop_front() {
        int tgt = node[HEAD].next;

        int prev = node[tgt].prev;
        int next = node[tgt].next;

        node[prev].next = next;
        node[next].prev = prev;
    }

    void erase(int p) {
        int tgt = node[HEAD].next;

        for (int i = 0; i < p; i++) {
            tgt = node[tgt].next;
        }
        int prev = node[tgt].prev;
        int next = node[tgt].next;

        node[prev].next = next;
        node[next].prev = prev;
    }
};

MY_LIST my_list;

int main() {
    // test case 만들기
    int cur_size = 0;
    for (int i = 0; i < NODE_SIZE; i++) {
        if (i < NODE_SIZE / 3) {
            test_cmd[i][0] = rand() % 2;
        }
        else
            test_cmd[i][0] = rand() % 6;

        switch (test_cmd[i][0]){
        case PUSH_BACK:
        case PUSH_FRONT: {
            test_cmd[i][1] = rand();
            cur_size++;
            break;
        }
        case INSERT: {
            test_cmd[i][1] = rand() % cur_size; // p
            test_cmd[i][2] = rand(); // data
            cur_size++;
            break;
        }
        case POP_BACK:
        case POP_FRONT: {
            cur_size--;
            break;
        }
        case ERASE: {
            test_cmd[i][1] = rand() % cur_size; // p
            cur_size--;
            break;
        }
        default:
            break;
        }
    }

    for (int i = 0; i < NODE_SIZE; i++) {
        switch (test_cmd[i][0]){
        case PUSH_BACK: {
            my_list.push_back(test_cmd[i][1]);
            break;
        }
        case PUSH_FRONT: {
            my_list.push_front(test_cmd[i][1]);
            break;
        }
        case INSERT: {
            my_list.insert(test_cmd[i][1], test_cmd[i][2]);
            break;
        }
        case POP_BACK: {
            my_list.pop_back();
            break;
        }
        case POP_FRONT: {
            my_list.pop_front();
            break;
        }
        case ERASE: {
            my_list.erase(test_cmd[i][1]);
            break;
        }
        default:
            break;
        }
    }


    return 0;
}
