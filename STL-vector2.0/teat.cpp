#define _CRT_SECURE_NO_WARNINGS 1
#include"vector.h"
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
	rxj::vector<int> v1;
	v1.resize(7);
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	Print(v1);
}
int main()
{
	test1();
	return 0;
}