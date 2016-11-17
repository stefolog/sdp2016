#include <iostream>
#include <cassert>

using namespace std;

template <class T>
struct node_bin
{
  T inf;
  node_bin *left;
  node_bin *right;
};


template <typename T = int>
class binOrdTree {
public:

  binOrdTree();
  ~binOrdTree();
  binOrdTree(const binOrdTree&);
  binOrdTree& operator=(const binOrdTree&);


  bool empty() const;
  T rootTree() const;
  binOrdTree leftTree() const;
  binOrdTree rightTree() const;
  void create3(const T&, const binOrdTree&, const binOrdTree&);
  void create();

  void print() const
  { pr(root);
    cout << endl;
  }

  void addNode(const T& x)
  { add(root, x);
  }

  void deleteNode(const T&);
  void minTree(T&, binOrdTree&) const;
private:
  node_bin<T>* root;
  void copyTree(const binOrdTree&);
  void copy(node_bin<T>*&, node_bin<T>* const&) const;
  void deleteTree(node_bin<T>*&) const;
  void pr(const node_bin<T>*) const;
  void add(node_bin<T>*&, const T&) const;
};

template <typename T>
binOrdTree<T>::binOrdTree() {
  root = NULL;
}

template <typename T>
binOrdTree<T>::~binOrdTree() {
  deleteTree(root);
}

template <typename T>
binOrdTree<T>::binOrdTree(const binOrdTree<T>& r) {
  copyTree(r);
}

template <typename T>
binOrdTree<T>& binOrdTree<T>::operator=(const binOrdTree<T>& r)
{ if (this != &r)
     { deleteTree(root);
        copyTree(r);
     }
   return *this;
}

template <typename T>
void binOrdTree<T>::copyTree(const binOrdTree<T>& r)
{ copy(root, r.root);
}
template <typename T>
void binOrdTree<T>::copy(node_bin<T>*& pos,
                                             node_bin<T>* const& r) const
{ pos = NULL;
   if (r) { pos = new node_bin<T>;
               assert(pos != NULL);
               pos->inf = r->inf;
               copy(pos->left, r->left);
               copy(pos->right, r->right);
            }
}

template <typename T>
void binOrdTree<T>::deleteTree(node_bin<T>*& p) const
{ if (p)
     { deleteTree(p->left);
        deleteTree(p->right);
        delete p;
         p = NULL;
      }
}

template <typename T>
bool binOrdTree<T>::empty() const
{ return root == NULL;
}

template <typename T>
T binOrdTree<T>::rootTree() const
{ return root->inf;
}

template <typename T>
binOrdTree<T> binOrdTree<T>::leftTree() const
{ binOrdTree<T> t;
   copy(t.root, root->left);
   return t;
}

template <typename T>
binOrdTree<T> binOrdTree<T>::rightTree() const
{ binOrdTree<T> t;
   copy(t.root, root->right);
   return t;
}

template <typename T>
void binOrdTree<T>::pr(const node_bin<T>* p) const {
  if (p) {
    pr(p->left);
    cout << p->inf << " ";
    pr(p->right);
  }
}

template <typename T>
void binOrdTree<T>::add(node_bin<T>*& p, const T& x)
const
{ if (!p)
     { p = new node_bin<T>;
       assert(p != NULL);
       p->inf = x;
       p->left = NULL;
       p->right = NULL;
    }
  else
     if (x < p->inf) add(p->left, x);
     else add(p->right, x);
}

template <typename T>
void binOrdTree<T>::create()
{ root = NULL;
   T x; char c;
   do
   { cout << "> "; cin >> x;
      addNode(x);
      cout << "next elem y/n? "; cin >> c;
    } while (c == 'y');
}

template <typename T>
void binOrdTree<T>::create3(const T& x, const binOrdTree<T>& l, const binOrdTree<T>& r)
{ if (root) deleteTree(root);
   root = new node_bin<T>;
   assert(root != NULL);
   root->inf = x;
   copy(root->left, l.root);
   copy(root->right, r.root);
}

template <typename T>
void binOrdTree<T>::minTree(T& x, binOrdTree<T>& mint) const {
  T a = rootTree();
  if (leftTree().empty()) {
    x = a;
    mint = rightTree();
  } else {
    binOrdTree<T> t, t1 = rightTree();
    leftTree().minTree(x, t);
    mint.create3(a, t, t1);
  }
}

template <typename T>
void binOrdTree<T>::deleteNode(const T& x) {
  if (root) {
    T a = rootTree();
    binOrdTree<T> t1, t2;

    if (a == x && leftTree().empty()) {
      *this = rightTree();
    } else if (a == x && rightTree().empty()) {
      *this = leftTree();
    } else if (a == x) {
      T c;
      t1 = leftTree();
      rightTree().minTree(c, t2);
      create3(c, t1, t2);
    } else if (x < a) {
      t2 = rightTree();
      *this = leftTree();
      deleteNode(x);
      t1 = *this;
      create3(a, t1, t2);
    } else {
      t1 = leftTree();
      *this = rightTree();
      deleteNode(x);
      t2 = *this;
      create3(a, t1, t2);
    }
  }
}
