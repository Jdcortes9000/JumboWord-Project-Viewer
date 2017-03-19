#pragma once

#include <iostream>

using namespace std;


template<typename Type> class BST
{
	
	struct Node
	{
		Type element;
		Node * left;
		Node * right;

		Node()
		{
			left = nullptr;
			right = nullptr;
		}
	};
	Node* Root;

	void InOrder( Node* n) const
	{
		while (true)
		{
			if (n->left == nullptr)
			{
				cout << n->element << " ";
				if (n->right != nullptr)
				{
					InOrder(n->right);
					break;
				}
				else if (n->right == nullptr)
				{
					break;
				}
			}
			else
			{
				if (n->left != nullptr)
				{
					InOrder(n->left);
					cout << n->element << " ";
					if (n->right != nullptr)
					{
						InOrder(n->right);
						break;
					}
					else if (n->right == nullptr)
					{
						break;
					}
				}
			}
		}
	}
	void PostOrder( Node *n)
	{
		while (true)
		{
			if (n->left == nullptr && n->right == nullptr)
			{
				delete n;
				break;
			}
			else
			{
				if (n->left != nullptr)
				{
					PostOrder(n->left);
					n->left = nullptr;
					
				}
				else if (n->right != nullptr)
				{
					PostOrder(n->right);
					n->right = nullptr;
				}
			}
		}
	}
	void PreOrder(Node *n)
	{
		/*insert(n->element);
		if (n->left == nullptr)
		{
			return;
		}
		PreOrder(n->left);
		if (n->right == nullptr)
		{
			return;
		}
		PreOrder(n->right);*/
		if (n != nullptr)
		{
			insert(n->element);
			PreOrder(n->left);
			PreOrder(n->right); 
		}
	}

public:
	/////////////////////////////////////////////////////////////////////////////
	// Function : Constuctor
	// Notes : constucts an empty BST
	/////////////////////////////////////////////////////////////////////////////
	BST()
	{
		Root = nullptr;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Destructor
	// Notes : destroys the BST cleaning up any dynamic memory
	/////////////////////////////////////////////////////////////////////////////
	~BST()
	{
		clear();
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : assignment operator
	/////////////////////////////////////////////////////////////////////////////
	BST& operator=(const BST& that)
	{
		if (this != &that)
		{
			Node*current = that.Root;
			this->clear();
			PreOrder(current);
			
		}
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function: copy constructor
	/////////////////////////////////////////////////////////////////////////////
	BST(const BST& that)
	{
		Root = nullptr;
		*this = that;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters :  v - the item to insert 
	/////////////////////////////////////////////////////////////////////////////
	void insert(const Type& v)
	{
		Node* n = new Node();
		Node* current = Root;
		if (Root == nullptr)
		{
			n->element = v;
			Root = n;
		}
		else
		{
			while (true)
			{
				if (v < current->element)
				{
					if (current->left == nullptr)
					{
						n->element = v;
						current->left = n;
						break;
					}
					else
					current = current->left;
				}
				else if (v > current->element)
				{
					if (current->right == nullptr)
					{
						n->element = v;
						current->right = n;
						break;
					}
					else
						current = current->right;
				}
			}			
		}

	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : findAndRemove
	// Parameters : v - the item to find (and remove if it is found)
	// Return : bool - true if the item was removed, false otherwise
	/////////////////////////////////////////////////////////////////////////////
	bool findAndRemove(const Type& v)
	{
		Node* current = Root;
		Node* min = Root;
		Node* parent = Root;
		Node* temp = Root;
		if (Root == nullptr)
		{
			return false;
		}
		if (Root->element == v)
		{
			min = current;
			temp = current;
			if (current->left != nullptr && current->right != nullptr)
			{
				min = min->right;
				while (true)
				{
					if (min->left == nullptr)
					{
						break;
					}
					else
					{
						min = min->left;
					}
				}

				while (true)
				{
					if (parent->left == min || parent->right == min)
					{
						break;
					}
					else
					{
						if (parent->element > min->element)
						{
							parent = parent->left;
						}
						else if (parent->element < min->element)
						{
							parent = parent->right;
						}
					}
				}
				Type temp2 = current->element;
				current->element = min->element;
				min->element = temp2;
				if (parent->left == min)
				{
					temp = min->right;
					min->right = nullptr;
					parent->left = temp;
					return true;
				}
				else if (parent->right == min)
				{
					temp = min->right;
					min->right = nullptr;
					parent->right = temp;
					return true;
				}
			}
			else if (current->left != nullptr || current->right != nullptr)
			{
				while (true)
				{
					if (parent == current)
					{
						if (parent->left != nullptr)
						{
							temp = parent->left;
						}
						else if (parent->right != nullptr)
						{
							temp = parent->right;
						}
						current = nullptr;
						Root = temp;
						return true;
					}
					if (parent->left == current || parent->right == current)
					{
						break;
					}
					else
					{
						if (parent->element > current->element)
						{
							parent = parent->left;
						}
						else if (parent->element < current->element)
						{
							parent = parent->right;
						}
						
					}
				}
				if (current->left != nullptr)
				{
					temp = current->left;
				}
				else if (current->right != nullptr)
				{
					temp = current->right;
				}
				if (parent->left == current)
				{
					if (current->left != nullptr)
					{
						current->left = nullptr;
						parent->left = temp;
						return true;
					}
					else if (current->right != nullptr)
					{
						current->right = nullptr;
						parent->left = temp;
						return true;
					}
				}
				else if (parent->right == current)
				{
					if (current->left != nullptr)
					{
						current->left = nullptr;
						parent->right = temp;
						return true;
					}
					else if (current->right != nullptr)
					{
						current->right = nullptr;
						parent->right = temp;
						return true;
					}
				}
			}
			else if (current->left == nullptr && current->right == nullptr)
			{
				if (parent == current)
				{
					Root = nullptr;
					return true;
				}
				while (true)
				{

					if (parent->left == current || parent->right == current)
					{
						break;
					}
					else
					{
						if (parent->element > current->element)
						{
							parent = parent->left;
						}
						else if (parent->element < current->element)
						{
							parent = parent->right;
						}
					}
				}
				if (parent->left == current)
				{
					parent->left = nullptr;
					return true;
				}
				else if (parent->right == current)
				{
					parent->right = nullptr;
					return true;
				}
			}
		}
		while (true)
		{
			if (current->element > v)
			{
				if (current->left == nullptr)
				{
					return false;
				}
				if (current->left->element == v)
				{
					current = current->left;
					min = current;
					temp = current;
					if (current->left != nullptr && current->right != nullptr)
					{
						min = min->right;
						while (true)
						{
							if (min->left == nullptr)
							{
								break;
							}
							else
							{
								min = min->left;
							}
						}

						while (true)
						{
							if (parent->left == min || parent->right == min)
							{
								break;
							}
							else
							{
								if (parent->element > min->element)
								{
									parent = parent->left;
								}
								else if (parent->element < min->element)
								{
									parent = parent->right;
								}
							}
						}
						Type temp2 = current->element;
						current->element = min->element;
						min->element = temp2;
						if (parent->left == min)
						{
							temp = min->right;
							min->right = nullptr;
							parent->left = temp;
							return true;
						}
						else if (parent->right == min)
						{
							temp = min->right;
							min->right = nullptr;
							parent->right = temp;
							return true;
						}
					}
					else if (current->left != nullptr || current->right != nullptr)
					{
						while (true)
						{
							if (parent->left == current || parent->right == current)
							{
								break;
							}
							else
							{
								if (parent->element > current->element)
								{
									parent = parent->left;
								}
								else if (parent->element < current->element)
								{
									parent = parent->right;
								}

							}
						}
						if (current->left != nullptr)
						{
							temp = current->left;
						}
						else if (current->right != nullptr)
						{
							temp = current->right;
						}
						if (parent->left == current)
						{
							if (current->left != nullptr)
							{
								current->left = nullptr;
								parent->left = temp;
								return true;
							}
							else if (current->right != nullptr)
							{
								current->right = nullptr;
								parent->left = temp;
								return true;
							}
						}
						else if (parent->right == current)
						{
							if (current->left != nullptr)
							{
								current->left = nullptr;
								parent->right = temp;
								return true;
							}
							else if (current->right != nullptr)
							{
								current->right = nullptr;
								parent->right = temp;
								return true;
							}
						}
					}
					else if (current->left == nullptr && current->right == nullptr)
					{
						while (true)
						{
							if (parent->left == current || parent->right == current)
							{
								break;
							}
							else
							{
								if (parent->element > current->element)
								{
									parent = parent->left;
								}
								else if (parent->element < current->element)
								{
									parent = parent->right;
								}
							}
						}
						if (parent->left == current)
						{
							parent->left = nullptr;
							return true;
						}
						else if (parent->right == current)
						{
							parent->right = nullptr;
							return true;
						}
					}
				}
				else
				{
					current = current->left;
					if (current->left == nullptr && current->right == nullptr)
					{
						return false;
					}
				}
			}
			else if (current->element < v)
			{
				if (current->right == nullptr)
				{
					return false;
				}
				if (current->right->element == v)
				{
					current = current->right;
					min = current;
					temp = current;
					if (current->left != nullptr && current->right != nullptr)
					{
						min = min->right;
						while (true)
						{
							if (min->left == nullptr)
							{
								break;
							}
							else
							{
								min = min->left;
							}
						}
						
							while (true)
							{
								if (parent->left == min|| parent->right == min)
								{
									break;
								}
								else
								{
									if (parent->element > min->element)
									{
										parent = parent->left;
									}
									else if (parent->element < min->element)
									{
										parent = parent->right;
									}
								}
							}
							Type temp2 = current->element;
							current->element = min->element;
							min->element = temp2;
							if (parent->left == min)
							{
								temp = min->right;
								min->right = nullptr;
								parent->left = temp;
								return true;
							}
							else if (parent->right == min)
							{
								temp = min->right;
								min->right = nullptr;
								parent->right = temp;
								return true;
							}
						
					}
					else if (current->left != nullptr || current->right != nullptr)
					{
						while (true)
						{
							if (parent->left == current || parent->right == current)
							{
								break;
							}
							else
							{
								if (parent->element > current->element)
								{
									parent = parent->left;
								}
								else if (parent->element < current->element)
								{
									parent = parent->right;
								}

							}
						}
						if (current->left != nullptr)
						{
							temp = current->left;
						}
						else if (current->right != nullptr)
						{
							temp = current->right;
						}
						if (parent->left == current)
						{
							if (current->left != nullptr)
							{
								current->left = nullptr;
								parent->left = temp;
								return true;
							}
							else if (current->right != nullptr)
							{
								current->right = nullptr;
								parent->left = temp;
								return true;
							}
						}
						else if (parent->right == current)
						{
							if (current->left != nullptr)
							{
								current->left = nullptr;
								parent->right = temp;
								return true;
							}
							else if (current->right != nullptr)
							{
								current->right = nullptr;
								parent->right = temp;
								return true;
							}
						}
					}
					else if (current->left == nullptr && current->right == nullptr)
					{
						while (true)
						{
							if (parent->left == current || parent->right == current)
							{
								break;
							}
							else
							{
								if (parent->element > current->element)
								{
									parent = parent->left;
								}
								else if (parent->element < current->element)
								{
									parent = parent->right;
								}
							}
						}
						if (parent->left == current)
						{
							parent->left = nullptr;
							return true;
						}
						else if (parent->right == current)
						{
							parent->right = nullptr;
							return true;
						}
					}
				}
				else
				{
					current = current->right;
					if (current->left == nullptr && current->right == nullptr)
					{
						return false;
					}
				}
			}
		}
		return false;
	}


	/////////////////////////////////////////////////////////////////////////////
	// Function : find
	// Parameters : v - the item to find
	// Return : bool - true if the item was found, false otherwise
	/////////////////////////////////////////////////////////////////////////////
	bool find(const Type& v) const
	{
		Node* current = Root;
		if (Root == nullptr)
		{
			return false;
		}
		else if (Root->element == v)
		{
			return true;
		}
		while (true)
		{
			if (current->element > v)
			{
				if (current->left == nullptr)
				{
					return false;
				}
				if (current->left->element == v)
				{
					return true;
				}
				else
				{
					current = current->left;
					if (current->left == nullptr && current->right == nullptr)
					{
					 return false;
					}
				}
			}
			else if (current->element < v)
			{
				if (current->right == nullptr)
				{
					return false;
				}
				if (current->right->element == v)
				{
					return true;
				}
				else
				{
					current = current->right;
					if (current->left == nullptr && current->right == nullptr)
					{
						return false;
					}
				}
			}
		}
		return false;
	}


	/////////////////////////////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the BST, cleaning up any dynamic memory
	/////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		Node* current = Root;
		if (Root != nullptr)
		{
			PostOrder(current);
			Root = nullptr;
		}	
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : printInOrder
	// Notes : prints the contents of the BST to the screen, in ascending order
	/////////////////////////////////////////////////////////////////////////////
	void printInOrder() const
	{
		Node* current = Root;
		if (Root != nullptr)
		{
			InOrder(current);
		}
		cout << "\n";
	}

};