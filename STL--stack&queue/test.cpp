#define _CRT_SECURE_NO_WARNINGS 1
#include"stack.h"
#include"queue.h"
int main()
{
	rxj::stack<int, vector<int>> st1;
	st1.push(1);
	st1.push(2);
	st1.push(3);
	st1.push(4);
	st1.push(5);
	st1.push(6);
	st1.pop();
	st1.pop();
	rxj::queue<int> q1;
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	q1.push(5);
	q1.push(6);
	q1.pop();
	q1.pop();
	return 0;
}