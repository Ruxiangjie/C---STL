#pragma once
#include<initializer_list>
//茹相杰新写的vector
namespace rxj
{
	template<class T>
	class vector
	{
		typedef T* iterator;
		typedef const T* const_iterator;
	public:
		//构造函数1
		vector() = default;//强制生成默认构造函数
		//构造函数2
		template<class Inputiterator>
		vector(Inputiterator first, Inputiterator end)
		{
			Inputiterator it = first;
			while (first != end)
			{
				push_back(*it);
				++it;
			}
		}
		//构造函数3
		vector(initializer_list li)
		{
			reserve(li.size());
			for (auto e : li)
			{
				push_back(e);//e直接得到了li里面的数据
			}
		}
		//拷贝构造函数
		//传统写法
		vector(const vector<T>& v)
		{
			_start = new T[v.capacity()];
			for (size_t i = 0;i < v.size();i++)
			{
				_start[i] = v[i];
			}
			_finish = _start+v.size();//有效元素个数
			_end_of_storage = _start + v.capacity();

		}
		//现代写法
		vector(const vector<T>& v)
		{
			reserve(v.capacity());
			for (auto& e : v)//这里记得使用语法糖
			{
				push_back(e);
			}
		}
		//赋值运算符重载
		//传统写法
		vector<T>& operator=(cosnt vector<T>& v)
		{
			if (this != &v)//防止连续赋值
			{
				delete[] _strat;//先释放原有空间里面的值
				_start = new T[v.capacity()];
				for (size_t i = 0;i < v.size();i++)
				{
					_start[i] = v[i];//这里vector的[]运算符重载需要自己实现
				}
				_finish = _start + v.size();
				_end_of_storage = _start + v.capacity();
			}
			return *this;//支持连续赋值
		}
		//现代写法
		swap()
		//元素个数的函数
		size_t size()const
		{
			return _finish-_start;
		}
		size_t capacity()const
		{
			return _end_of_storage - _start;
		}
		//迭代器相关函数
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin()const
		{
			return _start;
		}
		const_iterator end()const
		{
			return _finish;
		}

	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _end_of_storage = nullptr;
	};
}