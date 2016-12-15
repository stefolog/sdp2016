#include <iostream>
#include "binOrdTree.cpp"

template<typename T>
bool find(T, binOrdTree<T>);

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
int size(binOrdTree<T>);

template<typename T>
int size(binOrdTree<T> t) {
  if (t.empty()) {
    return 0;
  }

  return 1
       + size(t.leftTree())
       + size(t.rightTree());
}

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
class TreeSetIterator {
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

/**
  Requires implementation of:
    operator==
    operator<
    operator<<
  for type T
*/
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
  TreeSet<T> minusSet(TreeSet<T> x) const {
    TreeSet<T> result = *this;

    TreeSetIterator<T> iter = x.iterator();
    while (iter.hasNext()) {
      T toRemove = iter.next();
      result.remove(toRemove);
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
