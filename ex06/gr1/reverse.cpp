#include <iostream>
#include "../../templates/stack.cpp"
#include "../../templates/LList.cpp"
#include "../../templates/DLList.cpp"

template <typename T>
T elementAtIndex(LList<T> & list, int n) {
  list.IterStart();

  elem_link1<T>* p;
  while ((p = list.Iter()) && n > 0) {
    n--;
  }

  return p->inf;
}

template <typename T>
void reverse(LList<T> & list) {
  for (int i = list.len() - 1; i >= 0; i--) {
    cout << elementAtIndex(list, i) << " ";
  }
  cout << endl;
}

template <typename T>
void reverse2(LList<T> & list) {
  stack<T> listInReverseOrder;

  list.IterStart();
  elem_link1<T>* p;
  while ((p = list.Iter())) {
    listInReverseOrder.push(p->inf);
  }

  listInReverseOrder.print();
}


template <typename T>
void reverse(DLList<T> & list) {
  list.iterEnd();
  elem_link2<T>* p;
  while ((p = list.iterPred())) {
    cout << p->inf << " ";
  }
  cout << endl;
}

int main() {
  int size = 1000000;

  DLList<int> dlist;
  for (int i = 0; i < size; i++) {
    dlist.toEnd(i);
  }

  LList<int> llist;
  for (int i = 0; i < size; i++) {
    llist.ToEnd(i);
  }

  reverse(llist);  // 1
  reverse2(llist); // 2
  reverse(dlist);  // 3
}
