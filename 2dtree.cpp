#include <iostream>
#include <vector>
using  namespace std;

const int k=2;

struct  Node
{
	int point[ k ];
	Node  *left , *right;
};

vector<Node> rangelist;
//////////////////////////////////////////////////////////////////////////////////////////////
Node *newNode (int content[]) 
{  
	Node* temp= new Node;
	for(int i=0;i<k;i++)
		temp->point[i]=content[i];
	temp->left=temp->right=NULL;

	return temp;
}

//////////////////////////////////////////////////////////////////////////////////////////////

//insert iteratively,if not a leaf,keep going down to find a place to insert
//depth is used to tell whether to check x or y coordinate

Node *insertNode(Node *root , int content[ ] , unsigned int depth)
{
	//check x or y
	int flag = depth%k ;
	//empty tree
	if(root==NULL)
		return newNode(content);

	if(content[flag] < (root->point[flag]) )
		root->left = insertNode(root->left , content , depth+1);
	else
		root->right = insertNode(root->right , content , depth+1);

	return root;
}

//////////////////////////////////////////////////////////////////////////////////////////////

//insert utility for user,because we need a initiail input,so we define this function then using insertNode to recursive

Node *insert(Node *root,int content[])
{
	return insertNode(root , content , 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////

//check whether the node is existed or not

bool existNode(Node *root , int content[] , unsigned int depth)
{
	if(root == NULL)
		return false;
	if(root->point[0] == content[0] && root->point[1] == content[1])
		return true;
	else
		return false;
             int flag = depth%k;
             if(content[flag] < root->point[flag])
             	return existNode(root->left , content , depth+1);
             else
             	return existNode(root->right , content , depth+1);
}

//////////////////////////////////////////////////////////////////////////////////////////////

//initialize the checking process

bool exist(Node *root , int content[])
{
	return existNode(root , content , 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////

//get the node's location and the parent of the node
/*
tuple<Nose * , Node * , int> findNode(Node *parent , Node *root , int content[] , unsigned int depth)
{
	if(root == NULL)
		return make_tuple(NULL , NULL , -1);
	if(content[0] == root->point[0] && content[1] == root->point[1])
		return make_tuple(parent , root , depth) ;
	
	int flag=depth%2;
	if(content[flag] < root->point[flag])
		return findNode(root , root->left , content , depth+1 );
	else
		return findNode(root , root->right , content , depth+1 );

}

//////////////////////////////////////////////////////////////////////////////////////////////

//initialize the finding process

Node *find(Node *root , int content[])
{
	return findNode( NULL , root , content , 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////
*/

//for those different dimension nodes,get the min node in the current node and its children

Node *minNode(Node *root , Node *leftChild , Node *rightChild , int dimension)
{
	Node *temp=root;
	if(leftChild != NULL && root->point[dimension] > leftChild->point[dimension] )
		temp = leftChild;
	if(rightChild != NULL && root->point[dimension] > rightChild->point[dimension])
		temp = rightChild;
	return temp;
}

//////////////////////////////////////////////////////////////////////////////////////////////

Node *findMin(Node *root , int dimension , unsigned int depth)
{
	if(root == NULL)
		return NULL;
	unsigned int cd = depth%k;
	if( cd == dimension)
	{
		if(root->left != NULL)
			return findMin(root->left , dimension , depth + 1);
		return root;
	}
	else
	{
		return minNode(root , findMin(root->left , dimension , depth + 1) , findMin(root->right , dimension , depth + 1) , dimension);
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////

Node *Min(Node *root , int dimension)
{
	return findMin(root  , dimension , 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////

//check if the nodes are the same

bool samePoint(Node *root , int content[])
{
	if(root->point[0] == content[0] && root->point[1] == content[1])
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////

void copyPoint( int p1[] , int p2[])
{
	p1[0] = p2[0];
	p1[1] = p2[1];
}

/////////////////////////////////////////////////////////////////////////////////////////////

Node *deleteNode(Node *root, int content[] , unsigned int depth)
{	
	if(root == NULL)
		return NULL;

	int flag = depth%k;
	if(samePoint(root , content) == true)
	{
		//first , deal with the right child
		if(root->right != NULL)
			{
				Node *min = Min( root->right , flag );
				copyPoint( root->point , min->point);
				root->right = deleteNode( root->right , min->point , depth + 1 );

			}
		else if(root->left != NULL)
			{	
				Node *min = Min( root->left , flag );
				copyPoint( root->point , min->point );
				root->right = deleteNode( root->left , min->point , depth + 1);

			}
		else
			{
				delete root;
				return NULL;
			}
		//return root;
	}
	
	if(content[flag] > root->point[flag] )
		return deleteNode( root->right , content , depth + 1);
	else
		return deleteNode( root->left , content, depth + 1);
	return root;
	
}

//////////////////////////////////////////////////////////////////////////////////////////

Node *deletepoint(Node *root , int content)
{
	return deleteNode( root , content , 0);
}

//////////////////////////////////////////////////////////////////////////////////////////

void nodeInRange(Node *root , int lu[] , int ld[] , int rd[] , int ru[] ,unsigned int depth)
{
	//if the node is a leaf , check whether it is in the range
	if(root -> left == NULL && root->right == NULL)
	{
		if((root->point[0] <= rd[0] && root->point[0] >= ld[0] && root->point[1] >= ld[1] && root->point[1] <= lu[1])
			return root->point;
	}
	if(root->left != NULL)
	{

	}

}