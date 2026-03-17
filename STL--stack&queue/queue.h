#pragma once
#include<vector>
#include<list>
using namespace std;
namespace rxj
{
	template<class T,class Container = list<T>>//队列经常头删，所以我们默认使用list
	class queue
	{
	public:
		void push(const T& val)
		{
			_con.push_back(val);
		}
		void pop()
		{
			_con.pop_front();//vector没有pop_front，所以容器不能传vector
		}
		bool empty()const
		{
			return _con.empty();
		}
		const T& front()const
		{
			return _con.front();
		}
		const T& back()const
		{
			return _con.back();
		}
		size_t size()const
		{
			return _con.size();
		}
		void swap(queue<T,Container>& q)
		{
			_con.swap(q._con);
		}
	private:
		Container _con;
	};
}
