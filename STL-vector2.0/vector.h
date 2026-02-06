#pragma once
#include<initializer_list>
#include<utility>
#include<iostream>
#include<cassert>
//茹相杰新写的vector
using namespace std;
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
			while (it != end)
			{
				push_back(*it);
				++it;
			}
		}
		//构造函数3
		vector(initializer_list<T> li)
		{
			reserve(li.size());
			for (auto e : li)
			{
				push_back(e);//e直接得到了li里面的数据
			}
		}
		//拷贝构造函数
		//传统写法
		//vector(const vector<T>& v)
		//{
		//	_start = new T[v.capacity()];
		//	for (size_t i = 0;i < v.size();i++)
		//	{
		//		_start[i] = v[i];
		//	}
		//	_finish = _start+v.size();//有效元素个数
		//	_end_of_storage = _start + v.capacity();

		//}
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
		vector<T>& operator=(const vector<T>& v)
		{
			if (this != &v)//防止连续赋值
			{
				delete[] _start;//先释放原有空间里面的值
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
		vector<T>& operator=(vector<T> v)
		{
			(*this).swap(v);
			return *this;
		}
		void swap(vector<T>& v)//这里需要使用引用 
		{
			::swap(_start,v._start);
			::swap(_finish, v._finish);
			::swap(_end_of_storage, v._end_of_storage);
		}
		//析构函数
		~vector()
		{
			if (_start)
			{
				delete[]_start;
				_start = nullptr;
				_finish = nullptr;
				_end_of_storage = nullptr;
			}
		}
		//元素个数的函数
		size_t size()const
		{
			return _finish-_start;
		}
		size_t capacity()const
		{
			return _end_of_storage - _start;
		}
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t len = size();
				T* tmp = new T[n];
				if (_start)//我们要检查原数组有没有元素，没有的话就不需要管了
				{
					for (size_t i = 0;i < len; i++)
					{
						tmp[i] = _start[i];
					}
					delete[]_start;
				}
				_start = tmp;
				_finish = _start + len;
				_end_of_storage = _start + n;
			}
		}
		void resize(size_t n,T val = T())
		{
			if (n > size())
			{
				reserve(n);
				while (_finish != _start+n)
				{
					*_finish = val;
					++_finish;
				}
			}
			else
			{
				_finish = _start + n;
			}
		}
		bool empty()const//需要使用const修饰
		{
			return (_start == _finish);
		}
		//修改容器内容的相关函数
		void push_back(const T& v)//传进来的元素类型要注意一下
		{
			if (_finish == _end_of_storage)
			{
				//capacity()==0?reserve(4) : reserve(capacity() * 2);
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}
			*_finish = v;
			++_finish;
		}
		void pop_back()
		{
			if (!empty())
			{
				--_finish;
			}
		}
		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start && pos <= _finish);
			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;//药剂一下相对位置
				//capacity()==0?reserve(4) : reserve(capacity() * 2);
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;
			}
			iterator it = _finish;
			while (it > pos)
			{
				*it = *(it - 1);
				--it;
			}
			*pos = val;
			++_finish;
			return pos;
		}
		iterator erase(iterator pos)
		{
			assert(pos >= _start && pos < _finish);
			iterator it = pos;
			while (it < _finish - 1)
			{
				*it = *(it + 1);
				++it;
			}
			--_finish;
			return pos;
		}
		//访问容器相关内容函数
		const T& operator[](size_t n)const
		{
			assert(n < size());
			return *(_start + n);
		}
		T& operator[](size_t n)
		{
			assert(n < size());
			return *(_start + n);
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