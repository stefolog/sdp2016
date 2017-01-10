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

bool subtreesHasEqualSum(const tree<int>&);
bool subtreesHasEqualProduct(const tree<int>&);
bool existsSubtreeWithEqualSumOrProduct(const tree<int>&);
int sumTreeMultipliedByFibonacci(const tree<int>&);

int main() {
  tree<int> t;
  t.Create();


  cout << endl << endl << endl << endl << endl;
  cout << "Result (1.1): " << subtreesHasEqualSum(t) << endl;
  cout << "Result (1.2): " << subtreesHasEqualProduct(t) << endl;
  cout << "Result (1.3): " << existsSubtreeWithEqualSumOrProduct(t) << endl;
  cout << "Result (1.4): " << sumTreeMultipliedByFibonacci(t) << endl;
  cout << endl << endl << endl << endl << endl;
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

bool subtreesHasEqualSum(const tree<int>& t) {
  if (t.empty()) {
    return false;
  }

  return sumOfElements(t.LeftTree()) == sumOfElements(t.RightTree());
}

bool subtreesHasEqualProduct(const tree<int>& t) {
  if (t.empty()) {
    return false;
  }

  return productOfElements(t.LeftTree()) == productOfElements(t.RightTree());
}

bool existsTreeOrSubtreeWithEqualSumOrProduct(const tree<int>& t) {
  if (t.empty()) {
    return false;
  }

  if (subtreesHasEqualSum(t) || subtreesHasEqualProduct(t)) {
    return true;
  }

  return existsSubtreeWithEqualSumOrProduct(t.LeftTree())
      || existsSubtreeWithEqualSumOrProduct(t.RightTree());
}

bool existsSubtreeWithEqualSumOrProduct(const tree<int>& t) {
  return existsTreeOrSubtreeWithEqualSumOrProduct(t.LeftTree())
      || existsTreeOrSubtreeWithEqualSumOrProduct(t.RightTree());
}

int fib(int n) {
  if (n == 0 || n == 1) {
    return 1;
  }
  return fib(n-1) + fib(n-2);
}

int sumTreeMultipliedByFibonacci(const tree<int>& t, int& fibIdx) {
  if (t.empty()) {
    return 0;
  }

  int left = sumTreeMultipliedByFibonacci(t.LeftTree(), fibIdx);
  int root = t.RootTree() * fib(fibIdx);
  fibIdx++;
  int right = sumTreeMultipliedByFibonacci(t.RightTree(), fibIdx);

  return left + root + right;
}

int sumTreeMultipliedByFibonacci(const tree<int>& t) {
  int fibIdx = 0;
  return sumTreeMultipliedByFibonacci(t, fibIdx);
}


