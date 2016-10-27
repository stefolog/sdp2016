#include <iostream>
#include "../../templates/stack.cpp"

using namespace std;

template<typename T>
void moveAllElements(stack<T>& from, stack<T>& to) {
  while (!from.empty()) {
    T tmp;
    from.pop(tmp);
    to.push(tmp);
  }
}

template<typename T>
class PopStackedQueue {
public:
  bool empty() const {
    return popStack.empty();
  }

  void head(T& x) {
    popStack.top(x);
  }

  void pop(T& x) {
    popStack.pop(x);
  }

  void push(T x) {
    stack<T> tmpStack;
    moveAllElements(popStack, tmpStack);
    tmpStack.push(x);
    moveAllElements(tmpStack, popStack);
  }

private:
  stack<T> popStack;
};


template<typename T>
class DynamicStackedQueue {
public:
  bool empty() const {
    return popStack.empty() && pushStack.empty();
  }

  void head(T& x) {
    toPopMode();
    popStack.top(x);
  }

  void pop(T& x) {
    toPopMode();
    popStack.pop(x);
  }

  void push(T x) {
    toPushMode();
    pushStack.push(x);
  }

private:
  void toPopMode() {
    if (!popStack.empty()) {
      return;
    }

    if (!pushStack.empty()) {
      moveAllElements(pushStack, popStack);
    }
  }

  void toPushMode() {
    if (!pushStack.empty()) {
      return;
    }

    if (!popStack.empty()) {
      moveAllElements(popStack, pushStack);
    }
  }

  stack<T> popStack;
  stack<T> pushStack;
};


int main(int argc, char* argv[]) {
  if (argc == 1) {
    cout << "Parameters needed!" << endl;
    return 1;
  }

  if (string(argv[1]) == "popstack") {
    PopStackedQueue<int> queue;

    for (int i = 0; i < 10000000; i++) {
      queue.push(i);
    }
    while(!queue.empty()) {
      int x;
      queue.pop(x);
      cout << x << " ";
    }
  } else if (string(argv[1]) == "dynstack-seq") {
    DynamicStackedQueue<int> queue;

    for (int i = 0; i < 10000000; i++) {
      queue.push(i);
    }

    while(!queue.empty()) {
      int x;
      queue.pop(x);
      cout << x << " ";
    }
  } else if (string(argv[1]) == "dynstack-mixed") {
    DynamicStackedQueue<int> queue;

    for (int k = 0; k < 1000000; k++) {
      for (int i = 0; i < 10; i++) {
        queue.push(i);
      }

      while(!queue.empty()) {
        int x;
        queue.pop(x);
        cout << x << " ";
      }
    }
  }

  return 0;
}
