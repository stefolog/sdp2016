#include <iostream>
#include <fstream>
using namespace std;

void head(string filename, int lines) {
  ifstream fin(filename);
  if (!fin) {
    throw "File not found";
  }

  char buf[2000];
  while (lines > 0 && fin.getline(buf, 2000)) {
    cout << buf << endl;
    lines--;
  }

  fin.close();
}

void tail(string filename, int lines) {
  ifstream fin(filename);
  if (!fin) {
    throw "File not found";
  }

  int linesCount = 0;

  string * bufferLines = new string[lines];
  char buf[2000];
  while (fin.getline(buf, 2000)) {
    bufferLines[linesCount % lines] = string(buf);
    linesCount++;
  }
  fin.close();

  for (int i = 0; i < lines; i++) {
    cout << bufferLines[(i + linesCount) % lines] << endl;
  }
  delete[] bufferLines;
}



int main() {
  int lines = 5;
  string filename("bigfile.txt");

  // cout << "head" << endl;
  // head(filename, lines);
  // cout << endl << endl << "tail" << endl;
  tail(filename, lines);
  cout << endl << endl;
}
