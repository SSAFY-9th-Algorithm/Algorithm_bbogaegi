#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class MemoryPool {
private:
    Node* pool;
    bool* used;
    int size;
    int next_available;

public:
    MemoryPool(int s) : size(s) {
        pool = new Node[size];
        used = new bool[size];
        for (int i = 0; i < size; i++) {
            used[i] = false;
            pool[i].next = &pool[i+1];
        }
        pool[size-1].next = nullptr;
        next_available = 0;
    }

    ~MemoryPool() {
        delete[] pool;
        delete[] used;
    }

    Node* allocate() {
        if (next_available == size) {
            cout << "Memory pool is full" << endl;
            return nullptr;
        }
        Node* node = &pool[next_available++];
        used[node-pool] = true;
        return node;
    }

    void deallocate(Node* node) {
        if (node < pool || node > &pool[size-1]) {
            cout << "Node is not in the memory pool" << endl;
            return;
        }
        used[node-pool] = false;
        node->next = &pool[next_available];
        next_available = node - pool;
    }

    bool is_allocated(Node* node) {
        return used[node-pool];
    }
};

class LinkedList {
private:
    Node* head;
    MemoryPool* memory_pool;

public:
    LinkedList(int size) {
        memory_pool = new MemoryPool(size);
        head = memory_pool->allocate();
        head->next = nullptr;
    }

    ~LinkedList() {
        Node* node = head;
        while (node) {
            Node* temp = node;
            node = node->next;
            memory_pool->deallocate(temp);
        }
        delete memory_pool;
    }

    void insert(int data) {
        Node* node = memory_pool->allocate();
        node->data = data;
        node->next = head->next;
        head->next = node;
    }

    void remove(int data) {
        Node* prev = head;
        Node* curr = head->next;
        while (curr) {
            if (curr->data == data) {
                prev->next = curr->next;
                memory_pool->deallocate(curr);
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void print() {
        Node* node = head->next;
        while (node) {
            cout << node->data << " ";
            node = node->next;
        }
        cout << endl;
    }
};
