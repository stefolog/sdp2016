#include<iostream>
#include "../templates/stack.cpp"

using namespace std;

string s1 = "";
string s2 = "ala bala";
string s3 = "{}";
string s4 = "()";
string s5 = "[]";
string s6 = "}{";
string s7 = ")(";
string s8 = "][";
string s9 = "({})";
string s10 = "({[[[()]]]})";
string s11 = "({[[[(]]]})";
string s12 = "<<()>>";
string s13 = "{<[]>}";
string s14 = "aDSA";


/*
    |   |
    |   |
    |   |
    |   |
    |___|

    // fail:
    1. empty stack && closing bracket
    2. not empty stack && closing bracket does not match stack top

    3. stack is not empty in the end
*/

struct bracketPair {
  char open;
  char close;
};

bracketPair supportedBrackets[] = {
  { '(', ')' },
  { '[', ']' },
  { '{', '}' },
  { '<', '>' },
  { 'a', 'A' },
};

int BRACKETS_COUNT = 5;

bool isOpeningBracket(char c) {
  for (int i = 0; i < BRACKETS_COUNT; i++) {
    if (supportedBrackets[i].open == c) {
      return true;
    }
  }
  return false;
}

bool isClosingBracket(char c) {
  for (int i = 0; i < BRACKETS_COUNT; i++) {
    if (supportedBrackets[i].close == c) {
      return true;
    }
  }
  return false;
}

bool areMatchingBracket(char opening, char closing) {
  for (int i = 0; i < BRACKETS_COUNT; i++) {
    if (supportedBrackets[i].open == opening) {
      return supportedBrackets[i].close == closing;
    }
  }
  return false;
}

bool brackets(string str) {
  stack<char> s;

  for (int i = 0; i < str.length(); i++) {
    if (isOpeningBracket(str[i])) {
      s.push(str[i]); // STACK !!!
    } else if (isClosingBracket(str[i])) {
      if (s.empty()) { // STACK !!!
        return false;
      }
      char c;
      s.pop(c); // STACK !!!
      if (!areMatchingBracket(c, str[i])) {
        return false;
      }
    }
  }

  return s.empty(); // STACK !!!
}

void valid_brackets(string s, bool expected) {
  if (brackets(s) == expected) {
    cout << "[OK ] Check: " << s << endl;
  } else {
    cout << "[ERR] Check: " << s << endl;
  }
}

int main() {
  valid_brackets(s1, true);
  valid_brackets(s2, true);
  valid_brackets(s3, true);
  valid_brackets(s4, true);
  valid_brackets(s5, true);
  valid_brackets(s6, false);
  valid_brackets(s7, false);
  valid_brackets(s8, false);
  valid_brackets(s9, true);
  valid_brackets(s10, true);
  valid_brackets(s11, false);
  valid_brackets(s12, true);
  valid_brackets(s13, true);
  valid_brackets(s14, true);

}
