//Project 5 extra project
// Sujata Sahu

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBTNode
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBTNode
{
protected:
	// Instance Variables
	DT *_info;
	int _left;
	int _right;

public:
// Constructors and Destructor
ArrayBTNode(){};
ArrayBTNode(DT &info){_info = &info;};
~ArrayBTNode(){};
// getter Methods
//return info(pointer)
DT* getinfo(){return _info;};
//return _left (index of left child)
int getleft(){return _left;};
//return _right (index of right child)
int getright(){	return _right;};
// setter Methods
// Sets _info
void setInfo(DT &info){	_info = &info;};
// Sets _info to Null
void setInfoNull(){	_info = NULL;}; 
//Sets _left (left child index)
void setLeft(int left){	_left = left;};
//Sets _right (right child index)
void setRight(int right){_right = right;};
// Display Method
	// Outputs data in _info, _left, _right
void display(){cout << *_info << ", Left: " << _left << ", Right: " << _right << endl;};
// Overloaded Comparison Operators
// Used for comparing (< , > , ==, >=, <=, != ) _info field with other ArrayBTNodes
bool operator<(const ArrayBTNode<DT> &x)
{
	if(*_info < *x._info)
		return true;
	return false;
};
bool operator>(const ArrayBTNode<DT> &x)
{
	if(*_info > *x._info)
		return true;
	return false;
};
bool operator==(const ArrayBTNode<DT> &x)
{
	if(*_info == *x._info)
		return true;
	return false;
};
bool operator>=(const ArrayBTNode<DT> &x)
{	
	if(*_info >= *x._info)
		return true;
	return false;
};
bool operator<=(const ArrayBTNode<DT> &x)
{
	if(*_info <= *x._info)
		return true;
	return false;
};
bool operator!=(const ArrayBTNode<DT> &x)
{
	if(*_info != *x._info)
		return true;
	return false;
};
// TODO: Overloaded Ostream Operator - Uses display method to output ArrayBTNode contents
friend ostream & operator << (ostream &os, ArrayBTNode &btObject){
		cout << "Info: "; btObject.display();
		return os;
}
};

