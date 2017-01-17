#include <iostream>
#include "../templates/stack.cpp"

using namespace std;

void toBinary(int);
void toBinaryNoRec(int);

int main() {
  cout << "10: "; toBinaryNoRec(10); cout << endl;
  cout << "182: "; toBinaryNoRec(182); cout << endl;
  cout << "128: "; toBinaryNoRec(128); cout << endl;
  cout << "512: "; toBinaryNoRec(512); cout << endl;
  cout << "31: "; toBinaryNoRec(31); cout << endl;
}

void toBinary(int n) {
  if (n <= 1) {
    cout << n;
    return;
  }

  toBinary(n / 2);
  cout << (n % 2);
}

void toBinaryNoRec(int n) {

  stack<int> s;
  while (n > 1) {
    s.push(n % 2);
    n /= 2;
  }
  s.push(n);

  while(!s.empty()) {
    int x;
    s.pop(x);
    cout << x;
  }
}
