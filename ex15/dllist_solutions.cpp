#include <iostream>
#include "../templates/dllist.cpp"

using namespace std;

int sumFromEnds(DLList<int>& list) {
  list.iterStart();
  elem_link2<int>* s = list.iterSucc();

  list.iterEnd();
  elem_link2<int>* e = list.iterPred();

  int sum = 0;
  while (s && e && s != e && s->succ != e) {
    sum += (s->inf * e->inf);

    s = s->succ;
    e = e->pred;
  }
  if (s && e) {
    sum += (s->inf * e->inf);
  }

  return sum;
}

int sumFromEndsv2(DLList<int>& list) {
  list.iterStart();
  elem_link2<int>* s = list.iterSucc();

  list.iterEnd();
  elem_link2<int>* e = list.iterPred();

  int sum = 0;
  while (s) {
    sum += (s->inf * e->inf);

    if (s == e) {
      sum += (s->inf * e->inf);
    }

    s = s->succ;
    e = e->pred;
  }

  return sum / 2;
}


int main() {
  DLList<int> list1;
  list1.toEnd(3); // 9

  DLList<int> list2;
  list2.toEnd(1);
  list2.toEnd(2);
  list2.toEnd(1); // 5

  DLList<int> list3;
  list3.toEnd(1);
  list3.toEnd(3);
  list3.toEnd(3);
  list3.toEnd(1); // 10

  DLList<int> list4;

  DLList<int> list;
  list.toEnd(1);
  list.toEnd(2);
  list.toEnd(3);
  list.toEnd(4);
  list.toEnd(5);
  list.toEnd(5);
  list.toEnd(4);
  list.toEnd(3);
  list.toEnd(2);
  list.toEnd(1);

  cout << sumFromEnds(list1) << endl;
  cout << sumFromEnds(list2) << endl;
  cout << sumFromEnds(list3) << endl;
  cout << sumFromEnds(list) << endl;
  cout << sumFromEnds(list4) << endl;

  cout << sumFromEndsv2(list1) << endl;
  cout << sumFromEndsv2(list2) << endl;
  cout << sumFromEndsv2(list3) << endl;
  cout << sumFromEndsv2(list) << endl;
  cout << sumFromEndsv2(list4) << endl;
}
