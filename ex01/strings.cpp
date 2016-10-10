#include <iostream>
#include <string>

using namespace std;

// char* - C-String
// string - String
int main() {
  string s1("Hello");
  string s2("World");

  cout << (s1 + " " + s2) << endl;
  cout << (string("Hello World") == (s1 + " " + s2)) << endl;
  cout << "s1 < s2: " << (s1 < s2) << endl;
  cout << s1.find("o") << endl;
  // cout << ("Hello " + "World") << endl;
}
