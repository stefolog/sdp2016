#include <iostream>
#include <fstream>
using namespace std;

int main() {
  fstream fin("merge-columns.txt");
  ofstream fout("merge-columns-result.txt");

  string x;
  while (fin >> x) {
    fout << x << endl;
  }

  fin.close();
  fout.close();

  return 0;
}
