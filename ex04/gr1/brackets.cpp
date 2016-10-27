#include <iostream>
#include "../../templates/stack.cpp"

using namespace std;

/*
  {(})
  {()}
  {{

  | |
  | |
  |_|
*/
struct bracketPair {
  char opening;
  char closing;
};

const int supportedBracketsCount = 5;
bracketPair supportedBrackets[] = {
  { '(', ')' },
  { '[', ']' },
  { '{', '}' },
  { '<', '>' },
  { 'a', 'A' },
};


bool isOpeningBracket(char c) {
  for (int i = 0; i < supportedBracketsCount; i++) {
    if (supportedBrackets[i].opening == c) {
      return true;
    }
  }
  return false;
}

bool isClosingBracket(char c) {
  for (int i = 0; i < supportedBracketsCount; i++) {
    if (supportedBrackets[i].closing == c) {
      return true;
    }
  }
  return false;
}

bool bracketsMatch(char opening, char closing) {
  for (int i = 0; i < supportedBracketsCount; i++) {
    if (supportedBrackets[i].opening == opening) {
      return supportedBrackets[i].closing == closing;
    }
  }
  return false;
}

bool brackets(string str) {
  stack<char> openBrackets;

  for (int i = 0; i < str.length(); i++) {
    if (isOpeningBracket(str[i])) {
      openBrackets.push(str[i]);

    } else if (isClosingBracket(str[i])) {
      if (openBrackets.empty()) {
        return false;
      }

      char openingBracket;
      openBrackets.pop(openingBracket);

      if (!bracketsMatch(openingBracket, str[i])) {
        return false;
      }
    }
  }
  return openBrackets.empty();
}

void validate_brackets(string str, bool expected) {
  if (brackets(str) == expected) {
    cout << "[OK ] " << str << endl;
  } else {
    cout << "[ERR] " << str << endl;
  }
}

struct testData {
  string test;
  bool expected;
};

const int testsCount = 19;
testData tests[] = {
  { "", true },
  { "ala bala", true },
  { "()", true },
  { "{}", true },
  { "[]", true },
  { ")(", false },
  { "][", false },
  { "}{", false },
  { "({})", true },
  { "[()]", true },
  { "{[({})]}", true },
  { "{[(]}", false },
  { "{[((]}", false },
  { "()()", true },
  { "((())()())", true },
  { "abbbA", true },
  { "<html>", true },
  { "ababbA", false },
  { "<>html>", false },
};

int main() {
  for (int i = 0; i < testsCount; i++) {
    validate_brackets(tests[i].test, tests[i].expected);
  }

}
