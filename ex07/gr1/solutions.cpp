#include <iostream>
#include "../../templates/binOrdTree.cpp"
#include "../../templates/tree.cpp"

using namespace std;

template <typename T>
bool contains(const binOrdTree<T>& t, const T x) {
  if (t.empty()) {
    return false;
  }

  if (t.rootTree() == x) {
    return true;
  } else if (t.rootTree() < x) {
    return contains(t.rightTree(), x);
  } else {
    return contains(t.leftTree(), x);
  }
}

void problem1() {
  binOrdTree<int> t;
  t.addNode(5);
  t.addNode(7);
  t.addNode(6);
  t.addNode(3);
  t.addNode(4);
  t.addNode(2);
  t.addNode(1);

  t.print();

  cout << contains(t, 1) << " == 1" << endl;
  cout << contains(t, 5) << " == 1" << endl;
  cout << contains(t, 4) << " == 1" << endl;
  cout << contains(t, 8) << " == 0" << endl;
  cout << contains(t, 10) << " == 0" << endl;
}

void problem1_tree() {
  tree<int> t6;
  t6.Create3(6, tree<int>(), tree<int>());

  tree<int> t7;
  t7.Create3(7, t6, tree<int>());

  tree<int> t4;
  t4.Create3(4, tree<int>(), tree<int>());

  tree<int> t1;
  t1.Create3(1, tree<int>(), tree<int>());

  tree<int> t2;
  t2.Create3(2, t1, tree<int>());

  tree<int> t3;
  t3.Create3(3, t2, t4);

  tree<int> t;
  t.Create3(5, t3, t7);

  t.print();

  tree<int> tt;
  tt.Create();
  // 5 y 3 y 2 y 1 n n n y 4 n n y 7 y 6 n n n
  cout << endl << endl << endl;
  tt.print();
}

// b y a y b y x y a n n y y n y z n n y a n n n y u y u n y u n n n
/*
           b
          / \
         a   u
        /   /
       b   u
      / \   \
     x   a   u
    / \
   a   y
        \
         z
*/
bool containsWord(const tree<char>& t, string word, int i = 0) {
  if (t.empty()) {
    return false;
  }

  if (word.length() == i) {
    return false;
  }

  if (t.LeftTree().empty() && t.RightTree().empty()) {
    return (word.length() == i + 1)
        && (word[i] == t.getRoot()->inf);
  }

  return containsWord(t.LeftTree(), word, i + 1)
      || containsWord(t.RightTree(), word, i + 1);
}

void problem2() {
  tree<char> t;
  t.Create();
  cout << endl << endl << endl;
  cout << containsWord(t, "baba") << " == 1" << endl;
  cout << containsWord(t, "buuu") << " == 1" << endl;
  cout << containsWord(t, "babxyz") << " == 1" << endl;
  cout << containsWord(t, "bab") << " == 0" << endl;
  cout << containsWord(t, "bu") << " == 0" << endl;
  cout << containsWord(t, "buu") << " == 0" << endl;
  cout << containsWord(t, "babx") << " == 0" << endl;
  cout << containsWord(t, "alabala") << " == 0" << endl;
  cout << containsWord(t, "babxyzzz") << " == 0" << endl;
  // b y a y b y x y a n n y y n y z n n y a n n n y u y u n y u n n n
}

struct OpNode {
  char operation;
  int value;

  OpNode() {
    this->operation = 0;
    this->value = 0;
  }

  OpNode(char operation) {
    this->operation = operation;
    this->value = 0;
  }

  OpNode(int value) {
    this->operation = 0;
    this->value = value;
  }

  bool isOperation() {
    return this->operation != 0;
  }
};

int calculate(const tree<OpNode>& t) {
  if (t.empty()) {
    return 0;
  }

  if (!(t.getRoot()->inf).isOperation()) {
    return (t.getRoot()->inf).value;
  }

  int left = calculate(t.LeftTree());
  int right = calculate(t.RightTree());

  switch ((t.getRoot()->inf).operation) {
    case '*': return left * right;
    case '+': return left + right;
    case '-': return left - right;
    case '/': return right == 0 ? 0 : left / right;
    default: return 0;
  }
}

void problem3() {
  tree<OpNode> t10;
  t10.Create3(OpNode(10), tree<OpNode>(), tree<OpNode>());

  tree<OpNode> t3;
  t3.Create3(OpNode(3), tree<OpNode>(), tree<OpNode>());

  tree<OpNode> t5;
  t5.Create3(OpNode(5), tree<OpNode>(), tree<OpNode>());

  tree<OpNode> t2;
  t2.Create3(OpNode(2), tree<OpNode>(), tree<OpNode>());

  tree<OpNode> t_1;
  t_1.Create3(OpNode('-'), t10, t3);

  tree<OpNode> t_2;
  t_2.Create3(OpNode('+'), t2, t5);

  tree<OpNode> t;
  t.Create3(OpNode('*'), t_2, t_1);

  cout << calculate(t) << " == 49" << endl;
}

int main() {
  // problem1();
  // problem1_tree();
  // problem2();
  problem3();
}
















