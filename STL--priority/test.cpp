#define _CRT_SECURE_NO_WARNINGS 1
#include"priority_queue.h"

int main()
{
	rxj::priority_queue<int,deque<int>,less<int>> q1;
	q1.push(1);
	q1.push(4);
	q1.push(2);
	q1.push(5);
	q1.push(9);
	q1.push(6);
	q1.push(7);
	//q1.pop();
	//cout << q1.top() << endl;
	//q1.pop();
	//cout << q1.top() << endl;
	//q1.pop();
	//cout << q1.top() << endl;
	//q1.pop();
	//cout << q1.top() << endl;
	//vector<int> v1;
	//v1.push_back(1);
	//v1.push_back(2);
	//v1.push_back(3);
	//v1.push_back(4);
	//v1.push_back(5);
	//v1.push_back(6);
	//v1.push_back(7);
	//v1.push_back(8);
	//v1.push_back(9);
	//rxj::priority_queue<int> q2(v1.begin(),v1.end());
	while (!q1.empty())
	{
		cout << q1.top() << endl;
		q1.pop();
	}
}