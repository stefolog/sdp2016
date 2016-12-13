#include <iostream>
#include <iomanip>
#include <fstream>
#include "cassert"
#include "../templates/llist.cpp"

using namespace std;

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

ostream& operator<<(ostream& out, const rec& r) {
  return out;
}

// тип свързан списък от записи
typedef LList<rec> list_Rec;

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
  elem_link1<rec>* find(const KEY) const;

  // изтриване на запис по указан ключ
  void delRec(const KEY);

  void print() const;
private:
  unsigned k;      // брой елементи на хеш-таблицата
  LList<hashPair<KEY, VALUE> > *arr;
};

template <typename KEY, typename VALUE>
hashTable::hashTable(unsigned n)
{ k = n;
   arr = new LList<VALUE>[n];
   assert(arr != NULL);
}

template <typename KEY, typename VALUE>
hashTable::~hashTable()
{
  delete [] arr;
}

// ???
template <typename KEY, typename VALUE>
unsigned hashTable::hash(const char* str) const
{ unsigned sum = 0;
   for (unsigned i = 0; str[i]; i++)
       sum += (i+1)*str[i];
   return sum % k;
}

template <typename KEY, typename VALUE>
void hashTable::insert(const KEY key, VALUE val)
{
  arr[hash(key)].ToEnd(hashPair(key, val));
}

template <typename KEY, typename VALUE>
elem_link1<VALUE>* hashTable::find(const KEY key) const
{
  arr[hash(key)].IterStart();
  elem_link1<hashPair<KEY, VALUE> >* p;

  while ((p = arr[hash(key)].Iter())) {
    if ((p->inf).key == key) {
      return ->
      result.ToEnd((p->inf).value);
    }
  }

  return arr[hash(key)].Iter();
}

template <typename KEY, typename VALUE>
void hashTable::delRec(const KEY key)
{
  arr[hash(key)].IterStart();
  elem_link1<rec>* p = arr[hash(key)].Iter();
  while(p && strcmp(p->inf.name, str))
    p = p->link;
    if (p)
    {
      rec y;
      arr[hash(str)].DeleteElem(p, y);
    }
}

template <typename KEY, typename VALUE>
void hashTable::print() const
{ for (unsigned i = 0; i < k; i++)
   if (!arr[i].empty())
   { arr[i].print();
      cout << endl;
   }
}

// примерно изпълнение
int main()
{
// ifstream f("c:\\zad\\Student_Number.txt", ios::in);
//    if (!f)
//    { cerr << "Cannot open file Student_Number.txt!\n";
//       return 1;
//    }

//   char name[16];
//    unsigned num, k;
//    cout << "Дължина k на хеш-таблицата: "; cin >> k;
//    // създаване на празна хеш-таблица
//    hashTable hashObj(k);

//    // прехвърляне на записите на файла f
//    // в хеш-таблицата hashObj
//    while (f >> name >> num)
//    { cout << setw(20) << left << name
//              << setw(15) <<num << endl;
//       hashObj.insert(name, num);
//    }

//    // извеждане на хеш-таблицата
//    hashObj.print(); cout << endl;
//    // търсене на записи в хеш-таблицата
//    // (до въвеждане на end)
//    elem_link1<rec>* p = NULL;
//    cout << "Въведете име или end за край на програмата!\n";
//    cin >> name;
//    while (strcmp(name, "end"))
//    { p = hashObj.find(name);
//       if (p) cout << "Записът е намерен в хеш-таблицата.\n";
//       else cout << " Записът не е намерен в хеш-таблицата.\n";
//       cout << "Въведете фамилия или end "
//                    "за край на програмата!\n";
//       cin >> name;
//    }
//    f.close();
//    return 0;
}
