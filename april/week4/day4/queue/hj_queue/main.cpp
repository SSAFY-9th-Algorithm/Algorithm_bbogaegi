#include "Queue.hpp"

int main() {
	Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	cout << "front " <<  q.front() << endl;
	cout << "back " <<  q.back() << endl;
	q.pop();
	cout << "front " <<  q.front() << endl;
	cout << "back " <<  q.back() << endl;
	q.push(100);
	cout << "front " <<  q.front() << endl;
	cout << "back " <<  q.back() << endl;
	cout << "size " << q.size() << endl;
}
