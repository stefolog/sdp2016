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
    prev = p;
    i++;
    if (!p->link) {
      break;
    }
    numbers.IterStart(p->link); // !
  }

  return prev->inf;
}

int main() {
  cout << "127: " << isPrime(127) << endl;
  cout << "123: " << isPrime(123) << endl;
}
