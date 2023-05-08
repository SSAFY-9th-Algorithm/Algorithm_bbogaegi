#include "PriorityQueue.hpp"

int main(void) {
	PriorityQueue<int> pq;

	pq.push(1);
	pq.push(100);
	pq.push(3);
	pq.push(2);
	pq.push(4);
	pq.push(5);
	pq.push(-1);
	pq.push(10);
	cout << pq.top() << endl;
	cout << pq.size() << endl;

	while (!pq.empty()) {
		cout << "before pop" << endl;
		cout << pq.top() << endl;
		cout << pq.size() << endl << endl;
		pq.pop();
	}
	cout << "size : " << pq.size() << endl;
}
