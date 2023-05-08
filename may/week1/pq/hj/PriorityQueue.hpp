#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <iostream>
#include <cstring>
using namespace std;

#define MAX_SIZE 1000

template<typename T>
class PriorityQueue {
private:
    T pool[MAX_SIZE];
    int _size;
public:
    PriorityQueue(void) : _size(0) {
        memset(pool, 0, sizeof(pool));
    }
    bool empty() {
        return _size == 0;
    }
    int size() {
        return _size;
    }
    void push(T data) {
        _size++;
        int now = _size;
        pool[now] = data;
        if (now < 2)
            return;
        int parent = now / 2;
        while (parent > 0 && pool[parent] < pool[now]) {
            int temp = pool[parent];
            pool[parent] = pool[now];
            pool[now] = temp;
            now = parent;
            parent = now / 2;
        }
    }
    T top() {
        return pool[1];
    }
    void pop() {
        pool[1] = pool[_size];
        _size--;
        int now = 1;
        int lchild = now * 2;
        int rchild = lchild + 1;
        while ((lchild <= _size && pool[now] < pool[lchild]) || (rchild <= _size && pool[now] < pool[rchild])) {
            if (pool[rchild] < pool[lchild]) {
                int temp = pool[now];
                pool[now] = pool[lchild];
                pool[lchild] = temp;
                now = lchild;
            }
            else {
                int temp = pool[now];
                pool[now] = pool[rchild];
                pool[rchild] = temp;
                now = rchild;
            }
            lchild = now * 2;
            rchild = lchild + 1;
        }
    }
};

#endif