////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBST
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBST
{
protected:
	// Instance Variables
	vector<ArrayBTNode<DT> > _tree;    // Vector of ArrayBTNodes used to create a tree
	int _rootIndex;            // Index of the root node in _tree
	int _numNodes;             // Number of nodes in the tree
	int _size;                 // Maximum size of the _tree array
	stack<int> _freeLocations; // Stack containing indexes of freeLocations in the _tree array

public:
	// Constructors and Destructor
	ArrayBST(){};
	
	// initialize the vector with NULL nodes and fill the stack
	ArrayBST(int k)
	{
		_size = k;
		int *n = NULL; //NULL pointer for Null nodes
		for (int i = 0; i < _size; i++)
		{
			ArrayBTNode<int> newNode = ArrayBTNode<int>(*n); // Creating a New NULL Node
			newNode.setLeft(-1); //Initially set -1 for Left
			newNode.setRight(-1); //Initially set -1 for Right
			_tree.push_back(newNode); //Add Null node to tree
			_freeLocations.push(i); //Add free position to stack
		}
		_rootIndex = _size-1;
		_numNodes = 0;
	}; 
	~ArrayBST(){};

	// Accessor Methods
	//returns true or false based on tree has nodes or empty
	bool isEmpty() const{return _numNodes <= 0; };
	int Height();
	//returns size of tree i.e total number of nodes added to tree
	int Size(){return _numNodes;};
	//return index of root node in BST
	int rootIndex(){return _rootIndex;};
	//returns maxSize i.e maximum number of nodes that can be added to tree
	int maxSize(){return _size;};	
	
	// Mutator Methods
	void setData(int index, DT &value)
	{
		ArrayBTNode<int> node = _tree[index];
		node.setInfo(value);
		_tree[index] = node;
	};
	void setLeft(int index, int value)
	{
		ArrayBTNode<int> node = _tree[index];
		node.setLeft(value);
		_tree[index] = node;
	};
	void setRight(int index, int value)
	{
		ArrayBTNode<int> node = _tree[index];
		node.setRight(value);
		_tree[index] = node;
	};

	// Display methods and traversals
	void display(ostream &os) const
	{
		displayPreOrder(os); //call preorder traversal method
		displayInOrder(os); //call preorder traversal method
		os << endl;
	};
	//Display Tree in Pre Order
	void displayPreOrder(ostream &os) const
	{
		os << "Pre Order Traversal: " << endl;
		ArrayBTNode<int> rootNode = _tree[_rootIndex]; //Getting the root node first
		if(rootNode.getinfo() != NULL)
		{ //if info of root node is not null then print the info
			os << *rootNode.getinfo() << " ";
		}
		int left = rootNode.getleft(); //get index of left child
		int right = rootNode.getright();//get index of the right child
		preOrderTraverse(left, os); // First traverse the left tree
		preOrderTraverse(right, os); //Second traverse the right tree
		//rightTree(right, os);
		os << endl;
	};
	//Display Tree in In Order
	void displayInOrder(ostream &os) const
	{
		os << "In Order Traversal: " << endl;
		ArrayBTNode<int> rootNode = _tree[_rootIndex]; //get the root node
		//step 1 - if root node has left tree then traverse the left tree first
		if(rootNode.getleft() > -1)
		{ 
			InOrderTraverse(rootNode.getleft(), os);
		}
		//step 2 - print the parent node
		os << *rootNode.getinfo() << " ";
		//step 3 - now traverse the right tree
		if(rootNode.getright() > -1)
		{
			InOrderTraverse(rootNode.getright(), os);
		}
	};
	//Recursive method to Traverse the tree In Order and print the node info
	void InOrderTraverse(int currentPosition, ostream &os) const
	{
		ArrayBTNode<int> currentNode = _tree[currentPosition];//gets the current node
		//below steps are called recursively
		//step 1 - if current node(parent) has left tree then traverse the left tree first
		if(currentNode.getleft() > -1)
		{
			InOrderTraverse(currentNode.getleft(), os);
		}
		//step 2 - print the parent node
		os << *currentNode.getinfo() << " ";
		//step 3 - now traverse the right tree
		if(currentNode.getright() > -1)
		{
			InOrderTraverse(currentNode.getright(), os);
		}
	}
	//Recursive method to Traverse the tree Pre Order and print the node info
	void preOrderTraverse(int currentPosition, ostream &os) const
	{
		if(currentPosition == -1) //return if current index is -1 because its end of tree
			return;
		ArrayBTNode<int> currentNode = _tree[currentPosition]; //get the node at current index
		if(currentNode.getinfo() != NULL)
		{ //print if node is not NULL (this condition doesn't usually gets false)
			os << *currentNode.getinfo() << " ";
		}
		int left = currentNode.getleft();
		int right = currentNode.getright(); 
		preOrderTraverse(left, os); //First Travesrse the left tree of current node
		preOrderTraverse(right, os); //after traversing the left now traverse the right tree
	}
	// Display the array and all of its contents
	void printRaw()
	{
		stack<int> tempFree = _freeLocations; //Temporary Stack to show free locations
		cout << "Raw Data: "<< endl;
		//Loop to print Tree nodes in Raw format
		for (int i = 0; i < _size; i++)
		{
			ArrayBTNode<int> currentNode = _tree[i]; //Get Node at position i
			if(currentNode.getinfo() != NULL) //Check if the current node has NULL info value
			{
				cout << "Index " <<  i << ": " << currentNode;
			}
		}
		cout << "Free Indexes: "<< endl;
		if(tempFree.size()>0)
		{
			//Loop to print Free Positions
			while (!tempFree.empty())
			{
				if(tempFree.size() != 1)
				{
					cout << tempFree.top() << ", ";
				}
				else
				{
					cout << tempFree.top() << endl;
				}
				tempFree.pop();
			}
		}
		else
		{
			cout << "None" << endl;
		}
	};
	// BST Specific Methods
	//This method will insert new node into the tree
	void insert(DT &object)
	{
		if(_numNodes < _size)//Check if tree is full before add
		{ 
			//Step 1 - Create ArrayBTNode to be added in vector
			ArrayBTNode<int> newNode = ArrayBTNode<int>(object); //creates a new node with given info
			newNode.setLeft(-1); //Initially set left child -1
			newNode.setRight(-1); //Initially set right child -1
			
			//Step 2 - Get the free location on Vector and add on that position
			int position = _freeLocations.top(); //Free location to insert new node
			_tree[position] = newNode; //New node added to tree
			_freeLocations.pop(); //Popped the free location just used
				
			_numNodes++; //increment the nodes count by 1
		
			//Step 3 - Put it in proper position in BST
			if(position != _rootIndex) //If its first or root node then not needed
				PutInPosition(_rootIndex, position); //Calling this method to place newly added node in tree on its place
		}
		else
		{
			cout << "Cannot insert data, BST Full." << endl;
		}
	};
	//return true if node is found else return false 
	bool find(DT &object)
	{
		int index = findIndex(object); //call this function to check the index of given node.
		if(index > -1) //if index is greater than -1 then object found and is at returned index
		{
			cout << "Number found at index " << index << "." << endl;
			return true;
		}
		return false;
	};
	//traverse tree and return index of node. if not found -1 is returned
	int searchTree(int currentPosition, DT &object)
	{
		int index = -1; //initial index for given node is set -1
		if(currentPosition == -1) //return from here if current position is -1 because it is not a node
			return index;
		ArrayBTNode<int> currentNode = _tree[currentPosition]; //Add node at current position to a temp ArrayBTNode
		if(object == *currentNode.getinfo()) //Compare value of node with given number
		{
			return currentPosition; //return this position if equal
		}
		if(object < *currentNode.getinfo()) //if given number is less than current node then it will be available in left tree
		{
			int tempIndex = -1; //set temporary index -1
			int left = currentNode.getleft(); //get left child index
			tempIndex = searchTree(left, object); // store the index returned by this method recursively
			if(tempIndex > -1) //if returned index is greater than -1 then found
				return tempIndex; //return index of node
		}
		if(object > *currentNode.getinfo()) //if given number is greater than current node then it will be available in right tree
		{
			int tempIndex = -1;//set temporary index -1
			int right = currentNode.getright(); //get right child index
			tempIndex = searchTree(right, object);// store the index returned by this method recursively
			if(tempIndex > -1)//if returned index is greater than -1 then found
				return tempIndex;//return index of node
		}
		return index; //this will be returned  if node not found in current recursion
	}
	//return index of the given node. -1 will be returned if not found
	int findIndex(DT &object){
		return searchTree(_rootIndex, object);
	};
	// extra credit
	//removes this given node
	void remove(DT &object)
	{
		int *np = NULL;
		int index = findIndex(object);
		if(index == -1)
		{
			cout << "Object not found." << endl;
			return;
		}
		ArrayBTNode<int> remove = _tree[index];
		int left = remove.getleft();
		int right = remove.getright();
		if(left == -1 && right == -1) //Node to be removed is last child, doesn't have children
		{
			setData(index, *np); //set NULL value on given Node
			setLeft(index, -1); //set left node to -1
			setRight(index, -1); //set right node to -1
			_freeLocations.push(index); //push current index to freeLocations Stack

		}
		else if(left != -1 && right != -1) //Node to be removed has two childs
		{
			ArrayBTNode<int> maxNode; //Stores the max node 
			int maxIndex = -1; //Index of the max node
			if(_tree[right].getleft() == -1 && _tree[right].getright() == -1) //Check if right node is single node
			{
				maxIndex = right; //Set its index as max index
			}
			else if(_tree[right].getleft() != -1){ //Check if right node has nodes to its left
				maxIndex = lastNode(_tree[right].getleft()); //Call method to traverse the tree to get last node
			}
			else{ //Right node doesn't have any left child
				maxIndex = right; //max node can be right node
			}
			maxNode = _tree[maxIndex];
			setData(index, *maxNode.getinfo()); //set max node value to node we want to remove
			setLeft(maxIndex, maxNode.getleft()); //set max node left to node we will remove
			setRight(maxIndex, maxNode.getright()); //set max node right to node we will remove
			
			//Following loop will remove removed node index from parent node's left or right 
			for (int i = 0; i < _size; i++)
			{
				ArrayBTNode<int> parentNode = _tree[i];
				int left = parentNode.getleft();
				int right = parentNode.getright();
				if(left == maxIndex){
					parentNode.setLeft(-1);
					_tree[i] = parentNode;
					break;
				}
				else if(right == maxIndex){
					parentNode.setRight(-1);
					_tree[i] = parentNode;
					break;
				}
			}
			
			//Following statements will keep the Node NULL which has been removed
			setData(maxIndex, *np);
			setLeft(maxIndex, -1);
			setRight(maxIndex, -1);
			_freeLocations.push(maxIndex); //It will push the index to freelocation stack as its available now

		}
		else if(left != -1 || right != -1) //Node to be removed has a single child
		{
			int cIndex = -1; //saves the Index of the Node (right or left)
			if(left != -1){
				cIndex = left; //Left node
			}
			else{
				cIndex = right; //Right Node
			}
			//step - 1, Copy left node to temp node
			ArrayBTNode<int> cNode = _tree[cIndex]; //copied left node to temp Node
			//step - 2, put left node content to node which is to be removed
			setData(index, *cNode.getinfo());
			setLeft(index, cNode.getleft());
			setRight(index, cNode.getright());
			//Step - 3, Now Make left index null
			setData(cIndex, *np);
			setLeft(cIndex, -1);
			setRight(cIndex, -1);
			_freeLocations.push(cIndex);
		}
		_numNodes--;
	};
	//this method will return index of max node in left part of tree
	int lastNode(int beginIndex){
		int lastMin = -1; //initial index
		ArrayBTNode<int> currentNode = _tree[beginIndex]; //current node
		int right = currentNode.getright(); //left index of current node
		int left = currentNode.getleft(); //right index of current node
		if(right == -1 && left == -1){ //if current node is last then return its index
			return beginIndex;
		}
		else{
			if(left != -1){ //if it has left subtree then traverse
				lastMin = lastNode(left);
				return lastMin;
			}
			else{
				lastMin = lastNode(right); //else traverse the right part
				return lastMin;
			}
		}
		return -1; 
	}
	//This Method will place new node in its perfect place in BST by recursively calling itself
	void PutInPosition(int currentRootIndex, int newNodeIndex)
	{
		ArrayBTNode<int> currentRootNode = _tree[currentRootIndex]; //Assign parent node to Temporary node
		ArrayBTNode<int> newNode = _tree[newNodeIndex]; //Assign new node from vector to temp node
		if (newNode < currentRootNode) //Traverse left tree if new node is less the current parent node
		{
			int left = currentRootNode.getleft();
			if (left == -1) //Add new node as left child if parent node has no child on left
			{
				currentRootNode.setLeft(newNodeIndex); //add the new node index to left of parent
				_tree[currentRootIndex] = currentRootNode; //replace the parent node with new parent node having left child
			}
			else{ 
				PutInPosition(left, newNodeIndex); //again traverse the left tree if child is found on left of parent node
			}
		}
		else if(newNode >= currentRootNode){ //Traverse right tree if new node is greater or equal the current parent node
			int right = currentRootNode.getright();
			if (right == -1) //Add new node as right child if parent node has no child on right
			{
				currentRootNode.setRight(newNodeIndex); //add the new node index to right of parent
				_tree[currentRootIndex] = currentRootNode; //replace the parent node with new parent node having right child
			}
			else{
				PutInPosition(right, newNodeIndex); //again traverse the right tree if child is found on right of parent node
			}
		}
	}
	// TODO: Overridden ostream operator for ArrayBST - this will call the pre order and in order methods
	friend ostream & operator << (ostream &out, ArrayBST &myBst){
		out << "Information in Tree: " << endl;
		myBst.display(out);
		return out;
	}
};

