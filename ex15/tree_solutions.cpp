#include <iostream>
#include "../templates/tree.cpp"
#include "../templates/queue.cpp"
#include "../templates/stack.cpp"

using namespace std;

void funkyPrint(tree<char>& t) {
  stack<node<char>* > s;
  queue<node<char>* > q;

  node<char>* n = t.getRoot();
  while (n != NULL) {
    s.push(n);
    n = n->Left;
  }

  while (!s.empty() || !q.empty()) {
    queue<node<char> *> newQ;

    if (!s.empty()) {
      s.pop(n);
      cout << n->inf << " ";

      if (n->Right != NULL) {
        newQ.push(n->Right);
      }
    }

    while (!q.empty()) {
      q.pop(n);
      cout << n->inf << " ";

      if (n->Left != NULL) {
        newQ.push(n->Left);
      }

      if (n->Right != NULL) {
        newQ.push(n->Right);
      }
    }

    q = newQ;
    cout << endl;
  }
}

// 1 y 2 y 4 y a n n y b n n y 5 y c n n y d n n y 3 y 6 y e n n y f n n y 7 y g n n y h n n
/*

                     1
                    / \
                   2   3
                  / \ / \
                 4  5 6  7
                /\  /\ /\ /\
               a b c d ef g h

Expected result:
a
4
2 b
1 5
3 c d
6 7
e f g h
*/
int main() {
  tree<char> t;
  t.Create();
  funkyPrint(t);
}
