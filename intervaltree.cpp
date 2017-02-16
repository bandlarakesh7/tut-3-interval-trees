#include <iostream>
using namespace std;
 
struct Interval
{
    int low, high;
};
 
struct ITNode
{
    Interval *i;  
    int max;
    ITNode *left, *right;
};
 
ITNode * newNode(Interval i)
{
    ITNode *temp = new ITNode;
    temp->i = new Interval(i);
    temp->max = i.high;
    temp->left = temp->right = NULL;
return temp;};
 
ITNode *insert(ITNode *root, Interval i)
{
    if (root == NULL)
        return newNode(i);
 
    int l = root->i->low;
 
    if (i.low < l)
        root->left = insert(root->left, i);
 
    else
        root->right = insert(root->right, i);
 
    if (root->max < i.high)
        root->max = i.high;
 
    return root;
}
 
bool doOVerlap(Interval i1, Interval i2)
{
    if (i1.low <= i2.high && i2.low <= i1.high)
        return true;
    return false;
}
ITNode *minValueNode(ITNode *root)
{
    ITNode *temp=root;
    //loop down to find the leftmpst leaf
    while(temp->left!=NULL)
        temp=temp->left;
    return temp;
}  
Interval *overlapSearch(ITNode *root, Interval i)
{
    if (root == NULL) return NULL;
 
    if (doOVerlap(*(root->i), i))
        return root->i;

    if (root->left != NULL && root->left->max >= i.low)
        return overlapSearch(root->left, i);
 
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
    if(x.low<root->i->low)
        root->left=deleteInterval(root->left,x);
    else if(x.low>root->i->low)
        root->right=deleteInterval(root->right,x);
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
 
int main()
{
    Interval ints[] = {{15, 20}, {10, 30}, {17, 19},
        {5, 20}, {12, 15}, {30, 40}
    };
    int n = sizeof(ints)/sizeof(ints[0]);
    ITNode *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, ints[i]);
        
        Interval x[] = {{6, 7},{14,16},{21,23}};
 
 for(int i=0;i<3;i++)
 {
    cout << "[" << x[i].low << "," << x[i].high << "]";
    Interval *res = overlapSearch(root, x[i]);
    if (res == NULL)
        cout << "overlaps with none\n";
    else
        cout << "overlaps with [" << res->low << ", " << res->high << "]\n";
}   insert(root,{14,16});insert(root,{21,23});
cout << endl<< "Inorder traversal of constructed Interval Tree is\n";
    inorder(root);
    root=deleteInterval(root,{14,16});
cout << endl<< "Inorder traversal of constructed Interval Tree is\n";
    inorder(root);
return 0;
}