////////////////////////////////////////////////////////////////////////////////////////
// Main Method
////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	// Get input for the size of the tree
	int inputSize;
	char command;
	cin >> inputSize;
	cout << "Number of maximum nodes: " << inputSize << endl;
	// Create a BST of the size inputSize
	ArrayBST<int> myBST = ArrayBST<int>(inputSize);
    // TODO: input loop for commands
	while (cin >> command)
	{
		switch (command)
		{
			case 'I': //Insert New Node
			{
				int *inputValue = new int; //New Value for Node
				cin >> *inputValue; 
				cout << endl;
				cout << "Inserting " << *inputValue << endl;
				myBST.insert(*inputValue); //This will add new node to the tree
			}
			break;
			case 'A':
			{
				cout << endl; //New Line
				myBST.printRaw(); //calling method to print raw data
			}	
			break;		
			case 'O':
			{
				cout << endl; //New Line
				cout << myBST; //Ostream and operator (<<) overloading used for displaing PreOrder and InOrder
			}
			break;
			case 'F':
			{
				bool found;
				int *inputValue = new int; //New Value for Node
				cin >> *inputValue;
				cout << endl << "Finding " << *inputValue << endl;
				found = myBST.find(*inputValue);
				if(!found)
					cout << "Number not found." << endl;
			}
			break;
			case 'R':
			{
				int *inputValue = new int; //New Value for Node
				cin >> *inputValue;
				cout << endl << "Removing " << *inputValue << endl;
				myBST.remove(*inputValue);
			}
			break;
			default:
			break;
		}
	}
	return 0;
}