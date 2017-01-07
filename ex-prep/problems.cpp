#include <iostream>
#include "../templates/graph.cpp"
#include "../templates/queue.cpp"

using namespace std;

bool contains(LList<int> & list, int x) {
  list.IterStart();
  elem_link1<int>* p;
  while ((p = list.Iter())) {
    if (p->inf == x) {
      return true;
    }
  }
  return false;
}

int findPathLengthBFSIter(graph<int>& g, int a, int b) {
  queue<pair<int, int> > q;
  LList<int> visited;

  q.push(make_pair(a, 0));

  pair<int, int> xPair;
  while (q.pop(xPair)) {
    int x = xPair.first;
    int distanceToX = xPair.second;

    visited.ToEnd(x);

    if (x == b) {
      return distanceToX;
    }
    elem_link1<int>* neighbours = g.point(x);
    while (neighbours->link) {
      neighbours = neighbours->link;
      int n = neighbours->inf;
      if (!contains(visited, n)) {
        q.push(make_pair(n, distanceToX + 1));
      }
    }
  }

  return -1;
}


int findPathLengthBFS(graph<int>& g, int b, queue<pair<int, int> >& q, LList<int>& visited) {
  if (q.empty()) {
    return -1;
  }

  pair<int, int> aPair;
  q.pop(aPair);

  int a = aPair.first;
  int distanceToA = aPair.second;

  if (a == b) {
    return distanceToA;
  }

  visited.ToEnd(a);

  elem_link1<int>* neighbours = g.point(a);
  while (neighbours->link) {
    neighbours = neighbours->link;
    int n = neighbours->inf;
    if (!contains(visited, n)) {
      q.push(make_pair(n, distanceToA + 1));
    }
  }

  return findPathLengthBFS(g, b, q, visited);
}

int findPathLengthIter(graph<int>& g, int a, int b) {
  if (!g.top(a) || !g.top(b)) {
    return -1;
  }

  return findPathLengthBFSIter(g, a, b);
}

int findPathLength(graph<int>& g, int a, int b) {
  if (!g.top(a) || !g.top(b)) {
    return -1;
  }
  queue<pair<int, int> > q;
  q.push(make_pair(a, 0));

  LList<int> visited;
  return findPathLengthBFS(g, b, q, visited);
}

/*
  1. Кой от двата пътя в граф е по кратък - между A и B или C и D.

  returns 1 - if A,B is shorter
  returns 2 - if C,D is shorter
*/
int shorterPath(graph<int>& g, int a, int b, int c, int d) {
  int l1 = findPathLength(g, a, b);
  int l2 = findPathLength(g, c, d);

  if (l1 < 0) {
    return 2;
  }

  if (l2 < 0) {
    return 1;
  }

  return l1 <= l2 ? 1 : 2;
}

void deleteElement(LList<int>& list, int x) {
  list.IterStart();
  elem_link1<int>* p;
  while ((p = list.Iter())) {
    if (p->inf == x) {
      list.DeleteElem(p, x);
      return;
    }
  }
}

/*
  2. Съществува ли ацикличен път в графа, със сума на елементите >= N
*/
bool existsPathWithSum(graph<int>& g, int n, int a, LList<int>& visited) {
  if (n <= a) {
    return true;
  }
  visited.ToEnd(a);

  elem_link1<int>* neighbours = g.point(a);
  while (neighbours->link) {
    neighbours = neighbours->link;
    int next = neighbours->inf;
    if (!contains(visited, next)) {
      if (existsPathWithSum(g, n - a, next, visited)) {
        return true;
      }
    }
  }

  deleteElement(visited, a);
  return false;
}

bool existsPathWithSum(graph<int>& g, int n) {
  LList<int> v = g.vertexes();
  v.IterStart();
  elem_link1<int> *p;
  while ((p = v.Iter())) {
    LList<int> visited;
    if (existsPathWithSum(g, n, p->inf, visited)) {
      return true;
    }
  }
  return false;
}

/*
  3. Съществува ли ацикличен път между А и B, преминаващ през върхове в нарастващ ред
*/
LList<int> existsAscendingPath(graph<int>& g, int a, int b, LList<int>& visited) {
  visited.ToEnd(a);

  if (a == b) {
    return visited;
  }

  elem_link1<int>* neighbours = g.point(a);
  while (neighbours->link) {
    neighbours = neighbours->link;
    int next = neighbours->inf;

    if (next > a && !contains(visited, next)) {
      LList<int> path = existsAscendingPath(g, next, b, visited);
      if (!path.empty()) {
        return visited;
      }
    }
  }

  deleteElement(visited, a);
  return LList<int>();
}

LList<int> existsAscendingPath(graph<int>& g, int a, int b) {
  LList<int> visited;
  return existsAscendingPath(g, a, b, visited);
}

int main() {
  graph<int> g;
  g.addTop(1);
  g.addTop(2);
  g.addTop(3);
  g.addTop(4);
  g.addTop(5);
  g.addTop(6);
  g.addTop(8);

  g.addRib(1, 2); g.addRib(2, 1);
  g.addRib(1, 3); g.addRib(3, 1);
  g.addRib(2, 3); g.addRib(3, 2);
  g.addRib(2, 5); g.addRib(5, 2);
  g.addRib(2, 6); g.addRib(6, 2);
  g.addRib(3, 4); g.addRib(4, 3);
  g.addRib(3, 5); g.addRib(5, 3);
  g.addRib(4, 6); g.addRib(6, 4);

  g.print();
  // cout << findPathLength(g, 1, 6) << endl;
  // cout << findPathLength(g, 1, 8) << endl;
  // cout << findPathLengthIter(g, 1, 6) << endl;
  // cout << findPathLengthIter(g, 1, 8) << endl;
  // cout << existsPathWithSum(g, 10) << endl;
  // cout << existsPathWithSum(g, 21) << endl;
  // cout << existsPathWithSum(g, 22) << endl;
  cout << "(1, 1)>"; existsAscendingPath(g, 1, 1).print();
  cout << "(1, 6)>"; existsAscendingPath(g, 1, 6).print();
  cout << "(3, 6)>"; existsAscendingPath(g, 3, 6).print();
  cout << "(5, 6)>"; existsAscendingPath(g, 5, 6).print();
}
