#pragma once
#include<iostream>
#include<cassert>
using namespace std;
namespace rxj
{
	
	template<typename T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		//vector() 
		//	/*:_start(nullptr)
		//	,_finish(nullptr)
		//	,_end_of_storage(nullptr)*///因为我在private里面已经把这几个值弄上了初始值，所以我把注释了
		//{
		//	
		//}
		//因为我们已经写了拷贝构造了，所以编译器不会生成默认构造函数，所以默认构造函数对我们来说就是很重要的了，c++给了一个方案就是vector() = default
		//强制编译器生成默认构造函数
		vector() = default;//强制编译器生成默认构造

		//拷贝构造函数
		vector(const vector<T>& v)
		{
			reserve(v.capacity());
			for (auto& e : v)
			{
				push_back(e);
			}
		}
		//使用initializer_list构造
		vector(initializer_list li)
		{
			reserve(li.size());
			for (auto e : li)
			{
				push_back(e);//e直接得到了li里面的数据
			}
		}

		//迭代器构造函数
		//我们要构造一个可以使用任意容器迭代器初始化的构造函数
		//前提是解引用得到的底层数据和我们vector<>里面定义的类型一样
		//比如我们传入的是一个string的迭代器，解引用得到的就是char，可以进行转换，转换成int
		template<class InputIterator>
		vector(InputIterator first,InputIterator end)
		{
			while (first != end)
			{
				push_back(*first);//这里一样，我们传入的参数是解引用以后得到的
				++first;
			}
		}

		//赋值，现代写法
		/*T& operator=()
		{

		}*/

		void swap(const T v)
		{
			_start = v._start;
			_finish = v._finish;
			_end_of_storage = v._end_of_storage;
		}

		//n个value初始化的构造
		vector(size_t n, T val = T())
		{
			reserve(n,val);
		}
		~vector()
		{
			if (_start)//看这个vector是否为空
			{
				delete[]_start;
				_start = _finish = _end_of_storage = nullptr;
			}
		}
		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}
		
		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}

		size_t size() const//记得加const
		{
			return _finish - _start;
		}

		size_t capacity() const//记得加const，这里的const修饰的是this指针
		{
			return _end_of_storage - _start;
		}

		void reserve(size_t n)//这个函数在声明的时候，外面不能+const，否则后续我们对_start的修改就无从谈起了
		{
			if (n < capacity())
			{
				return;
			}
			else
			{
				T* tmp = new T[n];//这里使用new的时候，后面的[]不能打成()了！！！
				size_t old_size = size();
				/*while ()
				{

				}*///这里我知道你想用while把原vector里面的内容拷贝到新的vector，但是我们有更好的方法
				if (_start)//这里我们只需要看原数组里面有没有元素，如果没有，_start就是nullptr，我们就不需要管了
				{
					for (size_t i = 0; i < old_size; ++i)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;//这里我们需要把原数组的空间释放了
				}
				//最后一点就是记得把_start,_finish,_end_of_storage重新搞一下
				_start = tmp;
				_finish = _start + old_size;//这里我们需要注意一下，1、finish需要更新，因为需要指向新数组的那个位置
				//2、我们不能加上size()，因为这里使用size的话，会用_finish-_start，但是_start的位置已经改变了
				_end_of_storage = _start + n;
			}
		}
		void clear()
		{
			_finish = _start;
		}
		void resize(size_t n, T val = T())//这里我们传入默认构造，c++的内置类型也有构造函数
		{
			if (n > size())//n应该和size比较，n>size就是说要插入数据，但是不知道是否要扩容，我们可以直接使用reserve
			{
				reserve(n);//确保有足够的空间去扩容
				while (_finish != _start+n)
				{
					*_finish = val;
					++_finish;
				}
			}
			else//反义词就是n<=size
			{
				_finish = _start + n;//这一步是进行缩容
			}
		}

		
		void push_back(const T& x)//这里的参数我们要使用引用，而且需要使用const！！
		{
			if (_end_of_storage==_finish)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);//使用reserve扩容的时候我们要检查是否为空，然后决定扩多少
			}
			*_finish = x;
			++_finish;
		}
		//赋值运算符重载
		const T& operator [](size_t n)const//如果传入的是一个不可修改的对象，那么返回值也要是一个不可修改的引用
		{
			assert(n < size());//这里的比较，应该是实际的元素个数
			return *(_start + n);
		}

		void pop_back()
		{
			assert(!empty());
			--_finish;
		}

		bool empty() const
		{
			return(_start == _finish);
		}

		iterator insert(iterator pos,const T& x)
		{
			assert(pos>=_start&&pos<=_finish);
			if (_finish == _end_of_storage)//先检查内存是否够，内存不够就需要扩容，而且扩容有一个迭代器失效的问题
			{
				//在寻找相对位置的时候要注意两点：1、我们只有在需要扩容的时候才需要去找相对位置 2、length的计算和pos的重新赋值我们都要在这个扩容函数里面完成
				size_t length = pos - _start;
				//pos会失效，我们要找相对位置

				reserve(capacity() == 0 ? 4 : capacity() * 2);//这里我就聪明了，我不会使用_end_of_capacity去比较了
				pos = _start + length;
				//_end_of_storage *= 2;这一步是多余的
			}
			iterator end = _finish-1;
			while (end >= pos)
			{
				*(end+1) =*end;//这里我们要赋值的不是地址而是地址里面的元素
				--end;
			}
			*pos = x;
			++_finish;
			return pos;//为了防止迭代器失效，给用户返回一个有用的迭代器
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);
			iterator it = pos+1;
			while (it < _finish)
			{
				*(it-1) = *it;//我们要更改的值是it里面的值
				++it;
			}
			--_finish;
			return pos;
		}

	private:
		T* _start = nullptr;
		T* _finish = nullptr;
		T* _end_of_storage = nullptr;
	};
}
