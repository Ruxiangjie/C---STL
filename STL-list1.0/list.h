#pragma once
namespace rxj
{
	template<class T>
	struct list_node
	{
		T data;
		list_node<T>* _next;
		list_node<T>* _prev;

		List_node(const T& x = T())
			:data(x)
			,_next(nullptr)
			,_prev(nullptr)
		{

		}
	};

	template<class T>
	struct __list_iterator
	{
		typedef list_node<T> Node;
		Node* node;

		__list_iterator(Node* node)
			:_node(node)
		{
		}


		__list_iterator<T>& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		T& operator*()
		{
			return (_node->data);
		}
	private:
		Node* _node;
	};

	template<class T>
	class list
	{
		typedef List_node<T> Node;
	public:
		typedef __list_iterator<T> iterator;
		typedef const__list_iterator<T> iterator;
		
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