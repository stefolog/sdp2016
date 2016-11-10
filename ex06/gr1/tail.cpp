#include <iostream>
#include <fstream>
#include "../../templates/cyclicList.cpp"

template <typename T>
class RingBuffer {
public:
  RingBuffer(int size) {
    this->size = size;
  }

  void add(T element) {
    if (data.length() >= size) {
      data.iterStart();
      string _;
      data.deleteElem(data.iter(), _);
    }

    data.toEnd(element);
  }

  void print() {
    data.iterStart();
    elem_cyclic<T>* p;
    while ((p = data.iter())) {
      cout << p->inf << endl;
    }
  }

private:
  int size;
  cyclicList<T> data;
};

void tail(string filename, int lines) {
  ifstream fin(filename);
  if (!fin) {
    throw "File not found";
  }

  RingBuffer<string> bufferLines(lines);

  char buf[2000];
  while (fin.getline(buf, 2000)) {
    bufferLines.add(string(buf));
  }
  fin.close();

  bufferLines.print();
}

int main() {
  tail("test.txt", 3);
}
