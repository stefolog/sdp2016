#include <iostream>
#include "../../templates/tree.cpp"
#include "../../templates/binOrdTree.cpp"

using namespace std;

tree<int> treeWithRoot(int);

template<typename T>
bool find(T, binOrdTree<T>);

template<typename T>
int size(binOrdTree<T>);

int applyOperation(int, int, char);
tree<int> applyOperation(tree<int> leftOperands, tree<int> rightOperands, char op);

template <typename T, typename K>
struct Pair {
  T x;
  K y;

  bool operator==(const Pair<T, K> & other) const {
    return x == other.x && y == other.y;
  }

  bool operator<(const Pair<T, K> & other) const {
    return x < other.x || (x == other.x && y < other.y);
  }
};

template <typename T, typename K>
ostream& operator<<(ostream& out, const Pair<T, K>& obj) {
  out << "(" << obj.x << " " << obj.y << ")";
  return out;
}

template <typename T>
class TreeSetIterator : Iterator<T> {
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

  bool hasNext() {
    return !data.empty();
  }

  T next() {
    T result = data.rootTree();
    data.deleteNode(result);
    return result;
  }
private:
  binOrdTree<T> data;
};

template <typename T>
class Set {
  virtual void add(T) = 0;
  virtual void remove(T) = 0;
  virtual bool contains(T) const = 0;
  virtual bool empty() const = 0;
  virtual void print() const = 0;
  virtual int size() const = 0;

  virtual Iterator<T> iterator() const = 0;

  virtual Set<T> unionSet(Set<T>) const = 0;
  virtual Set<T> intersectSet(Set<T>) const = 0;
};

/**
  Requires implementation of:
    operator==
    operator<
    operator<<
  for type T
*/
template <typename T>
class TreeSet : Set<T> {
public:
  void add(T);
  void remove(T);
  bool contains(T) const;
  bool empty() const;
  void print() const;
  int size() const;

  const Iterator<T>& iterator() const {
    return TreeSetIterator<T>(data);
  }

  TreeSet<T> unionSet(TreeSet<T>) const;
  TreeSet<T> intersectSet(TreeSet<T>) const;

  template <typename K>
  TreeSet<Pair<T, K> > cartesianProduct(TreeSet<K> setB) {
    TreeSet<Pair<T, K> > result;

    TreeSetIterator<T> iterA = this->iterator();
    while (iterA.hasNext()) {
      T a = iterA.next();
      TreeSetIterator<K> iterB = setB.iterator();
      while (iterB.hasNext()) {
        K b = iterB.next();
        Pair<T, K> value = {a, b};
        result.add(value);
      }
    }

    return result;
  }

  void addAll(TreeSet<T>);

private:
  void addAll(binOrdTree<T>);
  void addAll2(binOrdTree<T>, binOrdTree<T>);
  binOrdTree<T> data;
};

template <typename T>
void TreeSet<T>::addAll(binOrdTree<T> tr) {
  if (tr.empty()) {
    return;
  }
  add(tr.rootTree());
  addAll(tr.leftTree());
  addAll(tr.rightTree());
}

template <typename T>
void TreeSet<T>::addAll(TreeSet<T> setB) {
  addAll(setB.data);
}

template <typename T>
void TreeSet<T>::addAll2(binOrdTree<T> setA, binOrdTree<T> setB) {
  if (setA.empty()) {
    return;
  }

  if (find(setA.rootTree(), setB)) {
    add(setA.rootTree());
  }

  addAll2(setA.leftTree(), setB);
  addAll2(setA.rightTree(), setB);
}

template <typename T>
TreeSet<T> TreeSet<T>::intersectSet(TreeSet<T> setB) const {
  TreeSet<T> result;

  TreeSetIterator<T> iterA = this->iterator();
  while (iterA.hasNext()) {
    T x = iterA.next();
    if (setB.contains(x)) {
      result.add(x);
    }
  }

  return result;
}

template <typename T>
TreeSet<T> TreeSet<T>::unionSet(TreeSet<T> setB) const {
  TreeSet<T> result = *this;

  TreeSetIterator<T> iterB = setB.iterator();
  while(iterB.hasNext()) {
    result.add(iterB.next());
  }

  return result;
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
  return find(x, data);
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
  return ::size(data);
}


void problem1();

void problem2() {
  TreeSet<int> setA;
  setA.add(1);
  setA.add(1);
  setA.add(1);
  setA.add(2);
  setA.add(4);
  setA.add(5);
  setA.add(2);
  setA.add(2);
  setA.add(5);

  TreeSet<int> setB;
  setB.add(1);
  setB.add(2);
  setB.add(13);
  setB.add(42);

  setA.print();
  setB.print();

  setA.unionSet(setA).print();
  setA.unionSet(setB).print();
  setA.intersectSet(setA).print();
  setA.intersectSet(setB).print();
  setB.intersectSet(setA).print();

  setA.cartesianProduct(setB).print();
}



int main() {
  // problem1();
  problem2();
  return 0;
}




void problem1() {
  tree<int> leftOperands;
  tree<int> rightOperands;
  char operation = '*';

  leftOperands.Create(); // 1 y 1 y 2 y 4 n n n y 3 n n y 1 y 2 n y 5 n n y 3 n n
  rightOperands.Create(); // 5 y 3 n n n

  // 1 y 1 y 2 y 4 n n n y 3 n n y 1 y 2 n y 5 n n y 3 n n 5 y 3 n n n

  cout << endl << endl << endl;

  applyOperation(leftOperands, rightOperands, operation).print();
}



tree<int> treeWithRoot(int root) {
  tree<int> result;
  result.Create3(root, tree<int>(), tree<int>());
  return result;
}

template<typename T>
bool find(T x, binOrdTree<T> t) {
  if (t.empty()) {
    return false;
  }

  if (x == t.rootTree()) {
    return true;
  } else if (x < t.rootTree()) {
    return find(x, t.leftTree());
  } else {
    return find(x, t.rightTree());
  }
}

template<typename T>
int size(binOrdTree<T> t) {
  if (t.empty()) {
    return 0;
  }

  return 1
       + size(t.leftTree())
       + size(t.rightTree());
}



int applyOperation(int left, int right, char operation) {
  switch (operation) {
    case '*':
      return left * right;
    case '+':
    default:
      return left + right;
  }
}

tree<int> applyOperation(tree<int> leftOperands, tree<int> rightOperands, char op) {
  if (leftOperands.empty()) {
    return tree<int>();
  }

  if (rightOperands.empty()) {
    return leftOperands;
  }

  int leftOperand = leftOperands.RootTree();
  int rightOperand = rightOperands.RootTree();

  tree<int> rightOperandsInLeftSubtree = rightOperands.LeftTree().empty() ? treeWithRoot(rightOperand) : rightOperands.LeftTree();
  tree<int> rightOperandsInRightSubtree = rightOperands.RightTree().empty() ? treeWithRoot(rightOperand) : rightOperands.RightTree();

  tree<int> resultTree;
  resultTree.Create3(
    applyOperation(leftOperand, rightOperand, op),
    applyOperation(leftOperands.LeftTree(), rightOperandsInLeftSubtree, op),
    applyOperation(leftOperands.RightTree(), rightOperandsInRightSubtree, op)
  );
  return resultTree;
}
