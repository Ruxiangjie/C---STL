#define _CRT_SECURE_NO_WARNINGS 1
#include<initializer_list>
#include<iostream>
#include<algorithm>//°üº¬find
#include"vector.h"

using namespace std;

template<class Container>
void Print(const Container& v)
{
	for (auto e : v)
	{
		cout << e << " ";
	}
}

void test1()
{
	rxj::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	v.insert(v.begin()+1,5);
	v.insert(v.begin() + 1, 4);
	v.insert(v.begin() + 1, 3);
	v.insert(v.begin() + 1, 2);
	v.erase(v.begin());
}

int main()
{
	test1();
	return 0;
}