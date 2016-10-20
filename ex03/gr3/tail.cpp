#include <iostream>
#include <fstream>
using namespace std;

/*  bigfile.txt

  100x ...

  ...
  xxxx\n
  LoL\n
  LoL\n
  LoL\n
  \n
bash: tail -n 3 bigfile.txt
*/

// 3
int findTheStartOfFirstLineToShow(ifstream& file, int lines) {
  file.seekg(0, ios::beg);
  streampos startPos = file.tellg();

  file.seekg(0, ios::end);
  streampos endPos = file.tellg();

  int fileSize = endPos - startPos;
  cout << "fileSize: " << fileSize << endl;

  bool newLine = false;
  int pos = 1;
  while (lines >= 0) {
    file.seekg(-1 * pos, ios::end); // v1
    // file.seekg(-2, ios::cur); // v2

    char c;
    file.get(c);

    if (c == 10) {
      lines--;
    }

    pos++;
    // TODO: refactor!!!
    if (pos >= fileSize) {
      pos += 2;
      break;
    }
    file.clear();
  }

  // -1 for last pos++
  // -1 last read charcter is \n
  return pos - 2;
}

void tail(string filename, int lines) {
  ifstream file(filename);

  int startOfFirstLineToShow = findTheStartOfFirstLineToShow(file, lines);

  file.seekg(-startOfFirstLineToShow, ios::end);
  char c;
  while (file.get(c)) {
    cout << c;
  }

  file.close();
}

int main(int argc, char* argv[]) {
  cout << argv[0] << endl;
  if (argc == 3) {
    string filename(argv[1]);
    int lines = stoi(argv[2]);

    tail(filename, lines);
  } else {
    cout << "Usage: tail $filename $linesNumber" << endl;
  }
}













