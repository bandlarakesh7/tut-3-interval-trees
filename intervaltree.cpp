#include <iostream>
using namespace std;

struct Interval
{
    int low, high;
};
 
struct ITNode
{
    Interval *i;  // 'i' could also be a normal variable
    int max;
    ITNode *left, *right;
};
 
// A utility function to create a new Interval Search Tree Node
ITNode * newNode(Interval i)
{
    ITNode *temp = new ITNode;
    temp->i = new Interval(i);
    temp->max = i.high;
    temp->left = temp->right = NULL;
    return temp;
};
 
//A utility function to find the min value node 
ITNode *minValueNode(ITNode *root)
{
    ITNode *temp=root;
    //loop down to find the leftmpst leaf
    while(temp->left!=NULL)
        temp=temp->left;
    return temp;
} 
// A utility function to insert a new Interval Search Tree Node
// This is similar to BST Insert.  Here the low value of interval
// is used tomaintain BST property
ITNode *insert(ITNode *root, Interval i)
{
    // Base case: Tree is empty, new node becomes root
    if (root == NULL)
        return newNode(i);
 
    // Get low value of interval at root
    int l = root->i->low;
 
    // If root's low value is smaller, then new interval goes to
    // left subtree
    if (i.low < l)
        root->left = insert(root->left, i);
 
    // Else, new node goes to right subtree.
    else
        root->right = insert(root->right, i);
 
    // Update the max value of this ancestor if needed
    if (root->max < i.high)
        root->max = i.high;
 
    return root;
}
 
// A utility function to check if given two intervals overlap
bool doOVerlap(Interval i1, Interval i2)
{
    if (i1.low <= i2.high && i2.low <= i1.high)
        return true;
    return false;
}
 
// The main function that searches a given interval i in a given
// Interval Tree.
void overlapSearch(ITNode *root, Interval i)
{
    // Base Case, tree is empty
    if (root == NULL) return ;
 
    // If given interval overlaps with root
    if (doOVerlap(*(root->i), i))
    {
        cout << "Overlaps with [" << root->i->low << ", " << root->i->high << "]\n";
    }
 
    // If left child of root is present and max of left child is
    // greater than or equal to given interval, then i may
    // overlap with an interval is left subtree
    if (root->left != NULL && root->left->max >= i.low)
        return overlapSearch(root->left, i);
 
    // Else interval can only overlap with right subtree
    return overlapSearch(root->right, i);
}

int maximum(int a,int b,int c)
{
    if(a>=b&&a>=c)
        return a;
    if(b>=a&&b>=c)
        return b;
    return c;
}

int maximum(int a,int b)
{
    if(a>b)
        return a;
    return b;
}

void updateMax(ITNode*root)
{
    if(root==NULL)
        return ;
    updateMax(root->left);
    updateMax(root->right);
    if(root->left==NULL&&root->right==NULL)
        root->max=root->i->high;
    else if(root->left==NULL)
    {
        root->max=maximum(root->i->high,root->right->max);
    }
    else if(root->right==NULL)
    {
        root->max=maximum(root->i->high,root->left->max);
    }
    else
    root->max=maximum(root->i->high,root->right->max,root->left->max);
}

ITNode *deleteInterval(ITNode *root,Interval x)
{
    if(root==NULL)
        return root;
    //if required interval is in left subtree
    if(x.low<root->i->low)
        root->left=deleteInterval(root->left,x);
    //if required interval is in right subtree
    else if(x.low<root->i->low)
        root->right=deleteInterval(root->right,x);
    //if key is same as root's key
    else
    {
        if(root->left==NULL)
        {
            ITNode *temp=root->right;
            delete(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            ITNode *temp=root->left;
            delete(root);
            return temp;
        }
        //node with two children
        ITNode *temp=minValueNode(root->right);
        root->i=temp->i;
        Interval k={temp->i->low,temp->i->high};
        root->right=deleteInterval(root->right,k);
    }
    return root;
} 
 
void inorder(ITNode *root)
{
    if (root == NULL) return;
 
    inorder(root->left);
 
    cout << "[" << root->i->low << ", " << root->i->high << "]"
         << " max = " << root->max << endl;
 
    inorder(root->right);
}
 
// Driver program to test above functions
int main()
{
    // Let us create interval tree shown in above figure
    Interval ints[] = {{15, 20}, {10, 30}, {17, 19},
        {5, 20}, {12, 15}, {30, 40}
    };
    int n = sizeof(ints)/sizeof(ints[0]);
    ITNode *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, ints[i]);
 
    cout << "Inorder traversal of constructed Interval Tree is\n";
    inorder(root);
 
    Interval x = {14,16};
 
    cout << "\nSearching for interval [" << x.low << "," << x.high << "]\n";
    overlapSearch(root, x);
    Interval y= {10,30};
    root=deleteInterval(root,y);
    updateMax(root);
    inorder(root);
    return 0;
}
