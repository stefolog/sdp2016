#include <iostream>
#include "../../templates/tree.cpp"
#include "../../templates/graph.cpp"

using namespace std;

int sumTree(const tree<int> &);
int prodTree(const tree<int> &);
int sum(const tree<int> &, int = 1);

void problem1();
void problem2();

int main() {
  problem1();
  // problem2();
}

void problem1() {
  // 1 y 2 y 3 y 5 n n n y 4 y 6 n n y 7 n n y 0 y 11 n n y 32 n n
  tree<int> t;
  t.Create();
  cout << endl << endl << endl;
  cout << sumTree(t) << endl;
  cout << sum(t) << endl;
}

int sum(const tree<int> & t, int level) {
  if (t.empty()) {
    return level % 2; // !!!
  }

  int leftSum = sum(t.LeftTree(), level + 1);
  int rightSum = sum(t.RightTree(), level + 1);

  if (level % 2 == 1) {
    return t.RootTree() + leftSum + rightSum;
  } else {
    return t.RootTree() * leftSum * rightSum;
  }
}

int sumTree(const tree<int> & t) {
  if (t.empty()) {
    return 1; // !!!
  }
  return t.RootTree() + prodTree(t.LeftTree()) + prodTree(t.RightTree());
}

int prodTree(const tree<int> & t) {
  if (t.empty()) {
    return 0; // !!!
  }
  return t.RootTree() * sumTree(t.LeftTree()) * sumTree(t.RightTree());
}

void problem2() {
  graph<int> g;
  g.addTop(1);
  g.addTop(2);
  g.addTop(3);
  g.addTop(4);
  g.addTop(5);
  g.addTop(6);
  g.addTop(7);

  g.addRib(1, 2);
  g.addRib(1, 3);

  g.addRib(2, 4);
  g.addRib(2, 5);

  g.addRib(3, 5);
  g.addRib(3, 6);
  g.addRib(3, 7);

  g.addRib(5, 3);
  g.addRib(5, 4);
  g.addRib(6, 5);
  g.addRib(7, 6);

  // g.addRib(4, 1); // connect it
}
