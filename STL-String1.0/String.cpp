#define _CRT_SECURE_NO_WARNINGS 1
#include"String.h"
namespace rxj//多个文件可以定义同一个命名空间，会被认为是合并了
{
	string::string(const char* str)
		:_size(strlen(str))//strlen和sizeof不同的是sizeof是在编译的时候实现的，strlen是在运行时调用的，这个成本太高
	{
		_capacity=_size;
		_str=new char[_size+ 1];//这里我们要开_size+1个空间
		strcpy(_str, str);//这里我们不能交换指针，因为我们的目的是把str里面的东西拷贝给_str。因为str指向的地方是一个常量串，我们就没办法修改了
		//memcpy(_str, str, _size);
	} 
	const char* string::c_str() const
	{
		return _str;
	}
	string::~string()
	{
		delete[]_str;
		_str = nullptr;//?
		_size = _capacity = 0;
	}
	size_t string::size()const
	{
		return _size;
	}
	const char& string::operator[](size_t i) const
	{
		assert(i >= 0 && i < _size);
		return _str[i];//返回的是什么类型，主要是看函数的头，而不是说你堂而皇之的写一个 &_str[i]，这是不对的
	}
	char& string::operator[](size_t i)
	{
		assert(i >= 0 && i < _size);
		return _str[i];
	}
	string::iterator string::begin()
	{
		return _str;
	}
	string::iterator string::end()
	{
		return _str + _size;
	}
	string::const_iterator string::begin()const
	{
		return _str;
	}
	string::const_iterator string::end()const
	{
		return _str + _size;
	}
	void string::push_back(const char ch)
	{
		if (_size >= _capacity)
		{
			size_t newcapacity = _capacity == 0 ? 4 : 2 * _capacity;
			reserve(newcapacity);
		}
		_str[_size] = ch;
		++_size;
		_str[_size] = '\0';
	}
	void string::append(const char* str)
	{
		size_t len = strlen(str);
		if (_size + len > _capacity)//因为括号里面的_size,len,_capacity都不包含'\0'，所以运算的时候都不需要+1
		{
			size_t newcapacity = _capacity * 2 > (_size + len) ? _capacity * 2 : (_size + len);
			reserve(newcapacity);//这里为什么传的是newcapacity而不是newcapacity+1呢？因为我们在实现reserve的时候已经考虑了\0，开辟空间的时候已经多开一个了
		}
		memcpy(_str + _size, str, len + 1);
		_size += len;
	}
	void string::reserve(size_t n)
	{
		if (n > _capacity)//保证他至少不缩容
		{
			char* tmp = new char[n+1];//为什么我们要+1呢？我们期望存n个有效字符，但是'\0'也是要存里面的
			memcpy(tmp, _str, _size+1);
			delete[] _str;
			_str = tmp;
			_capacity = n;
		}
	}
	string& string::operator+=(char ch)
	{
		push_back(ch);
		return *this;
	}
	string& string::operator+=(const char* str)
	{
		append(str);
		return *this;
	}
	ostream& operator<<(ostream& out, const string& s)
	{
		/*for (auto ch : s)
		{
			out << ch;
		}*/
		for (size_t i = 0;i < s.size();i++)
		{
			out << s[i];
		}
		return out;
	}
	string& string::insert(size_t pos,const char* str)
	{
		assert(pos <= _size);//因为size_t不会为负数，所以我们在判断的时候，可以取巧
		//这一段我们在判断内存是否够用的时候可以直接使用append的逻辑
		size_t len = strlen(str);
		if (len == 0)
			return *this;
		if (_size + len > _capacity)//因为括号里面的_size,len,_capacity都不包含'\0'，所以运算的时候都不需要+1
		{
			size_t newcapacity = _capacity * 2 > (_size + len) ? _capacity * 2 : (_size + len);
			reserve(newcapacity);//这里为什么传的是newcapacity而不是newcapacity+1呢？因为我们在实现reserve的时候已经考虑了\0，开辟空间的时候已经多开一个了
		}
		size_t end = _size + 1;
		while (end > pos)
		{
			_str[end - 1 + len] = _str[end - 1];
			--end;
		}
		memcpy(_str + pos, str, len);
		_size += len;
		return *this;
	}
	string& string::insert(size_t pos,char ch)
	{
		assert(pos <= _size);//因为size_t不会为负数，所以我们在判断的时候，可以取巧
		
		//判断这一段是否扩容我们直接调用push_back的逻辑
		if (_size >= _capacity)
		{
			size_t newcapacity = _capacity == 0 ? 4 : 2 * _capacity;
			reserve(newcapacity);
		}

		//在挪动数据的时候我们要从后往前挪
		size_t end = _size+1;//把'\0'的位置给end
		while (end > pos)
		{
			_str[end] = _str[end-1];//这一段极其重要，我们把'\0'的位置给了end，我们要把\0带着一起往后挪动
			--end;
		}
		_str[pos] = ch;
		++_size;
		return *this;
	}
	string& string::erase(size_t pos, size_t len)
	{
		assert(pos < _size);//要删除的数据大于后面的字符
		if (len == npos||len>=(_size-pos))//前闭后开相减就是个数
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			size_t i = pos+len;
			memmove(_str + pos, _str + i, _size - i + 1);//会动态调整复制的方向
			_size -= pos;
		}
		return *this;
	}
	void string::pop_back()
	{
		assert(_size > 0);
		_str[_size - 1] = '\0';
		_size -= 1;
	}
	size_t string::find(char ch, size_t pos)const
	{
		for (size_t i = pos;i < _size;i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return npos;//注意这里的返回值是npos
	}
	size_t string::find(const char* str, size_t pos)const
	{
		const char* p1 = strstr(_str + pos, str);
		if (p1 == nullptr)
		{
			return npos;
		}
		else//指针如何转化为下标？
		{
			return p1 - _str;
		}
	}
	string string::substr(size_t pos, size_t len)const
	{
		if (len == npos || pos + len >= _size)
		{
			len = _size - pos;
		}
		string ret;
		ret.reserve(len);
		for (size_t i = 0;i < len;i++)
		{
			ret += _str[pos + i];
		}
		return ret;
	}
	string::string(const string& s)
	{
		(*this) = new char[s._size + 1];
		memcpy(_str, s._str, s._capacity + 1);
		_size = s._size;
		_capacity = s._capacity;
	}
	bool string::operator <(const string& s)const
	{
		size_t i1 = 0, i2 = 0;
		while (i1 < _size && i2 < s._size)
		{
			if (_str[i1] > s._str[i2])
			{
				return false;
			}
			else if(_str[i1]<s._str[i2])
			{
				return true;
			}
			else
			{
				i1++;
				i2++;
			}
		}
		//能走到这里的只有三种情况
		//1.hello与hello   2.hellox与hello   3.hello与hellox
		//其实我们只需要比较i2与_size的大小就可以了
		return i2 > s._size;//只有这种情况是true，其余都是false
	}
	bool string::operator ==(const string& s)const
	{
		size_t i1 = 0, i2 = 0;
		while (i1 < _size && i2 < s._size)
		{
			if (_str[i1] != s._str[i2])
			{
				return false;
			}
			else 
			{
				i1++;
				i2++;
			}
		}
		//到这里也是三种情况
		//1.hello与hello   2.hellox与hello   3.hello与hellox
		return i1 == _size && i2 == s._size;
	}
	bool string::operator <=(const string& s)const
	{
		return !((*this) > s);
	}
	bool string::operator >(const string& s)const
	{
		return !((*this) <= s);
	}
	bool string::operator >=(const string& s)const
	{
		return !((*this) < s);
	}
	bool string::operator !=(const string& s)const
	{
		return !((*this) == s);
	}
	void string::clear()
	{
		_str[_size] = '\0';
		_size = 0;
	}
	istream& operator>>(istream& in, string& s)
	{
		s.clear();

		char buff[128];
		int i = 0;

		char ch = in.get();
		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == 127)
			{
				buff[i] = '\0';
				s += buff;
				i = 0;
			}

			ch = in.get();
		}

		if (i > 0)
		{
			buff[i] = '\0';
			s += buff;
		}

		return in;
	}

	istream& getline(istream& in, string& s, char delim)
	{
		s.clear();

		char buff[128];
		int i = 0;

		char ch = in.get();
		while (ch != delim)
		{
			buff[i++] = ch;
			if (i == 127)
			{
				buff[i] = '\0';
				s += buff;
				i = 0;
			}

			ch = in.get();
		}

		if (i > 0)
		{
			buff[i] = '\0';
			s += buff;
		}

		return in;
	}
	const size_t string::npos = -1;//在这里写定义的时候就不需要+stactic了，而且npos要指明类域。

}