// Ex 13.28: implementing default constructor and necessary copy-control members
// We'll build these with valuelike approach to pointers, as suggested by exercise box's title

#include <string>
#include <iostream>

class TreeNode 
{
	public:

		TreeNode(std::string s, int c): _value(s), _count(c), left(NULL), right(NULL) {}
		TreeNode(const TreeNode&);
		TreeNode& operator=(const TreeNode&);

	private:

		std::string _value;
		int _count;
		TreeNode *left;
		TreeNode *right;
};

class BinStrTree 
{
	public:

		// create new item as a root node on construction
		BinStrTree(TreeNode &t) { root = new TreeNode(t); }

		// copy constructor copies the value of rhs TreeNode to a new item (root is never NULL!)
		BinStrTree(const BinStrTree& rhs) { *root = *(rhs.root); }
		BinStrTree& operator=(const BinStrTree& rhs) { *root = *(rhs.root); }

		~BinStrTree() { delete root; }
		
	private:

		TreeNode *root;
};

TreeNode::TreeNode(const TreeNode &rhsTreeNode):
	_value(rhsTreeNode._value),
	_count(rhsTreeNode._count)
{ 
	std::cout << "Copy Constructing TreeNode" << std::endl;

	if (rhsTreeNode.left != NULL) // if there is something to copy
	{
		// If there is nothing yet in left, we create a new pointer
		// if there is, we just update the value
		if (left == NULL)
			left = new TreeNode(*rhsTreeNode.left);
		else
			*left = *rhsTreeNode.left;
	}
	if (rhsTreeNode.right != NULL)
	{
		if (right == NULL)
			right = new TreeNode(*rhsTreeNode.right);
		else
			*right = *rhsTreeNode.right;
	}
}

TreeNode& TreeNode::operator=(const TreeNode &rhsTreeNode)
{
	std::cout << "Assigning TreeNode" << std::endl;

	_value = rhsTreeNode._value;
	_count = rhsTreeNode._count;
	
	if (rhsTreeNode.left != NULL) // if there is something to copy
	{
		// If there is nothing yet in left, we create a new pointer
		// if there is, we just update the value
		if (left == NULL)
			left = new TreeNode(*rhsTreeNode.left);
		else
			*left = *rhsTreeNode.left;
	}
	if (rhsTreeNode.right != NULL)
	{
		if (right == NULL)
			right = new TreeNode(*rhsTreeNode.right);
		else
			*right = *rhsTreeNode.right;
	}
}

int main()
{
	TreeNode ruut("string", 14), muut("noe", 41);
	BinStrTree folder(ruut), filder(muut);
	BinStrTree copyOfFolder(ruut);

	filder = folder;
	muut = ruut;

	return 0;
}
