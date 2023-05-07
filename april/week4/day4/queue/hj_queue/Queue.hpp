#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <cstring>

using namespace std;

#define MAX_SIZE 1000

template <typename T>
class Node {
	public:
		T data;
		Node<T> *prev;
		Node<T> *next;
		Node(void) : data(0), prev(0), next(0) {}
		Node(T _data) : data(_data), prev(0), next(0) {}
};

template <typename T>
class Queue {
	private:
		Node<T> pool[MAX_SIZE];
		Node<T> *head;
		Node<T> *tail;
		int _size;
		int idx;
	public:
		Queue(void) : _size(0), idx(0) {
			memset(pool, 0, sizeof(pool));
			head = new Node<T>();
			tail = new Node<T>();
			head->next = tail;
			tail->prev = head;
		}
		~Queue() {
			delete head;
			delete tail;
		}
		void push(T data) {
			pool[idx] = Node<T>(data);
			pool[idx].prev = tail->prev;
			pool[idx].next = tail;
			tail->prev->next = &pool[idx];
			tail->prev = &pool[idx];
			_size++;
			idx++;
		}
		void pop() {
			Node<T> *target = head->next;
			target->next->prev = head;
			head->next = target->next;
			_size--;
		}
		bool empty() {
			return _size == 0;
		}
		T& front() {
			return head->next->data;
		}
		T& back() {
			return tail->prev->data;
		}
		int size() {
			return _size;
		}
};


#endif
