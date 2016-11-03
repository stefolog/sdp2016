#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include "../templates/llist.cpp"

using namespace std;

template<typename T>
elem_link1<T>* skip(LList<T>& list, int n) {
  elem_link1<bool> * q = NULL;
  for (int i = 0; i < n; i++) {
    q = list.Iter();
    if (!q) {
      return NULL;
    }
  }
  return q;
}

bool isPrime(long n) {
  LList<bool> numbers;
  for (int i = 0; i <= n; i++) {
    numbers.ToEnd(true);
  }

  numbers.IterStart();
  numbers.Iter();
  numbers.Iter();
  int i = 2;

  elem_link1<bool> * prev;
  elem_link1<bool> * p;
  while ((p = numbers.Iter())) {
    if (!p->inf) {
      prev = p;
      i++;
      continue;
    }

    while (true) {
      elem_link1<bool> * q = skip(numbers, i);
      if (!q) {
        break;
      }
      q->inf = false;
    }
    numbers.IterStart(p); // !
    prev = p;
    i++;
  }

  return prev->inf;
}

int main() {
  cout << "99999: " << isPrime(10) << endl;
}
