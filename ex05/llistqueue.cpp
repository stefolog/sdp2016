#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include "../templates/llist.cpp"

using namespace std;

template <typename T>
class llistqueue {
public:
  void push(T x) {
    data.ToEnd(x);
  }

  T pop() {
    data.IterStart();

    if (data.empty()) {
      throw "EmptyQueue";
    }

    elem_link1<T>* p = data.Iter();
    T x;
    data.DeleteElem(p, x);
    return x;
  }

  T head() {
    if (data.empty()) {
      throw "EmptyQueue";
    }
    data.IterStart();
    elem_link1<T>* p = data.Iter();
    return p->inf;
  }

  bool empty() {
    data.empty();
  }
private:
  LList<T> data;
};

int main() {
  llistqueue<int> q;
  q.push(5);
  q.push(13);
  q.push(42);
  q.push(121);

  try {
    cout << q.pop() << endl;

    cout << q.pop() << endl;

    cout << q.pop() << endl;

    cout << q.pop() << endl;

    cout << q.pop() << endl;
  } catch (const char* e) {
    cout << "Error: " << e << endl;
  }
}
