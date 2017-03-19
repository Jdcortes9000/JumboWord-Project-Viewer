#pragma once

template<typename Type> class SLLIter;

template<typename Type> class SLList
{

	friend class SLLIter<Type>;
	struct Node
	{
		Type element;
		Node * next;
	};
	Node* head;
	unsigned int Size;
	void DynamicCopy(Node* temp)
	{
		if (temp != nullptr)
		{
			DynamicCopy(temp->next);
			addHead(temp->element);
		}
		
	}
public:
	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor
	// Notes : constructs an empty list
	/////////////////////////////////////////////////////////////////////////////
	SLList()
	{
		head = nullptr;
		Size = 0;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : Destructor
	// Notes : Destroys the list
	/////////////////////////////////////////////////////////////////////////////
	~SLList()
	{
		clear();
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : Assignment Operator
	/////////////////////////////////////////////////////////////////////////////
	SLList<Type>& operator=(const SLList<Type>& that)
	{

		if (this != &that)
		{
			clear();
			DynamicCopy(that.head);

		}
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Copy Constructor
	/////////////////////////////////////////////////////////////////////////////
	SLList(const SLList<Type>& that)
	{
		clear();
		DynamicCopy(that.head);
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : addHead
	// Parameters :	v - the item to add to the list
	/////////////////////////////////////////////////////////////////////////////
	void addHead(const Type& v)
	{
		Node* n = new Node;
		n->element = v;
		n->next = head;
		head = n;
		++Size;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the list, freeing any dynamic memory
	/////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		while (head != nullptr)
		{
			Node*temp = head;
			head = head->next;
			delete temp;
			temp = nullptr;
		}
		Size = 0;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters :	index - an iterator to the location to insert at
	//				v - the item to insert
	// Notes : do nothing on a bad iterator
	/////////////////////////////////////////////////////////////////////////////
	void insert(SLLIter<Type>& index, const Type& v)
	{
		Node* prev = nullptr;
		Node * curr = head;
		for (unsigned int i = 0; i < Size; i++)
		{
			if (head == index.c)
			{
				Node* n = new Node;
				n->element = v;
				n->next = head;
				head = n;
				index.begin();
				break;
			}
			else if (curr == index.c)
			{
				Node*n = new Node;
				prev->next = n;
				n->next = curr;
				n->element = v;
				index.c = n;
				break;
			}
			prev = curr;
			curr = curr->next;
		}
		++Size;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : remove
	// Parameters :	index - an iterator to the location to remove from
	// Notes : do nothing on a bad iterator
	/////////////////////////////////////////////////////////////////////////////
	void remove(SLLIter<Type>& index)
	{
		Node* prev = nullptr;
		Node * curr = head;
		for (unsigned int i = 0; i < Size; i++)
		{
			if (head == index.c)
			{
				Node*temp = head;
				head = head->next;
				temp = nullptr;
				++index;
				break;
			}
			else if (curr == index.c)
			{
				prev->next = curr->next;
				Node*temp = curr;
				curr = curr->next;
				temp = nullptr;
				++index;
				break;
			}
			prev = curr;
			curr = curr->next;
		}
		--Size;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : size
	// Return : the number of items stored in the linked list.
	/////////////////////////////////////////////////////////////////////////////
	inline unsigned int size() const { return Size; }
};

template<typename Type>
class SLLIter
{
	// the list is the iterator’s friend
	friend class SLList<Type>;
	SLList<Type>* LinkList;
	typename SLList<Type>::Node * c;
	typename SLList<Type>::Node * pre;
	// add members/methods here…
public:

	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor
	// Parameters :	listToIterate - the list to iterate
	/////////////////////////////////////////////////////////////////////////////
	SLLIter(SLList<Type>& listToIterate)
	{
		LinkList = &listToIterate;
		begin();
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : begin
	// Notes : moves the iterator to the head of the list
	/////////////////////////////////////////////////////////////////////////////
	void begin()
	{
		pre = nullptr;
		c = LinkList->head;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : end
	// Notes : returns true if we are at the end of the list, false otherwise
	/////////////////////////////////////////////////////////////////////////////
	bool end() const
	{
		if (c == nullptr)
		{
			return true;
		}
		else
			return false;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : operator++
	// Notes : move the iterator forward one node
	/////////////////////////////////////////////////////////////////////////////
	SLLIter<Type>& operator++()
	{
		if (c == nullptr)
		{
			return *this;
		}
		else
		{
			pre = c;
			c = c->next;
			return *this;
		}

	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : current
	// Notes : returns the item at the current iterator location
	/////////////////////////////////////////////////////////////////////////////
	Type& current() const
	{
		return c->element;
	}
};