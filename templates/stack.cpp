#include <iostream>

using namespace std;

template <class T>
class stack;

template <class T>
class item {
  friend class stack<T>;
  private:
  item(T x = 0) {
    inf = x;
    link = NULL;
  }

  T inf;
  item* link;
};


template <class T>
class stack {
  public:
  stack(T x);
  stack();
  ~stack();
  stack(stack const &);

  stack<T>& operator=(stack const &);

  void push(T const &);
  void pop(T&);
  void top(T&) const;
  bool empty() const;
  void print();

  private:
  item<T>* start;
  void delstack();
  void copy(stack const &);
};

// Constructors & operators
template <class T>
stack<T>::stack(T x) {
  start = new item<T>(x);
}

template <class T>
stack<T>::stack() {
  start = NULL;
}

template <class T>
stack<T>::stack(stack const & r) {
  copy(r);
}

template <class T>
stack<T>::~stack() {
  delstack();
}

template <class T>
stack<T>& stack<T>::operator=(stack<T> const & r)  {
  if (this != &r) {
    delstack();
    copy(r);
  }
  return *this;
}

// Stack API
template <class T>
void stack<T>::push(T const & x) {
  item<T> * i = new item<T>(x);
  i->link = start;
  start = i;
}

template <class T>
void stack<T>::pop(T & x) {
  if (!start) {
    throw 1;
  }

  item<T>* temp = start;
  start = start->link;

  x = temp->inf;
  delete temp;
}

template <class T>
void stack<T>::top(T& res) const {
  res = start->inf;
}

template <class T>
bool stack<T>::empty() const {
  return start == NULL;
}

template <class T>
void stack<T>::print() {
  T x;
  while (!empty()) {
    pop(x);
    cout << x << " ";
  }
  cout << endl;
}

// Private helpers
template <class T>
void stack<T>::delstack() {
  item<T> * p;
  while (start) {
    p = start;
    start = start->link;
    delete p;
  }
}

template <class T>
void stack<T>::copy(stack const & r) {
  if (r.start) {
    item<T> *p = r.start;
    item<T> *q = NULL;

    start = new item<T>;
    start->inf = p->inf;
    start->link = q;

    q = start;
    p = p->link;
    while (p) {
      q->link = new item<T>;
      q->link->inf = p->inf;
      q->link->link = NULL;

      q = q->link;
      p = p->link;
    }
  } else {
    start = NULL;
  }
}
