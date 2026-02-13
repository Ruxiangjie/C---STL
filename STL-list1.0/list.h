#pragma once
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
		Ref operator*()
		{
			return (_node->data);
		}

		//判断
		bool operator!=(const self& it)
		{
			return _node != it._node;
		}

		bool operator==(const self& it)
		{
			return _node == it._node;
		}

		ptr operator->()
		{
			return &(_node->data);
		}
	private:
		Node* _node;
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
		list()
		{
			_head = new Node;
			_head->next = _head;
			_head->prev = _head;
		}
		void push_back(const T& x)
		{
			Node* newnode = new Node(x);
			Node* tail = _head->prev;

			tail->next = newnode;
			newnode->prev = tail;
			newnode->next = _head;
			_head->prev = newnode;
		}
	private:
		Node* _head;
	};
}