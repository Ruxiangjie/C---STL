#pragma once
#include<iostream>
#include<vector>
#include<deque>
using namespace std;
namespace rxj
{
	template<class T>
	class less
	{
	public:
		bool operator()(const T& x, const T& y)
		{
			return x > y;
		}
	};
	template<class T>
	class greater
	{
	public:
		bool operator()(const T& x, const T& y)
		{
			return y > x;
		}
	};

	template<class T,class Container = vector<T>,class Compare = less<T>>
	class priority_queue
	{
	private:
		/*void adjust_up()
		{
			if (_con.size() == 1)
				return;
			else
			{
				size_t parents = (_con.size() - 2) / 2;                    
				size_t child = _con.size() - 1;
				while (child != 0&&_con[parents] < _con[child])
				{
					swap(_con[parents], _con[child]);
					child = parents;
					parents = (child - 1) / 2;
				}
			}
		}*/
		//void constructheap_down()
		//{
		//	int parent = (_con.size() - 1) / 2;
		//	while (parent>=0)//如果写while循环，就不要使用size_t类型的变量
		//	{
		//		adjust_down(parent);
		//		--parent;
		//	}
		//}

		void adjust_up(size_t child)
		{
			size_t parent = (child - 1) / 2;
			while (child>0)
			{
				if (com(_con[child],_con[parent]))
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		void adjust_down(size_t parent)
		{
			size_t child = parent * 2+1;
			while (child<_con.size())//只要有左孩子就可以去比较
			{
				if (child+1<_con.size()&&com(_con[child+1] , _con[child]))//先判断右孩子是否存在，再去访问右孩子
				{
					++child;
				}
				if (com(_con[child],_con[parent]))
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
	public:
		priority_queue() = default;
		/*template<class InputIterator>
		priority_queue(InputIterator first,InputIterator end)
		{
			InputIterator it = first;
			while (it != end)
			{
				_con.push_back(*it);
				++it;
			}
			constructheap_down();
		}*/
		template<class InputIterator>//这是真大神
		priority_queue(InputIterator begin, InputIterator end)
			:_con(begin, end)
		{
			for (int i = (_con.size() - 1) / 2;i >= 0;i--)
			{
				adjust_down(i);
			}
		}

		void push(const T& val)
		{
			_con.push_back(val);
			//向上建堆
			adjust_up(_con.size()-1);
		}

		void pop()
		{
			swap(_con[0],_con[_con.size()-1]);
			_con.pop_back();//我们要先把后面的那个元素删除以后，再去向下调整堆
			adjust_down(0);
		}
		const T& top() const
		{
			return _con[0];
		}
		bool empty()const
		{
			return _con.empty();
		}
	private:
		Container _con;
		Compare com;
	};
}