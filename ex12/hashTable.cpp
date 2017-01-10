#include <iostream>
// #include <iomanip>
// #include <fstream>
#include "cassert"
#include "../templates/llist.cpp"


template <typename KEY, typename VALUE>
struct hashPair
{
  hashPair() {}

  hashPair(KEY key, VALUE value) {
    this->key = key;
    this->value = value;
  }

  KEY key;
  VALUE value;
};

template <typename KEY, typename VALUE>
ostream& operator<<(ostream& out, const hashPair<KEY, VALUE>& r) {
  return out;
}

template <typename KEY, typename VALUE>
class hashTable
{
public:
  hashTable(unsigned = 1021);
  ~hashTable();

  // хеш-функция
  unsigned hash(const KEY) const;

  // включване на нов запис по зададени компоненти
  void insert(KEY, VALUE);

  // търсене на запис по указан ключ
  elem_link1<hashPair<KEY, VALUE> >* find(const KEY) const;

  // изтриване на запис по указан ключ
  void delRec(const KEY);

  void print() const;
private:
  unsigned k;      // брой елементи на хеш-таблицата
  LList<hashPair<KEY, VALUE> > *arr;
};

template <typename KEY, typename VALUE>
hashTable<KEY, VALUE>::hashTable(unsigned n)
{
  k = n;
  arr = new LList<VALUE>[n];
  assert(arr != NULL);
}

template <typename KEY, typename VALUE>
hashTable<KEY, VALUE>::~hashTable()
{
  delete [] arr;
}

// template <typename VALUE>
// unsigned hashTable<string, VALUE>::hash(const char* str) const
// {
//   unsigned sum = 0;
//   for (unsigned i = 0; str[i]; i++)
//     sum += (i+1)*str[i];
//   return sum % k;
// }

template <typename KEY, typename VALUE>
void hashTable<KEY, VALUE>::insert(const KEY key, VALUE val)
{
  arr[hash(key)].ToEnd(hashPair<KEY, VALUE>(key, val));
}

template <typename KEY, typename VALUE>
elem_link1<hashPair<KEY, VALUE> >* hashTable<KEY, VALUE>::find(const KEY key) const
{
  LList<hashPair<KEY, VALUE> > list = arr[hash(key)];
  list.IterStart();
  elem_link1<hashPair<KEY, VALUE> >* p;

  while ((p = list.Iter())) {
    if ((p->inf).key == key) {
      return p;
    }
  }

  return NULL;
}

template <typename KEY, typename VALUE>
void hashTable<KEY, VALUE>::delRec(const KEY key)
{
  arr[hash(key)].IterStart();
  elem_link1<hashPair<KEY, VALUE> >* p = arr[hash(key)].Iter();
  while(p && strcmp(p->inf.name, key))
    p = p->link;
    if (p)
    {
      rec y;
      arr[hash(key)].DeleteElem(p, y);
    }
}

template <typename KEY, typename VALUE>
void hashTable<KEY, VALUE>::print() const
{ for (unsigned i = 0; i < k; i++)
   if (!arr[i].empty())
   { arr[i].print();
      cout << endl;
   }
}
