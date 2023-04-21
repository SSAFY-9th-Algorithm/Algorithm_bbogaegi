#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

struct MemoryPool {
    Node* nodes;
    bool* used;
    int size;
    int next_available;

    MemoryPool(int s) : size(s) {
        nodes = new Node[size];
        used = new bool[size];
        for (int i = 0; i < size; i++) {
            used[i] = false;
            nodes[i].next = &nodes[i+1];
        }
        nodes[size-1].next = nullptr;
        next_available = 0;
    }

    ~MemoryPool() {
        delete[] nodes;
        delete[] used;
    }

    Node* allocate() {
        if (next_available == size) {
            cout << "Memory pool is full" << endl;
            return nullptr;
        }
        Node* node = &nodes[next_available++];
        used[node-nodes] = true;
        return node;
    }

    void deallocate(Node* node) {
        if (node < nodes || node > &nodes[size-1]) {
            cout << "Node is not in the memory pool" << endl;
            return;
        }
        used[node-nodes] = false;
        node->next = &nodes[next_available];
        next_available = node - nodes;
    }

    bool is_allocated(Node* node) {
        return used[node-nodes];
    }
};

void insert(Node* head, MemoryPool& memory_pool, int data) {
    Node* node = memory_pool.allocate();
    node->data = data;
    node->next = head->next;
    head->next = node;
}

void remove(Node* head, MemoryPool& memory_pool, int data) {
    Node* prev = head;
    Node* curr = head->next;
    while (curr) {
        if (curr->data == data) {
            prev->next = curr->next;
            memory_pool.deallocate(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void print(Node* head) {
    Node* node = head->next;
    while (node) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

int main() {
    const int size = 10;
    MemoryPool memory_pool(size);
    Node head = {0, nullptr};

    insert(&head, memory_pool, 1);
    insert(&head, memory_pool, 2);
    insert(&head, memory_pool, 3);
    print(&head);
    remove(&head, memory_pool, 2);
    print(&head);

    return 0;
}
