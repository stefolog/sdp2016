README.md

Упражнение 6
===

Задача 1
---
Да се промени фунцкията tail, така че да използва цъкличен списък вместо масив като буфер.

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

  if (linesCount < lines) {
    for (int i = 0; i < linesCount; i++) {
      cout << bufferLines[i] << endl;
    }
  } else {
    for (int i = 0; i < lines; i++) {
      cout << bufferLines[(i + linesCount) % lines] << endl;
    }
  }

  delete[] bufferLines;
}
