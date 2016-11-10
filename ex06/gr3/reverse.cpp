#include <iostream>
#include <fstream>
#include "../../templates/DLList.cpp"
#include "../../templates/llist.cpp"

template <typename T>
void reverse(LList<T>& list) {
  elem_link1<T>* p;

  elem_link1<T>* lastElement = NULL;
  while (true) {
    list.IterStart();

    elem_link1<T>* prev = NULL;
    while ((p = list.Iter()) && p != lastElement) {
      prev = p;
    }
    cout << prev->inf << " "; // last element
    lastElement = prev;
  }
}

template <typename T>
void reverse(DLList<T>& list) {
  list.iterEnd();
  elem_link2<T>* p;
  while ((p = list.iterPred())) {
    cout << p->inf << " ";
  }
  cout << endl;
}

int main() {
  LList<int> ll;
  for (int i = 0; i < 10000; i++) {
    ll.ToEnd(i);
  }
  reverse(ll);


  DLList<int> dl;
  for (int i = 0; i < 10000; i++) {
    dl.toEnd(i);
  }
  // reverse(dl);
}
