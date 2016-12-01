#include <iostream>
#include "../templates/tree.cpp"
#include "../templates/binOrdTree.cpp"

using namespace std;

tree<int> applyOperation(tree<int>, tree<int>, char, int);
tree<int> applyOperation(tree<int>, tree<int>, char);

template <typename T>
bool find(binOrdTree<T>, T);

void problem1();
void problem2();

template <typename T>
class Iterator {
public:
  virtual bool hasNext() = 0;
  virtual T next() = 0;
};

template <typename T>
class TreeSetIterator : Iterator<T> {
public:
  TreeSetIterator(binOrdTree<T> data) {
    this->data = data;
  }

  virtual bool hasNext() {
    return !data.empty();
  }

  virtual T next() {
    T x = data.rootTree();
    data.deleteNode(x);
    return x;
  }
private:
  binOrdTree<T> data;
};

template <typename T, typename K>
class Pair {
public:
  T x;
  K y;

  bool operator==(const Pair<T, K>& other) const {
    return other.x == x && other.y == y;
  }

  bool operator<(const Pair<T, K>& other) const {
    return x < other.x || (x == other.x && y < other.y);
  }

  bool operator>(const Pair<T, K>& other) const {
    return x > other.x || (x == other.x && y > other.y);
  }
};

template <typename T, typename K>
ostream& operator<<(ostream& out, const Pair<T, K>& other) {
  out << "(" << other.x << " " << other.y << ")";
  return out;
}

template <typename T>
class TreeSet {
public:
  void add(T);
  void remove(T);
  bool contains(T) const;
  bool empty() const;
  void print() const;
  int size() const;

  TreeSetIterator<T> iterator() const {
    return TreeSetIterator<T>(data);
  }

  TreeSet<T> unionSet(TreeSet<T>) const;
  TreeSet<T> intersectSet(TreeSet<T>) const;

  TreeSet<T>& addAll(TreeSet<T>);

  template <typename K>
  TreeSet<Pair<T,K> > cartesianProduct(TreeSet<K> other) const {
    TreeSet<Pair<T,K> > result;

    TreeSetIterator<T> setA = this->iterator();
    while (setA.hasNext()) {
      TreeSetIterator<K> setB = other.iterator();
      T x = setA.next();
      while (setB.hasNext()) {
        K y = setB.next();

        Pair<T, K> pair = { x, y };
        result.add(pair);
      }
    }

    return result;
  }

  TreeSet<T> operator+(TreeSet<T> other) {
    return unionSet(other);
  }

  TreeSet<T> operator^(TreeSet<T> other) {
    return intersectSet(other);
  }

private:
  binOrdTree<T> data;

  void addAll(binOrdTree<T>);
};

int main() {
  // problem1();
  problem2();
}

/*
 Problem 2 solution
*/
void problem2() {
  TreeSet<int> setA;
  setA.add(5);
  setA.add(5);
  setA.add(2);
  setA.add(5);
  setA.add(3);
  setA.add(3);
  setA.print();

  TreeSet<int> setB;
  setB.add(5);
  setB.add(5);
  setB.add(2);
  setB.add(4);
  setB.add(6);
  setB.add(7);
  setB.print();

  (setA + setB + setA).print();
  (setA ^ setA).print();
  (setA ^ setB).print();

  TreeSet<char> setC;
  setC.add('a');
  setC.add('b');
  setC.add('c');
  setC.add('a');
  setC.add('a');
  setC.add('c');
  setC.print();

  setA.cartesianProduct(setC).cartesianProduct(setA.cartesianProduct(setC)).print();
}

template <typename T>
TreeSet<T>& TreeSet<T>::addAll(TreeSet<T> other) {
  addAll(other.data);
  return *this;
}

template <typename T>
void TreeSet<T>::addAll(binOrdTree<T> other) {
  if (other.empty()) {
    return;
  }

  add(other.rootTree());
  addAll(other.leftTree());
  addAll(other.rightTree());
}

template <typename T>
TreeSet<T> TreeSet<T>::unionSet(TreeSet<T> other) const {
  TreeSet<T> result = *this;

  TreeSetIterator<T> setB = other.iterator();
  while (setB.hasNext()) {
    result.add(setB.next());
  }

  return result;
}

template <typename T>
TreeSet<T> TreeSet<T>::intersectSet(TreeSet<T> other) const {
  TreeSetIterator<T> setA = iterator();

  TreeSet<T> result;
  while (setA.hasNext()) {
    T i = setA.next();
    if (other.contains(i)) {
      result.add(i);
    }
  }

  return result;
}

template <typename T>
bool find(binOrdTree<T> tree, T x) {
  if (tree.empty()) {
    return false;
  }

  if (tree.rootTree() == x) {
    return true;
  } else if (x < tree.rootTree()) {
    return find(tree.leftTree(), x);
  } else {
    return find(tree.rightTree(), x);
  }
}

template <typename T>
int size(binOrdTree<T> tree) {
  if (tree.empty()) {
    return 0;
  }

  return 1 + size(tree.leftTree()) + size(tree.rightTree());
}


template <typename T>
void TreeSet<T>::add(T x) {
  if (!contains(x)) {
    data.addNode(x);
  }
}

template <typename T>
void TreeSet<T>::remove(T x) {
  data.deleteNode(x);
}

template <typename T>
bool TreeSet<T>::contains(T x) const {
  return find(data, x);
}

template <typename T>
bool TreeSet<T>::empty() const {
  return data.empty();
}

template <typename T>
void TreeSet<T>::print() const {
  data.print();
}

template <typename T>
int TreeSet<T>::size() const {
  return size(data);
}



/*
 Problem 1 solution
*/
void problem1() {
  tree<int> mainTree;
  tree<int> delta;
  char operation = '*';

  mainTree.Create(); // 1 y 1 y 2 y 4 n n n y 3 n n y 1 y 2 n y 5 n n y 3 n n
  delta.Create(); // 5 y 3 n n n

  // 1 y 1 y 2 y 4 n n n y 3 n n y 1 y 2 n y 5 n n y 3 n n 5 y 3 n n n

  cout << endl << endl << endl << endl << endl;
  applyOperation(mainTree, delta, operation).print();
}

tree<int> applyOperation(
  tree<int> mainTree,
  tree<int> delta,
  char operation,
  int lastElement) {

  if (mainTree.empty()) {
    return tree<int>();
  }

  int leftOperand = mainTree.getRoot()->inf;
  int rightOperand = delta.empty() ? lastElement : delta.getRoot()->inf;

  int newRootElement = 0;
  switch (operation) {
    case '*':
      newRootElement = leftOperand * rightOperand;
      break;
    case '+':
    default:
      newRootElement = leftOperand + rightOperand;
  }

  tree<int> result;
  result.Create3(leftOperand * rightOperand,
    applyOperation(mainTree.LeftTree(), delta.empty() ? delta : delta.LeftTree(), operation, rightOperand),
    applyOperation(mainTree.RightTree(), delta.empty() ? delta : delta.RightTree(), operation, rightOperand)
  );
  return result;
}

tree<int> applyOperation(tree<int> mainTree, tree<int> delta, char operation) {
  if (delta.empty()) {
    return mainTree;
  }
  return applyOperation(mainTree, delta, operation, delta.getRoot()->inf);
}
