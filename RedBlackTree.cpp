#include <bits/stdc++.h>
using namespace std;

struct Node
{
  int key;
  int color;
  Node *parent;
  Node *left;
  Node *right;
};

typedef Node *NodeRB;

class RBtree
{
private:
  NodeRB root;
  NodeRB q;

public:
  RBtree();
  void CreateNullNode(NodeRB node, NodeRB parent);
  void Delete(NodeRB node, int key);
  void DeleteFix(NodeRB x);
  void Insert(int key);
  void InsertFix(NodeRB x);
  void Innew(NodeRB u, NodeRB v);
  void leftRotate(NodeRB x);
  void rightRotate(NodeRB x);
  void Search(int key);
  void Print(NodeRB root, string indent, bool last);
  bool check(){
    if(root==nullptr)
        return true;
    return false;
}
  NodeRB minimum(NodeRB node)
  {
    while (node->left != q)
    {
      node = node->left;
    }
    return node;
  }

  NodeRB maximum(NodeRB node)
  {
    while (node->right != q)
    {
      node = node->right;
    }
    return node;
  }

  NodeRB successor(NodeRB x)
  {
    if (x->right != q)
    {
      return minimum(x->right);
    }

    NodeRB y = x->parent;
    while (y != q && x == y->right)
    {
      x = y;
      y = y->parent;
    }
    return y;
  }

  NodeRB predecessor(NodeRB x)
  {
    if (x->left != q)
    {
      return maximum(x->left);
    }

    NodeRB y = x->parent;
    while (y != q && x == y->left)
    {
      x = y;
      y = y->parent;
    }

    return y;
  }

  NodeRB getRoot()
  {
    return this->root;
  }

  void deleteNode(int key)
  {
    Delete(this->root, key);
  }

  void printTree()
  {
    if (root)
    {
      Print(this->root, "", true);
    }
  }
};

RBtree::RBtree()
{
  q = new Node;
  q->color = 0;
  q->left = nullptr;
  q->right = nullptr;
  root = q;
}

void RBtree::CreateNullNode(NodeRB node, NodeRB parent)
{
  node->key = 0;
  node->parent = parent;
  node->left = nullptr;
  node->right = nullptr;
  node->color = 0;
}


