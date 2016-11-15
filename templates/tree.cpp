#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <iostream>

using namespace std;

template <class T>
struct node
{
  T inf;
  node *Left;
  node *Right;
};

template <class T>
class tree
{
  public:
  tree();
  ~tree();
  tree(tree const&);
  tree& operator=(tree const&);
  bool empty()const;
  T RootTree() const;
  node<T>* getRoot() const;
  tree LeftTree()const;
  tree RightTree()const;
  void Create3(T, tree<T>, tree<T>);
  void print() const
  {
    pr(root);
    cout << endl;
  }
  void Create()
  {
    CreateTree(root);
  }
  private:
  node<T> *root;
  void DeleteTree(node<T>* &)const;
  void Copy(node<T> * &, node<T>* const&)const;
  void CopyTree(tree<T> const&);
  void pr(const node<T> *) const;
  void CreateTree(node<T> * &)const;
};

template <class T>
tree<T>::tree()
{
  root = NULL;
}

template <class T>
tree<T>::~tree()
{
  DeleteTree(root);
}

template <class T>
tree<T>::tree(tree<T> const& r)
{
  CopyTree(r);
}

template <class T>
tree<T>& tree<T>::operator=(tree<T> const& r)
{
  if(this!=&r)
  {
    DeleteTree(root);
    CopyTree(r);
  }
  return *this;
}

template <class T>
void tree<T>::DeleteTree(node<T>* &p)const
{
  if(p)
  {
    DeleteTree(p->Left);
    DeleteTree(p->Right);
    delete p;
    p=NULL;
  }
}

template <class T>
void tree<T>::CopyTree(tree<T> const& r)
{
  Copy(root, r.root);
}

template <class T>
void tree<T>::Copy(node<T> * & pos, node<T>* const & r)const
{
  pos=NULL;
  if(r)
  {
    pos = new node<T>;
    pos->inf = r->inf;
    Copy(pos->Left, r->Left);
    Copy(pos->Right, r->Right);
  }
}

template <class T>
bool tree<T>::empty()const
{
  return root==NULL;
}

template <class T>
T tree<T>::RootTree()const
{
  return root->inf;
}

template <class T>
node<T>* tree<T>::getRoot()const
{
  return root;
}

template <class T>
tree<T> tree<T>::LeftTree()const
{
  tree<T> t;
  Copy(t.root, root->Left);
  return t;
}

template <class T>
tree<T> tree<T>::RightTree()const
{
  tree<T> t;
  Copy(t.root, root->Right);
  return t;
}

template <class T>
void tree<T>::pr(const node<T>*p)const
{
  if(p)
  {
    pr(p->Left);
    cout << p->inf << " " ;
    pr(p->Right);
  }
}

template <class T>
void tree<T>::Create3(T x, tree<T> l, tree<T> r)
{
  root = new node<T>;
  root->inf = x;
  Copy(root->Left, l.root);
  Copy(root->Right, r.root);
}

template <class T>
void tree<T>::CreateTree(node<T> * & pos)const
{
  T x;
  char c;

  cout << "root: ";
  cin >> x;
  pos = new node<T>;
  pos->inf=x;
  pos->Left=NULL;
  pos->Right=NULL;
  cout << "Left Tree of: " << x << "  y/n? ";
  cin >> c;
  if(c=='y')
    CreateTree(pos->Left);
  cout << "Right Tree of: " << x << " y/n? ";
  cin >> c;
  if(c=='y')
    CreateTree(pos->Right);
}

#endif // !TREE_H_INCLUDED
