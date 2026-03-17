#pragma once
#include<vector>
#include<list>
using namespace std;
namespace rxj//1 后面没有冒号
{
	template<class T,class Container = vector<T>>//2. 这里我们传入T的目的是为了push的时候知道容器内存放的数据是什么类型
	class stack
	{
	public:
		void push(const T& val)//在这里我们要传数据的引用，既然是引用，我们就要防止数据被修改
		{
			_con.push_back(val);//栈是后进先出，我们要往队尾插入数据
		}
		void pop()
		{
			_con.pop_back();//后进先出，我们要先出后面的元素
		}
		size_t size()const//避免数据在这个函数内被修改
		{
			return _con.size();
		}
		bool empty()const
		{
			return _con.empty();
		}
		const T& top()const
		{
			return _con.back();
		}
		void swap(stack<T, Container>& st)//这里的参数，我们在构造一个st的时候，会自动生成一个类，
		//T和container会自动给上值，所以我们如果想传入一个和原本对象相同类型的对象，就要这样传
		{
			_con.swap(st._con);
		}
	private:
		Container _con;//3. 成员变量要使用_命名法  4.stack并不管数据的存储，所以里面没有_data这个成员
	};
}





//namespace rxj
//{
//	template<class T, class Container = vector<T>>//两个模版参数，一个是数据类型，一个是容器
//	class Stack
//	{
//	public:
//		void push(const T& val)
//		{
//			_con.push_back(val);
//		}
//
//		void pop()
//		{
//			_con.pop_back();
//		}
//
//		size_t size()const
//		{
//			return _con.size();
//		}
//
//		bool empty()const
//		{
//			return _con.empty();
//		}
//
//		const T& top() const
//		{
//			return _con.back();//你不知道container是什么，不能直接使用方括号和其他的
//		}
//	private:
//		Container _con;//这里
//	};
//}