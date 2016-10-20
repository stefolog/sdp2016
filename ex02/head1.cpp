#include <iostream>
#include <fstream>
using namespace std;

void head(string filename, int n) {
  ifstream ifs(filename);

  char buf[4096];
  while (n > 0 && ifs.getline(buf, 4096)) {
    cout << buf << endl;
    n--;
  }

  ifs.close();
}

void tail(string filename, int n) {
}

int main() {
  head("bigfile.txt", 5);

  tail("bigfile.txt", 5);
}