void RBtree::leftRotate(NodeRB x)
{
  NodeRB y = x->right;
  x->right = y->left;
  if (y->left != q)
  {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr)
  {
    this->root = y;
  }
  else if (x == x->parent->left)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void RBtree::rightRotate(NodeRB x)
{
  NodeRB y = x->left;
  x->left = y->right;
  if (y->right != q)
  {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr)
  {
    this->root = y;
  }
  else if (x == x->parent->right)
  {
    x->parent->right = y;
  }
  else
  {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

void RBtree::DeleteFix(NodeRB x)
{
  NodeRB s;
  while (x != root && x->color == 0)
  {
    if (x == x->parent->left)
    {
      s = x->parent->right;
      if (s->color == 1)
      {
        s->color = 0;
        x->parent->color = 1;
        leftRotate(x->parent);
        s = x->parent->right;
      }

      if (s->left->color == 0 && s->right->color == 0)
      {
        s->color = 1;
        x = x->parent;
      }
      else
      {
        if (s->right->color == 0)
        {
          s->left->color = 0;
          s->color = 1;
          rightRotate(s);
          s = x->parent->right;
        }

        s->color = x->parent->color;
        x->parent->color = 0;
        s->right->color = 0;
        leftRotate(x->parent);
        x = root;
      }
    }
    else
    {
      s = x->parent->left;
      if (s->color == 1)
      {
        s->color = 0;
        x->parent->color = 1;
        rightRotate(x->parent);
        s = x->parent->left;
      }

      if (s->right->color == 0 && s->right->color == 0)
      {
        s->color = 1;
        x = x->parent;
      }
      else
      {
        if (s->left->color == 0)
        {
          s->right->color = 0;
          s->color = 1;
          leftRotate(s);
          s = x->parent->left;
        }

        s->color = x->parent->color;
        x->parent->color = 0;
        s->left->color = 0;
        rightRotate(x->parent);
        x = root;
      }
    }
  }
  x->color = 0;
}

void RBtree::Innew(NodeRB u, NodeRB v)
{
  if (u->parent == nullptr)
  {
    root = v;
  }
  else if (u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void RBtree::Delete(NodeRB node, int key)
{
  NodeRB z = q;
  NodeRB x, y;
  while (node != q)
  {
    if (node->key == key)
    {
      z = node;
    }

    if (node->key <= key)
    {
      node = node->right;
    }
    else
    {
      node = node->left;
    }
  }

  if (z == q)
  {
    cout << "Key not found!!!\n";
    return;
  }

  y = z;
  int y_original_color = y->color;
  if (z->left == q)
  {
    x = z->right;
    Innew(z, z->right);
  }
  else if (z->right == q)
  {
    x = z->left;
    Innew(z, z->left);
  }
  else
  {
    y = minimum(z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z)
    {
      x->parent = y;
    }
    else
    {
      Innew(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    Innew(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  delete z;
  if (y_original_color == 0)
  {
    DeleteFix(x);
  }
}

void RBtree::InsertFix(NodeRB k)
{
  NodeRB u;
  while (k->parent->color == 1)
  {
    if (k->parent == k->parent->parent->right)
    {
      u = k->parent->parent->left;
      if (u->color == 1)
      {
        u->color = 0;
        k->parent->color = 0;
        k->parent->parent->color = 1;
        k = k->parent->parent;
      }
      else
      {
        if (k == k->parent->left)
        {
          k = k->parent;
          rightRotate(k);
        }
        k->parent->color = 0;
        k->parent->parent->color = 1;
        leftRotate(k->parent->parent);
      }
    }
    else
    {
      u = k->parent->parent->right;

      if (u->color == 1)
      {
        u->color = 0;
        k->parent->color = 0;
        k->parent->parent->color = 1;
        k = k->parent->parent;
      }
      else
      {
        if (k == k->parent->right)
        {
          k = k->parent;
          leftRotate(k);
        }
        k->parent->color = 0;
        k->parent->parent->color = 1;
        rightRotate(k->parent->parent);
      }
    }
    if (k == root)
    {
      break;
    }
  }
  root->color = 0;
}
void RBtree::Insert(int key)
{
  NodeRB node = new Node;
  node->parent = nullptr;
  node->key = key;
  node->left = q;
  node->right = q;
  node->color = 1;

  NodeRB y = nullptr;
  NodeRB x = this->root;

  while (x != q)
  {
    y = x;
    if (node->key < x->key)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }

  node->parent = y;
  if (y == nullptr)
  {
    root = node;
  }
  else if (node->key < y->key)
  {
    y->left = node;
  }
  else
  {
    y->right = node;
  }

  if (node->parent == nullptr)
  {
    node->color = 0;
    return;
  }

  if (node->parent->parent == nullptr)
  {
    return;
  }

  InsertFix(node);
}

void RBtree::Search(int data){
  if(RBtree::check())
     {
        cout<<"\nEmpty Tree\n";
        return;
     }

     Node *p=root;
     int flag=0;
     while(p!=NULL&& flag==0)
     {
            if(p->key==data)
                flag=1;
            if(flag==0)
            {
                 if(p->key<data) p=p->right;
                 else
                      p=p->left;
            }
     }
     if(flag==0)
          cout<<"\nNot Found!!!\n";
     else
        cout<<"\nFound!!!\n";
}
void RBtree::Print(NodeRB root, string indent, bool last)
  {

    if (root != q)
    {
      cout << indent;
      if (last)
      {
        cout << "RightNode: ";
        indent += "===========";
      }
      else
      {
        cout << "LeftNode: ";
      }
      string sColor = root->color ? "RED" : "BLACK";
      cout << root->key << "(" << sColor << ")" << endl;
      Print(root->left, indent, false);
      Print(root->right, indent, true);
    }
  }
int main(){
    RBtree A;
    int catchkey;
    system("Color 3f");
	cout << "\n\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\ WELCOME TO RB_tree Visualize \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n";
	cout << "\t\t\t--------------------\n"
		 << endl;

	cout << "\t\tCurrent date&time : ";
	time_t now;
	time(&now);
	printf("%s\n", ctime(&now));
	;

	cout << "\t\t\t--------------------\n"
		 << endl;
	cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n";
	int a;
	cout<<"\t\t\tPress 1 to start visualization\n";
	cin >> a;
	if(a==1){
        do
			{
				system("cls");

				cout << endl
					 << "\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb Red-Black Tree Visualize Menu Screen \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n"
					 << endl
					 << endl;
				cout << "\t\tPRESS [1] To Insert" << endl;
				cout << "\t\tPRESS [2] To Delete" << endl;
				cout << "\t\tPRESS [3] To Find" << endl;
				cout << "\t\tPRESS [4] To Print" << endl;
				cout << "\t\tPRESS [0] To Exit" << endl
					 << endl;
				cout << "\tPLEASE ENTER A SELECTION AND PRESS RETURN KEY: \n\n";
				cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n\n";

				while(cin>>catchkey&&catchkey!=1&&catchkey!=2&&catchkey!=3&&catchkey!=4&&catchkey!=5&&catchkey!=6&&catchkey!=0)
				cout<<"\tJust press in range 0->4. Please press again!!!\n";
				switch (catchkey)
				{
				case 1:
				    int x;
				    cout<<"\tEnter the value you want to insert: ";
				    cin>>x;
					A.Insert(x);
					break;
				case 2:
				    int y;
				    cout<<"\tEnter the value you want to delete: ";
				    cin>>y;
					A.deleteNode(y);
					break;
				case 3:
				    int z;
				    cout<<"\tEnter the value you want to find: ";
				    cin>>z;
					A.Search(z);
					break;
				case 4:
                    cout << "\n\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\  Red-Black Tree \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n";
                    cout << "\t\t\t--------------------\n"
		                 << endl;
					cout<<"ROOT ";
					A.printTree();
					break;
				default:
					break;
				}
				system("pause");
			} while (catchkey != 0);
	}
}
