#include <iostream>
#include "../templates/tree.cpp"

using namespace std;

int sumTree(const tree<int> &);
int prodTree(const tree<int> &);
int sum(const tree<int> &, bool = true);

int main() {
  tree<int> t;
  t.Create();
  cout << endl << endl << endl << endl;
  // input: 1 y 2 y 3 y 5 n n n y 4 y 6 n n y 7 n n y 0 y 11 n n y 32 n n
  // expected: 273
  cout << sumTree(t) << endl;
  cout << sum(t) << endl;
}

int sum(const tree<int> & t, bool doSum) {
  if (t.empty()) {
    return doSum ? 1 : 0;
  }

  if (doSum) {
    return t.RootTree() + sum(t.LeftTree(), !doSum) + sum(t.RightTree(), !doSum);
  } else {
    return t.RootTree() * sum(t.LeftTree(), !doSum) * sum(t.RightTree(), !doSum);
  }
}

int sumTree(const tree<int> & t) {
  if (t.empty()) {
    return 1;
  }

  return t.RootTree() + prodTree(t.LeftTree()) + prodTree(t.RightTree());
}

int prodTree(const tree<int> & t) {
  if (t.empty()) {
    return 0;
  }

  return t.RootTree() * sumTree(t.LeftTree()) * sumTree(t.RightTree());
}
