#include<iostream>
#include<fstream>

using namespace std;

bool isNewLine(char c) {;
  return c == '\n';
}

int findFirstNonNewLineCharcter(ifstream& file) {
  int pos = -1;
  file.seekg(pos, ios::end);

  char c;
  while (file.get(c) && isNewLine(c)) {
    pos--;
    file.seekg(pos, ios::end);
  }

  if (!file) {
    return pos + 1;
  }

  return pos;
}

char readChar(ifstream& file) {
  char c;
  file.get(c);
  return c;
}

int findStartPositionForReading(ifstream& file, int lines) {
  int pos = findFirstNonNewLineCharcter(file);
  int lastNonNewLineCharacterPosition = pos;

  while (true) {
    file.seekg(pos, ios::end);

    char c = readChar(file);

    if (!file) {
      file.clear();
      return lastNonNewLineCharacterPosition;
    }

    if (isNewLine(c)) {
      lines--;
    } else {
      lastNonNewLineCharacterPosition = pos;
    }

    if (lines <= 0) {
      return lastNonNewLineCharacterPosition;
    }

    pos--;
  }

  return pos;
}

void writeTillEndOfFile(ifstream& file) {
  char c;
  while (file.get(c)) {
    cout << c;
  }
}

void tail(string filename, int lines) {
  ifstream file(filename);

  int startPositionForReading = findStartPositionForReading(file, lines);
  file.seekg(startPositionForReading, ios::end);
  writeTillEndOfFile(file);

  file.close();
}

int main(int argc, char* argv[]) {
  if (argc == 3) {
    string filename(argv[1]);
    int lines = stoi(argv[2]);

    tail(filename, lines);
  } else {
    cout << "Usage: " << argv[0] << " filename lines" << endl;
  }

}
