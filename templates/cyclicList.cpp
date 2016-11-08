#ifndef CYCLICLIST_H_INCLUDED
#define CYCLICLIST_H_INCLUDED

#include <iostream>

using namespace std;


template <typename T = int>
struct elem_cyclic
{
  T inf;
  elem_cyclic<T> *link;
};

template <typename T = int>
class cyclicList
{
public:
  cyclicList();
  ~cyclicList();
  cyclicList(const cyclicList&);
  cyclicList& operator=(const cyclicList&);
  bool empty() const;
  void iterStart(elem_cyclic<T>* = NULL);
  elem_cyclic<T>* iter();
  void insert(const T&);
  void toEnd(const T&);
  void deleteElem(elem_cyclic<T>*, T&);
  void print() const;
  int length() const;
private:
  elem_cyclic<T> *start,
  *current;
  void copyList(const cyclicList&);
  void deleteList();
};

template <typename T>
cyclicList<T>::cyclicList()
{ start = NULL;
}

template <typename T>
cyclicList<T>::~cyclicList()
{ deleteList();
}

template <typename T>
cyclicList<T>::cyclicList (const cyclicList<T>& r)
{ copyList(r);
}

template <typename T>
cyclicList<T>& cyclicList<T>::operator=(const cyclicList<T>& r)
{ if (this != &r)
     { deleteList();
        copyList(r);
     }
   return *this;
}

template <typename T>
void cyclicList<T>::copyList(const cyclicList& r)
{ start = NULL;
   elem_cyclic<T> *p = r.start;
   if (p)
     do
     { p = p->link;
        toEnd(p->inf);
     } while (p != r.start);
}

template <typename T>
void cyclicList<T>::deleteList()
{ iterStart();
   elem_cyclic<T> *p = iter();
   while (p)
   { delete p;
      p = iter();
   }
   start = NULL;
}

template <typename T>
bool cyclicList<T>::empty() const
{ return start == NULL;
}

template <typename T>
void cyclicList<T>::iterStart(elem_cyclic<T>* p)
{ if (p) current = p;
   else
      if (!start) current = NULL;
      else current = start->link;
}
template <typename T>
elem_cyclic<T>* cyclicList<T>::iter()
{ if (!current) return NULL;
   elem_cyclic<T> *p = current;
   if (current == start) current = NULL;
   else current = current->link;
   return p;
}
template <typename T>
void cyclicList<T>::insert(const T& x)
{ elem_cyclic<T>* p = new elem_cyclic<T>;
   assert(p != NULL);
   p->inf = x;
   if (start) p->link = start->link;
   else start = p;
   start->link = p;
}
template <typename T>
void cyclicList<T>::toEnd(const T& x)
{ insert(x);
   start = start->link;
}
template <typename T>
void cyclicList<T>::deleteElem(elem_cyclic<T>* p, T& x)
{ x = p->inf;
   if (start != start->link)
   { elem_cyclic<T> *q = start;
      while (q->link != p) q = q->link;
      q->link = p->link;
      if (p == start) start = q;
   }
   else start = NULL;
   delete p;
}
template <typename T>
void cyclicList<T>::print() const
{
  iterStart();
  elem_cyclic<T> *p;
  while ((p = this->iter())) {
    cout << p->inf << " ";
  }
  cout << endl;
}

template <typename T>
int cyclicList<T>::length() const
{ int n = 0;
   elem_cyclic<T> *p = start;
   if (p)
     do
     { p = p->link;
        n++;
     } while (p != start);
   return n;
}


#endif // !CYCLICLIST_H_INCLUDED
