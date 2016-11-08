#ifndef DLLIST_H_INCLUDED
#define DLLIST_H_INCLUDED

#include <iostream>
#include <cassert>

using namespace std;

template <typename T = int>
struct elem_link2
{  T inf;
   elem_link2<T> *pred,
                 *succ;
};

template <typename T = int>
class DLList
{
public:
  DLList();
  ~DLList();
  DLList(const DLList&);
  DLList& operator=(const DLList&);

  bool empty() const;
  void iterStart(elem_link2<T>* = NULL);
  void iterEnd (elem_link2<T>* = NULL);
  elem_link2<T>* iterSucc();
  elem_link2<T>* iterPred();
  void toEnd(const T&);
  void toStart(const T&);
  void deleteElem(elem_link2<T>*, T&);
  void print() const;
  void print_reverse() const;
  int length() const;
private:
  elem_link2<T> *start,
                *end,
                *currentS,
                *currentE;
  void copyList(const DLList&);
  void deleteList();
};

template <typename T>
DLList<T>::DLList()
{ start = end = NULL;
}

template <typename T>
DLList<T>::~DLList()
{ deleteList();
}

template <typename T>
DLList<T>::DLList(const DLList<T>& r)
{ copyList(r);
}

template <typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& r)
{ if (this != &r)
     { deleteList();
        copyList(r);
     }
   return *this;
}

template <typename T>
void DLList<T>::copyList(const DLList<T>& r)
{ start = end = NULL;
   elem_link2<T>* p = r.start;
   while (p)
   { toEnd(p->inf);
      p = p->succ;
   }
 }

template <typename T>
void DLList<T>::deleteList()
{ elem_link2<T>* p = start;
   while (p)
   { start = start->succ;
      delete p;
      p = start;
   }
   end = NULL;
}

template <typename T>
bool DLList<T>::empty() const
{ return start == NULL;
}

template <typename T>
void DLList<T>::iterStart(elem_link2<T>* p)
{ if (p) currentS = p;
   else currentS = start;
}
template <typename T>
elem_link2<T>* DLList<T>::iterSucc()
{ elem_link2<T>* p = currentS;
   if (currentS) currentS = currentS->succ;
   return p;
}

template <typename T>
void DLList<T>::iterEnd(elem_link2<T>* p)
{ if (p) currentE = p;
   else currentE = end;
}

template <typename T>
elem_link2<T>* DLList<T>::iterPred()
{ elem_link2<T>* p = currentE;
   if (currentE) currentE = currentE->pred;
   return p;
}

template <typename T>
void DLList<T>::toEnd(const T& x)
{ elem_link2<T>* p = end;
   end = new elem_link2<T>;
   assert(end != NULL);
   end->inf = x;
   end->succ = NULL;
   if (p) p->succ = end;
   else start = end;
   end->pred = p;
}

template <typename T>
void DLList<T>::toStart(const T& x)
{ elem_link2<T>* p = start;
   start = new elem_link2<T>;
   assert(start != NULL);
   start->inf = x;
   start->pred = NULL;
   if (p) p->pred = start;
   else end = start;
   start->succ = p;
}

template <typename T>
void DLList<T>::deleteElem(elem_link2<T>* p, T& x)
{ x = p->inf;
   if (start == end)  start = end = NULL;
   else
      if (p == start)
      { start = start->succ;
         start->pred = NULL;
      }
      else
         if (p == end)
         { end = p->pred;
            end->succ = NULL;
         }
         else
         { p->pred->succ = p->succ;
            p->succ->pred = p->pred;
         }
  delete p;
}

template <typename T>
void DLList<T>::print() const
{ elem_link2<T>* p = start;
   while (p)
   { cout << p->inf << " ";
      p = p->succ;
   }
   cout << endl;
}

template <typename T>
void DLList<T>::print_reverse() const
{ elem_link2<T>* p = end;
   while (p)
   { cout << p->inf << " ";
      p = p->pred;
   }
   cout << endl;
}

template <typename T>
int DLList<T>::length() const
{ int n = 0;
   elem_link2<T>* p = start;
   while (p)
   { n++;
      p = p->succ;
   }
   return n;
}

#endif // !DLLIST_H_INCLUDED
