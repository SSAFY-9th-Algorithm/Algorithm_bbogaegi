#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <cstring>
#define MAX_SIZE 1000
using namespace std;

template<typename T>
class Node {
	public:
		T data;
		Node<T> *next;
		Node(void): data(0), next(0) {}
		Node(T _data) : data(_data), next(0) {} 
};

template<typename T>
class Stack {
	private:
		Node<T> pool[MAX_SIZE];
		Node<T> *head;
		int _size;
		int idx;
	public:
		Stack(void) : _size(0), head(0), idx(0) {
			memset(pool, 0, sizeof(pool));
		}
		~Stack() {}
		bool empty() {
			return _size == 0;
		}
		int size() {
			return _size;
		}
		void push(T data) {
			pool[idx] = Node<T>(data);
			if (_size > 0)
				pool[idx].next = head;
			head = &pool[idx];
			_size++;
			idx++;
		}
		void pop() {
			head = head->next;
			_size--;
		}
		T top() {
			return head->data;
		}
		void print() {
			Node<T> *now = head;
			for (int i = 0; i < _size; i++) {
				cout << now->data << '\n';
				now = now->next;
			}
		}
};

#endif
