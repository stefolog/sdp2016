#include <iostream>
#include <iomanip>
#include <fstream>
#include "cassert"
#include "../templates/llist.cpp"

using namespace std;

struct rec
{ char name[32];    // фамилно име
   unsigned num;    // факултетен номер
};

ostream& operator<<(ostream& out, const rec& r) {
  return out;
}

typedef LList<rec> list_Rec;        // тип свързан списък от записи

class hashTable
{

public:
  hashTable(unsigned = 1021);
  ~hashTable();
  unsigned hash(const char*) const;     // хеш-функция
  // включване на нов запис по зададени компоненти
  void insert(const char*, unsigned);
  // търсене на запис по указан ключ
  elem_link1<rec>* find(const char*) const;
  // изтриване на запис по указан ключ
  void delRec(const char*);
  void print() const;  // извеждане на хеш-таблицата
private:
  unsigned k;    // брой елементи на хеш-таблицата
  list_Rec *arr;   // носител на хеш-таблица
};

hashTable::hashTable(unsigned n)
{ k = n;
   arr = new list_Rec[n];
   assert(arr != NULL);
}

hashTable::~hashTable()
{ delete [] arr;
}

unsigned hashTable::hash(const char* str) const
{ unsigned sum = 0;
   for (unsigned i = 0; str[i]; i++)
       sum += (i+1)*str[i];
   return sum % k;
}

void hashTable::insert(const char* str, unsigned nu)
{
  // rec r(str, nu);
  rec r;
  strcpy(r.name, str);
  r.num = nu;
  arr[hash(str)].ToEnd(r);
}

elem_link1<rec>* hashTable::find(const char* str) const
{ arr[hash(str)].IterStart();
   elem_link1<rec>* p = arr[hash(str)].Iter();
   while (p && strcmp(p->inf.name, str))
        p = p->link;
   return p;
}

void hashTable::delRec(const char* str)
{ arr[hash(str)].IterStart();
   elem_link1<rec>* p = arr[hash(str)].Iter();
   while(p && strcmp(p->inf.name, str))
        p = p->link;
   if (p)
   { rec y;
      arr[hash(str)].DeleteElem(p, y);
   }
}

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
