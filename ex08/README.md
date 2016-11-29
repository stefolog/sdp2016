Упражнение 8
===

AVL
Red-Black Trees
B Tree
B+ Tree
Heap
Graph

Задачи
---
1. При зададено дърво и
получаване на операция (+ или *) и частично покриващо дърво,
приложете опрецията върху оригиналното дърво използвайки
най-близкия елемент на покриващото дърво като втори операнд.
input: tree, operation, delta tree

tree:
         1
        / \
       /   \
      1     1
     / \   / \
    2   3 2   3
   /       \
  4         5

operation: *
operands tree:
     5
    /
   3

Result:
         5
        / \
       /   \
      3     5
     / \   / \
    6   9 10  15
   /       \
  12        25


2. Set - имплементация на множество
TreeSet<T>
  void add(T)
  void remove(T)
  bool contains(T) const
  bool empty() const
  void print() const
  void size() const
  TreeSet<T> union(TreeSet<T>)
  TreeSet<T> intersect(TreeSet<T>)
  TreeSet<T> minus(TreeSet<T>)

  operator+()
  operator^()
  operator-()

  union (setA, setB)
    setC = setA.union(setB)
    setA + setB

  union*
    setA.addAll(setB)
    +=

  intersection
    setA ^ setB

  intersection*
    setA.retainAll(setB)
    ^=

  minus
    setA - setB

  minus*
    setA.deleteAll(setB)
    -=

  template<T, K>
  TreeSet<Pair<T,K>> TreeSet<T>::cartesianProduct(TreeSet<K> setB)
    setA * setB

Vector
 O(n)     void add(T)
 O(n)     void remove(T)
 O(n)     bool contains(T) const

BinaryTree
 O(logn)     void add(T)
 O(logn)     void remove(T)
 O(logn)     bool contains(T) const

Hashtable
 O(1)     void add(T)
 O(1)     void remove(T)
 O(1)     bool contains(T) const
  key -> value
