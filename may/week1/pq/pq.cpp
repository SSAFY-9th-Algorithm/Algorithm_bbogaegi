#include <iostream>
using namespace std;

const int MAX_SIZE = 10000;

struct PriorityQueue {
    int heap[MAX_SIZE];
    int size = 0;

    void heapifyUp(int index) {
        if (index == 0) {
            return;
        }

        int parent = (index - 1) / 2;

        if (heap[index] > heap[parent]) {
            swap(heap[index], heap[parent]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int largest = index;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

    void push(int value) {
        heap[size++] = value;
        heapifyUp(size - 1);
    }

    int top() {
        return heap[0];
    }

    void pop() {
        heap[0] = heap[--size];
        heapifyDown(0);
    }

    bool empty() {
        return size == 0;
    }
};

int main() {
    PriorityQueue pq;

    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.push(1);

    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }

    cout << endl;

    return 0;
}
