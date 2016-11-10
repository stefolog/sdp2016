#include <iostream>
#include <fstream>
#include "../templates/cyclicList.cpp"

using namespace std;

template <typename T>
class RingBuffer {
public:
  RingBuffer(int size) {
    this->size = size;
  }

  void add(T value) {
    if (list.length() >= size) {
      list.iterStart();
      T _;
      list.deleteElem(list.iter(), _);
    }
    list.toEnd(value);
  }

  void print() {
    list.iterStart();
    elem_cyclic<T> *x;
    while ((x = list.iter())) {
      cout << x->inf << endl;
    }
  }
private:
  cyclicList<T> list;
  int size;
};

void tail(string filename, int lines) {
  ifstream fin(filename);
  if (!fin) {
    throw "File not found";
  }

  int linesCount = 0;

  RingBuffer<string> lastLines(lines);

  string * bufferLines = new string[lines];
  char lineBuffer[2000];
  while (fin.getline(lineBuffer, 2000)) {
    lastLines.add(string(lineBuffer));
  }
  fin.close();

  lastLines.print();

  delete[] bufferLines;
}

int main() {
  tail("test.txt", 300);
}
