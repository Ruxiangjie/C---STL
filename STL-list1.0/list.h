#pragma once
#include<initializer_list>
#include<iostream>
#include<algorithm>
using namespace std;
namespace rxj
{
	template<class T>
	struct list_node
	{
		T data;
		list_node<T>* _next;
		list_node<T>* _prev;
		list_node(const T& x = T())//这里我们要写带有缺省值的构造函数，因为我们在新开节点的时候，可以直接通过这个传入值
			:data(x)
			,_next(nullptr)
			,_prev(nullptr)
		{
		}
	};

	template<class T,class Ref,class Ptr>
	struct __list_iterator
	{
		typedef list_node<T> Node;
		typedef __list_iterator<T, Ref,Ptr> self;
		Node* _node;
		__list_iterator(Node* node = nullptr)
			:_node(node)
		{
		}

		self& operator++()//前置++
		{
			_node = _node->_next;
			return *this;
		}

		self operator++(int)//后置++
		{
			self temp(*this);
			_node = _node->_next;
			return temp;
		}
		self& operator--()//前置--
		{
			_node = _node->_prev;
			return *this;
		}

		self operator--(int)//后置--
		{
			self temp(*this);
			_node = _node->_prev;
			return temp;
		}

		//解引用
		Ref operator*()const
		{
			return (_node->data);
		}

		//判断
		bool operator!=(const self& it)const
		{
			return _node != it._node;
		}

		bool operator==(const self& it)const
		{
			return _node == it._node;
		}

		Ptr operator->()const
		{
			return &(_node->data);
		}
	};

	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		typedef __list_iterator<T,T&,T*> iterator;
		typedef __list_iterator<T, const T&,const T*> const_iterator;
		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin()const
		{
			return const_iterator(_head->_next);
		}
		const_iterator end()const
		{
			return const_iterator(_head);
		}
		//构造函数
		void empty_init()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		list()
		{
			empty_init();
		}

		list(initializer_list<T> li)
		{
			empty_init();
			for (const auto& e : li)
			{
				push_back(e);
			}
		}

		//析构函数
		~list()
		{
			clear();
			delete _head;
		}
		//拷贝构造函数
		list(const list<T>& lt)
		{
			empty_init();
			for (const auto& e : lt)
			{
				push_back(e);
			}
		}
		//赋值运算符重载
		//传统写法
		list<T>& operator=(const list<T>& lt)
		{
			if (this!= &lt)//防止自己给自己赋值
			{
				clear();
				for (const auto& e : lt)
				{
					push_back(e);
				}
			}
			return *this;
		}
		//现代写法
		void swap(list<T>& lt)
		{
			std::swap(this->_head,lt._head);
			std::swap(this->_size, lt._size);
		}
		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = Erase(it);
			}
		}
		void push_back(const T& x)
		{
			Node* newnode = new Node(x);
			Node* tail = _head->_prev;

			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
			++_size;
		}
		void pop_back()
		{
			Erase(--end());
		}

		size_t size()const
		{
			return _size;
		}

		iterator Insert(iterator pos,const T& val)
		{
			Node* cur = pos._node;
			Node* newnode = new Node(val);
			Node* prev = cur->_prev;

			cur->_prev = newnode;
			newnode->_next = cur;
			prev->_next = newnode;
			newnode->_prev = prev;
		    ++_size;
			return iterator(newnode);
		}

		iterator Erase(iterator pos)
		{
			if (pos == end())
			{
				return pos;
			}
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = next;
			next->_prev = prev;
			delete cur;
			--_size;
			return iterator(next);
		}

	private:
		Node* _head;
		size_t _size = 0;
	};
}