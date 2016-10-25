#include <iostream>
#include "../templates/stack.cpp"

using namespace std;

template<class T>
void moveAllElements(stack<T>& source, stack<T>& target) {
  while (!source.empty()) {
    T tmp;
    source.pop(tmp);
    target.push(tmp);
  }
}

template<class T>
class stackedQueue {
public:
  void pop(T& x) {
    s.pop(x);
  }

  void push(T x) {
    stack<T> tmp;
    moveAllElements(s, tmp);
    s.push(x);
    moveAllElements(tmp, s);
  }

  void head(T& x) const {
    s.top(x);
  }

  bool empty() const {
    return s.empty();
  }
private:
  stack<T> s;
};

int main() {
  stackedQueue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  q.push(4);

  while (!q.empty()) {
    int x;
    q.pop(x);
    cout << x << endl;
  }
}
