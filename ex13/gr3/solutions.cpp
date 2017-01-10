#include <iostream>
#include "../templates/tree.cpp"

using namespace std;

/*
  Fib Tree
  5 y 6 y 4 n n y 4 n n y 3 n n

  Sum Tree
  130 y 5 y 5 y 3 n n y 2 n n n y 10 n y 4 y 1 n n n

  Prod Tree
  101 y 3 y 2 n n y 1 n n y 1 y 1 y 6 n n n y 1 y 1 n n n
*/

bool hasEqualSubtreesBySum(tree<int>);
bool hasEqualSubtreesByProduct(tree<int>);
bool hasAnyEqualSubtrees(tree<int>);
int sumByFibonacci(tree<int>);

int main() {
  tree<int> input;
  input.Create();

  cout << endl << endl << endl;
  cout << "Result is (1.1.): ";
  cout << hasEqualSubtreesBySum(input) << endl;
  cout << "Result is (1.2.): ";
  cout << hasEqualSubtreesByProduct(input) << endl;
  cout << "Result is (1.3.): ";
  cout << hasAnyEqualSubtrees(input) << endl;
  cout << "Result is (1.4.): ";
  cout << sumByFibonacci(input) << endl;
  cout << endl << endl << endl;
}

int sumOfElements(const tree<int>& t) {
  if (t.empty()) {
    return 0;
  }

  return t.RootTree()
      + sumOfElements(t.LeftTree())
      + sumOfElements(t.RightTree());
}

int productOfElements(const tree<int>& t) {
  if (t.empty()) {
    return 1;
  }

  return t.RootTree()
      * productOfElements(t.LeftTree())
      * productOfElements(t.RightTree());
}

bool hasEqualSubtreesBySum(tree<int> t) {
  if (t.empty()) {
    return false;
  }
  return sumOfElements(t.LeftTree()) == sumOfElements(t.RightTree());
}

bool hasEqualSubtreesByProduct(tree<int> t) {
  if (t.empty()) {
    return false;
  }
  return productOfElements(t.LeftTree()) == productOfElements(t.RightTree());
}

bool hasAnyEqualSubtrees(tree<int> t) {
  if (t.empty()) {
    return false;
  }

  if (hasEqualSubtreesBySum(t) || hasEqualSubtreesByProduct(t)) {
    return true;
  }

  return hasAnyEqualSubtrees(t.LeftTree())
      || hasAnyEqualSubtrees(t.RightTree());
}

int fib(int n) {
  if (n == 0 || n == 1) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}

int sumByFibonacci(tree<int> t, int& fibN, int& fibN1) {
  if (t.empty()) {
    return 0;
  }

  int leftSum = sumByFibonacci(t.LeftTree(), fibN, fibN1);
  int rootSum = t.RootTree() * fibN;

  int fibTemp = fibN1;
  fibN1 = fibN;
  fibN = fibTemp + fibN1;

  int rightSum = sumByFibonacci(t.RightTree(), fibN, fibN1);

  return leftSum + rootSum + rightSum;
}

int sumByFibonacci(tree<int> t) {
  int a = 1;
  int b = 0;
  return sumByFibonacci(t, a, b);
}

bool areMirrors(tree<char> t1, tree<char> t2) {
  if (t1.empty() && t2.empty()) {
    return true;
  }

  if (t1.empty() || t2.empty()) {
    return false;
  }

  return t1.RootTree() == t2.RootTree()
      && areMirrors(t1.LeftTree(), t2.RightTree())
      && areMirrors(t1.RightTree(), t2.LeftTree());
}

bool isMirrored(tree<char> t) {
  if (t.empty()) {
    return false;
  }

  return areMirrors(t.LeftTree(), t.RightTree());
}

