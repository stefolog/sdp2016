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

struct BracketPair {
  char opening;
  char closing;
};

const int SUPPORTED_BRACKETS_COUNT = 5;
BracketPair supportedBrackets[] = {
  { '(', ')'},
  { '[', ']'},
  { '{', '}'},
  { '<', '>'},
  { 'a', 'A'}
};


bool isOpeningBracket(char c) {
  for (int i = 0; i < SUPPORTED_BRACKETS_COUNT; i++) {
    if (supportedBrackets[i].opening == c) {
      return true;
    }
  }
  return false;
}

bool isClosingBracket(char c) {
  for (int i = 0; i < SUPPORTED_BRACKETS_COUNT; i++) {
    if (supportedBrackets[i].closing == c) {
      return true;
    }
  }
  return false;
}

bool bracketsMatch(char opening, char closing) {
  for (int i = 0; i < SUPPORTED_BRACKETS_COUNT; i++) {
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

void validateBrackets(string str, bool expected) {
  if (brackets(str) == expected) {
    cout << "[OK ] " << str << endl;
  } else {
    cout << "[ERR] " << str << endl;
  }
}

struct TestData {
  string test;
  bool expected;
};

const int TESTS_COUNT = 19;
TestData tests[] = {
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
  for (int i = 0; i < TESTS_COUNT; i++) {
    validateBrackets(tests[i].test, tests[i].expected);
  }

}
