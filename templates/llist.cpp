#ifndef LLIST_H_INCLUDED
#define LLIST_H_INCLUDED

#include <iostream>

using namespace std;

template <class T>
struct elem_link1
{
  T inf;
  elem_link1 *link;
};

template <class T>
class LList
{
public:
  LList();
  ~LList();
  LList(LList const&);
  LList& operator=(LList const &);
  void print();
  void IterStart(elem_link1<T>* = NULL);
  elem_link1<T>* Iter();
  void ToEnd(T const &);

  void InsertAfter(elem_link1<T> *, T const &);
  void InsertBefore(elem_link1<T> *, T const &);

  int DeleteAfter(elem_link1<T> *, T &);
  int DeleteBefore(elem_link1<T> *, T &);
  void DeleteElem(elem_link1<T> *, T &);

  bool empty() const;
  int len();
  void concat(LList const&);
  void reverse();

  T operator[](int idx);
private:
  elem_link1<T> *Start, *End, *Current;
  void DeleteList();
  void CopyList(LList<T> const &);
};


template <class T>
LList<T>::LList()
{
  Start = NULL;
  End = NULL;
}

template <class T>
LList<T>::~LList()
{
  DeleteList();
}

template <class T>
LList<T>::LList(LList<T> const& r)
{
  CopyList(r);
}

template <class T>
LList<T>& LList<T>::operator=(LList<T> const & r)
{
  if(this!=&r)
  {
    DeleteList();
    CopyList(r);
  }
  return *this;
}

template <class T>
void LList<T>::DeleteList()
{
  elem_link1<T> *p;
  while(Start)
  {
    p = Start;
    Start = Start->link;
    delete p;
  }
  End = NULL;
}

template <class T>
void LList<T>::CopyList(LList<T> const & r)
{
  Start = End = NULL;
  if(r.Start)
  {
    elem_link1<T> *p = r.Start;
    while(p)
    {
      ToEnd(p->inf);
      p=p->link;
    }
  }
}

template <class T>
void LList<T>::print()
{
  IterStart();
  elem_link1<T>* e = Iter();
  while(e)
  {
    cout << e->inf << " ";
    e = Iter();
  }
  cout << endl;
}

template <class T>
void LList<T>::IterStart(elem_link1<T> *p)
{
  if (p) Current = p;
  else Current = Start;
}

template <class T>
elem_link1<T>* LList<T>::Iter()
{
  elem_link1<T> *p = Current;
  if(Current)Current = Current->link;
  return p;
}

template <class T>
void LList<T>::ToEnd(T const & x)
{
  Current = End;
  End = new elem_link1<T>;
  End->inf = x;
  End->link = NULL;
  if(Current) Current->link = End;
  else Start = End;
}

template <class T>
void LList<T>::InsertAfter(elem_link1<T> *p, T const & x)
{
  elem_link1<T> *q = new elem_link1<T>;
  q->inf = x;
  q->link = p->link;
  if(p==End) End = q;
  p->link = q;
}

template <class T>
void LList<T>::InsertBefore(elem_link1<T> * p, T const& x)
{
  elem_link1<T> *q = new elem_link1<T>;
  *q = *p;
  if(p==End) End = q;
  p->inf = x;
  p->link = q;
}

template <class T>
int LList<T>::DeleteAfter(elem_link1<T> *p, T &x)
{
  if(p->link)
  {
    elem_link1<T> *q = p->link;
    x = q->inf;
    p->link = q->link;
    if(q==End) End = p;
    delete q;
    return 1;
  }
  else return 0;
}

template <class T>
void LList<T>::DeleteElem(elem_link1<T> *p, T &x)
{
  if(p==Start)
  {
    x = p->inf;
    if(Start == End){Start = End = NULL;}
    else Start = Start->link;
    delete p;
  }
  else
  {
    elem_link1<T> *q = Start;
    while(q->link!=p)q = q->link;
    DeleteAfter(q, x);
  }
}

template <class T>
int LList<T>::DeleteBefore(elem_link1<T> *p, T &x)
{
  if(p!=Start)
  {
    elem_link1<T> *q=Start;
    while(q->link!=p)q = q->link;
    DeleteElem(q, x);
    return 1;
  } else return 0;
}

template <class T>
bool LList<T>::empty() const
{
  return End == NULL;
}

template <class T>
int LList<T>::len()
{
  int n = 0;
  IterStart();
  elem_link1<T> *p= Iter();
  while(p)
  {
    n++;
    p = Iter();
  }
  return n;
}

template <class T>
void LList<T>::concat(LList<T> const &L)
{
  elem_link1<T> *p = L.Start;
  while(p)
  {
    ToEnd(p->inf);
    p = p->link;
  }
}

template <class T>
void LList<T>::reverse()
{
  LList<T> l;
  IterStart();
  elem_link1<T> *p = Iter();
  if(p)
  {
    l.ToEnd(p->inf);
    p = p->link;
    while(p)
    {
      l.InsertBefore(l.Start, p->inf);
      p = p->link;
    }
  }
  *this = l;
}

#endif // !LLIST_H_INCLUDED
