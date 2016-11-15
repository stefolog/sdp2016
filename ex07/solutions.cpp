#include <iostream>
#include "../templates/tree.cpp"

template <class T>
bool find(T x, tree<T>& t) {
  if (t.empty()) {
    return false;
  }

  if (t.getRoot()->inf == x) {
    return true;
  }

  if (t.getRoot()->inf > x) {
    tree<T> left = t.LeftTree();
    return find(x, left);
  } else {
    tree<T> right = t.RightTree();
    return find(x, right);
  }
}

void problem1() {
  tree<int> tree1;
  tree1.Create3(1, tree<int>(), tree<int>());

  tree<int> tree5;
  tree5.Create3(5, tree<int>(), tree<int>());

  tree<int> tree2;
  tree2.Create3(2, tree1, tree<int>());

  tree<int> tree4;
  tree4.Create3(4, tree<int>(), tree5);

  tree<int> tree3;
  tree3.Create3(3, tree2, tree4);

  tree<int> tree7;
  tree7.Create3(7, tree<int>(), tree<int>());

  tree<int> t;
  t.Create3(6, tree3, tree7);
  cout << "find(5, t): " << find(5, t) << endl;

  cout << endl << endl << endl << endl;
  t.print();

  // 6 y 3 y 2 y 1 n n n y 4 y 5 n n n y 7 n n
  // tree<int> tt;
  // tt.Create();
  // tt.print();
}

bool containsWord(tree<char>& t, string word, int i = 0) {
  if (t.empty()) {
    return false;
  }

  if (t.LeftTree().empty() && t.RightTree().empty()) {
    return word[i] == t.getRoot()->inf && word.length() == i + 1;
  }

  if (word.length() == i) {
    return false;
  }

  if (t.getRoot()->inf == word[i]) {
    tree<char> left = t.LeftTree();
    tree<char> right = t.RightTree();
    return containsWord(left, word, i + 1) || containsWord(right, word, i + 1);
  } else {
    return false;
  }
}

void problem2() {
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
  tree<char> ct;
  ct.Create();
  cout << endl << endl << endl << endl;
  ct.print();

  cout << containsWord(ct, "baba") << " == 1" << endl;
  cout << containsWord(ct, "buuu") << " == 1" << endl;
  cout << containsWord(ct, "ba") << " == 0" << endl;
  cout << containsWord(ct, "babx") << " == 0" << endl;
  cout << containsWord(ct, "babxy") << " == 0" << endl;
}

struct OperationNode {
  char operation;
  int value;

  OperationNode() {
    operation = 0;
    value = 0;
  }

  OperationNode(char operation) {
    this->operation = operation;
    value = 0;
  }

  OperationNode(int value) {
    this->value = value;
    operation = 0;
  }

  bool isOperation() {
    return this->operation != 0;
  }
};

int calculate(tree<OperationNode>& t) {
  if (t.empty()) {
    return 0;
  }

  OperationNode node = t.getRoot()->inf;
  if (!node.isOperation()) {
    return node.value;
  } else {
    tree<OperationNode> left = t.LeftTree();
    tree<OperationNode> right = t.RightTree();
    int leftValue = calculate(left);
    int rightValue = calculate(right);

    node.applyOperation(leftValue, rightValue);

    switch (node.operation) {
      case '*': return leftValue * rightValue;
      case '+': return leftValue + rightValue;
      case '-': return leftValue - rightValue;
      case '/': return leftValue / rightValue;
      default: return 0;
    }
  }
}

void problem3() {
  /*
                -
               /\
              *  5
            /  \
           *    4
         /   \
        +     -
       /\     /\
      5  2  10  3
  */
  tree<OperationNode> t1;
  t1.Create3(OperationNode(10), tree<OperationNode>(), tree<OperationNode>());
  tree<OperationNode> t2;
  t2.Create3(OperationNode(3), tree<OperationNode>(), tree<OperationNode>());

  tree<OperationNode> t;
  t.Create3(OperationNode('-'), t1, t2);

  cout << calculate(t) << endl;
}

int main() {
  // problem1();
  // problem2();
  problem3();
}
