#pragma once
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
namespace rxj
{
	using namespace std;
	class string
	{
	public:
		typedef char* iterator;
		iterator begin();
		iterator end();
		typedef char const* const_iterator;
		const_iterator begin()const;//值得一提的是我们这里的begin的返回值是无法修改的指针！！！所以我们在传参的时候也应该用const修饰
		const_iterator end()const;
		string(const char* str = "\0");
		const char* c_str() const;
		~string();
		size_t size()const;
		const char& operator[](size_t i) const;
		char& operator[](size_t i);//既然这个[]是可以替换内容的，那么我们就不能只读了，也就是不能+const修饰
		void push_back(const char ch);//我们只实现最核心的这个尾插一个字符
		void append(const char* str);//最核心的这个尾插一个字符串
		void reserve(size_t n);
		void pop_back();
		string& operator+=(char ch);
		string& operator+=(const char* str);
		string& insert(size_t pos,const char* str);
		string& insert(size_t pos,char ch);
		string& erase(size_t pos = 0,size_t len = npos);
		size_t find(char ch,size_t pos = 0)const;
		size_t find(const char* str,size_t pos = 0)const;
		string substr(size_t pos, size_t len = npos)const;
		string(const string& s);
		static const size_t npos;
		bool operator <(const string& s)const;
		bool operator ==(const string& s)const;
		bool operator <=(const string& s)const;
		bool operator >(const string& s)const;
		bool operator >=(const string& s)const;
		bool operator !=(const string& s)const;
		void clear();
		istream& getline(istream& in, string& s, char delim = '\n');
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
	ostream& operator<<(ostream& out, const string& s);//输出运算符必须要写成友元吗？写成友元的原因是我们要访问这个对象里面的私有
	istream& operator>>(istream& in, string& s);

}
