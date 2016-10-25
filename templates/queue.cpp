#include <iostream>

using namespace std;

template <class T>
struct elem_q {
  T inf;
  elem_q<T>* link;
};

template <class T>
class queue
{
  public:
    queue();
    ~queue();
    queue(queue const &);
    queue<T>& operator=(queue const &);
    void push(T const &);
    int pop(T &);
    void head(T &);
    void print();
    bool empty() const;

  private:
    elem_q<T> *front, *rear;
    void delqueue();
    void copy(queue const &);
};

template <class T>
queue<T>::queue() {
  front = rear = NULL;
}

template <class T>
queue<T>::~queue() {
  delqueue();
}

template <class T>
queue<T>::queue(queue const & r) {
  front = rear = NULL;
  copy(r);
}

template <class T>
queue<T>& queue<T>::operator=(queue const & r) {
  if (this != &r) {
    delqueue();
    copy(r);
  }
  return *this;
}

template <class T>
void queue<T>::push(T const & x) {
  elem_q<T> * e =  new elem_q<T>;
  e->inf = x;
  e->link = NULL;

  if (rear) {
    rear->link = e;
    rear = e;
  } else {
    front = rear = e;
  }
}

template <class T>
void queue<T>::head(T & x) {
  if (!rear) {
    throw 1;
  }

  x = front->inf;
}

template <class T>
int queue<T>::pop(T & x) {
  if (!rear) {
    return 0;
  }

  if (front == rear) {
    rear = NULL;
  }

  elem_q<T> * temp = front;
  front = front->link;

  x = temp->inf;
  delete temp;

  return 1;
}

template <class T>
void queue<T>::print() {
  T x;
  while (pop(x)) {
    cout << x << " ";
  }
  cout << endl;
}

template <class T>
bool queue<T>::empty() const {
  return rear == NULL;
}

template <class T>
void queue<T>::delqueue() {
  elem_q<T>* temp;
  while (front) {
    temp = front;
    front = front->link;
    delete temp;
  }

  front = rear = NULL;
}

template <class T>
void queue<T>::copy(queue const & r) {
  elem_q<T> *p = r.front;
  while(p) {
    push(p->inf);
    p = p->link;
  }
}
