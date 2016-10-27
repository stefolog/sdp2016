#include<iostream>
#include "../../templates/stack.cpp"

using namespace std;

/* call stack
  main: [int x | char c]
  f1: [int a, int b]
  f2: [int a]
  f1: [int a, int b]
  f2: [int a]
  f1: [int a, int b]
  f2: [int a]
  f1: [int a, int b]
*/

/*
  fibonacci
  7

  1, 1, 2, 3, 5, 8, 13
  |8|
  |5|
  |3|
  |2|
  |1|
  |1|
*/

void fibonacci(int n, stack<int>& prev) {
  if (n <= 2) {
    return;
  } else {
    int an1, an2;
    prev.pop(an1);
    prev.pop(an2);
    prev.push(an2);
    prev.push(an1);
    prev.push(an1 + an2);
    fibonacci(n - 1, prev);
  }
}

int main() {
  stack<int> prev;
  prev.push(1);
  prev.push(1);
  fibonacci(7, prev);

  int res;
  prev.top(res);

  cout << res << endl;
}
