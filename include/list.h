#pragma once
using namespace std;

template <class T>
class List {
	struct Node {
		T data;
		Node* next;

		Node(T a = T(), Node* t = nullptr)
		{
			data = a;
			next = t;
		}

		Node& operator=(const Node& other)
		{
			data = other.data;
			delete next;
			next = other.next;
		}

		~Node()
		{
			next = nullptr;
			data = 0;
		}
	};
	Node* first;

public:
	List()
	{
		first = nullptr;
	}

	List(int n) : first(nullptr)
	{
		for (int i = 0; i < n; ++i)
		{
			insert_front(T());
		}
	}

	~List()
	{
		while (first)
		{
			Node* second = first->next;
			delete first;
			first = second;
		}
	}

	List(const List& other) : first(nullptr)
	{
		if (other.first)
		{
			first = new Node(other.first->data);
			Node* current = first;
			Node* ocurrent = other.first->next;
			while (ocurrent)
			{
				current->next = new Node(ocurrent->data);
				current = current->next;
				ocurrent = ocurrent->next;
			}
		}
	}

	List& operator=(const List& a)
	{
		if (this == &a) return *this;

		while (first)
		{
			Node* second = first->next;
			delete first;
			first = second;
		}

		if (!a.first)
		{
			first = nullptr;
			return *this;
		}

		first = new Node;
		first->data = a.first->data;
		Node* current = first;
		Node* ocurrent = a.first->next;
		while (ocurrent)
		{
			current->next = new Node;
			current = current->next;
			current->data = ocurrent->data;
			ocurrent = ocurrent->next;
		}
		current->next = nullptr;

		return *this;
	}

	void print()
	{
		Node* current = first;
		while (current)
		{
			std::cout << current->data << "  ";
			current = current->next;
		}
	}

	T& operator[](int index)
	{
		Node* current = first;
		int count = 0;
		while (current)
		{
			if (count == index)
			{
				return current->data;
			}
			current = current->next;
			count++;
		}
		throw "Index out of range";
	}

	Node* insert(T value, Node* prev)
	{
		if (!prev) throw "Previous node cannot be null";
		Node* temp = new Node(value, prev->next);
		prev->next = temp;
		return temp;
	}

	Node* insert_front(T value)
	{
		Node* first_first = new Node;
		first_first->next = first;
		first_first->data = value;
		first = first_first;
		return first;
	}

	Node* erase(Node* prev)
	{
		if (!prev || !prev->next) throw "Invalid node or no next node to erase";
		Node* tmp = prev->next;
		prev->next = tmp->next;
		delete tmp;
		return prev->next;
	}

	Node* erase_front()
	{
		if (!first) throw "List is empty";
		Node* tmp = first;
		first = tmp->next;
		delete tmp;
		return first;
	}

	Node* find(T value)
	{
		Node* current = first;
		while (current)
		{
			if (current->data == value)
			{
				return current;
			}
			current = current->next;
		}
		return nullptr;
	}

	Node* get_first()
	{
		return first;
	}

	size_t size()
	{
		int count = 0;
		Node* current = first;
		while (current)
		{
			count++;
			current = current->next;
		}
		return count;
	}
};