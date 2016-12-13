#include <iostream>
#include <iomanip>
#include <fstream>
#include "cassert"

using namespace std;

struct rec
{ char name[32];    // фамилно име
   unsigned num;    // факултетен номер
};

class hashTable
{
public:
  hashTable(unsigned = 1021);
  ~hashTable();
  void insert(const char*, unsigned);
  rec* find(const char*);
  void print() const;

private:
  unsigned n,    // размер на хеш-таблицата
           sum;  // за низа "Len" sum = 1.'L'+2.'e' + 3.'n'
  rec* arr;      // носител на хеш-таблицата
  unsigned hash(const char*);      // хеш-функция
  unsigned increment() const;    // втора хеш-функция
  bool search(const char*, unsigned &);  // търсене на ключ
};

hashTable::hashTable(unsigned num)
{
  if (num > 5) n = num;
  else n = 5;
  arr = new rec[n];
  assert(arr != NULL);
  for (unsigned i = 0; i < n; i++)
    arr[i].name[0] = '\0';
}

hashTable::~hashTable()
{
  delete [] arr;
}

unsigned hashTable::hash(const char* str)
{
  sum = 0;
  for (unsigned i = 0; str[i]; i++)
    sum += (i+1)*str[i];
  return sum % n;
}

unsigned hashTable::increment() const
{
  return 1 + sum % (n-2);
}

bool hashTable::search(const char* str, unsigned &i)
{
  unsigned count = 0, incr;
  if (strcmp(arr[i].name, str))
  {
    incr = increment();
    do
    {
      count++;
      if (count == n) return false;
      i = (i+incr) % n;
    } while(strcmp(arr[i].name, str));
  }
  return true;
}

void hashTable::insert(const char* str, unsigned num)
{
  unsigned i = hash(str);
  if (!search("", i))
  {
    cout << "Хеш-таблицата е запълнена.\n";
    return;
  }
  strcpy(arr[i].name, str);
  arr[i].num = num;
}

rec* hashTable::find(const char* str)
{
  unsigned i = hash(str);
  if (search(str, i)) return arr+i;
  return NULL;
}

void hashTable::print() const
{
  for (unsigned i = 0; i < n; i++)
    if (strcmp(arr[i].name, ""))
      cout << setw(5) << i
           << setw(35) << arr[i].name
           << setw(10) << arr[i].num << endl;
    else cout << setw(5) << i << endl;
  cout << endl;
}

int main() {

}
