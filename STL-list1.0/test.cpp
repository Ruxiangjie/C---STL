#define _CRT_SECURE_NO_WARNINGS 1
#include"list.h"
#include<iostream>
using namespace std;
namespace rxj
{
	template<class T>
	void Print(const list<T>& lt)
	{
		typename list<T>::const_iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << endl;
			++it;
		}
	}

	void test()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		Print<int>(lt);
	}
}
int main()
{
	rxj::test();
	return 0;
}