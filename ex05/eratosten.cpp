#include <iostream>
#include <vector>
#include <cmath>

using namespace std;



// 1, 2, 3, x, 5, x, 7, x, x, x, 10 .... sqrt(n)
// vector:

// t, t, t, t, t, t, t, t, ....
// 1, 2, 3, x, 5, x, 7, x, x, x, 10, ... n
bool isPrime(long n) {
  vector<bool> v;
  for (long i = 0; i <= n; i++) {
    v.push_back(true);
  }

  for (long i = 2; i <= n; i++) {
    if (!v[i]) {
      continue;
    }

    for (long multiplies = 2 * i; multiplies <= n; multiplies += i) {
      v[multiplies] = false;
    }
  }

  return v[n];
}

// O(sqrt(n)*log(n))
vector<long> primeMultipliers(long n) {
  vector<long> possibleMultipliers;
  long sqrtN = (long)sqrt(n);

  vector<bool> v;
  for (long i = 0; i <= sqrtN; i++) {
    v.push_back(true);
  }

  for (long i = 2; i <= sqrtN; i++) {
    if (!v[i]) {
      continue;
    }

    // the number is prime
    possibleMultipliers.push_back(i);

    for (long multiplies = 2 * i; multiplies <= sqrtN; multiplies += i) {
      v[multiplies] = false;
    }
  }

  return possibleMultipliers;
}

bool isPrime2(long n) {
  vector<long> multipliers = primeMultipliers(n);
  for (long i = 0; i < multipliers.size(); i++) {
    if (n % multipliers[i] == 0) {
      return false;
    }
  }
  return true;
}

template<typename T>
void print(vector<T>& v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
}

int main() {
  cout << "5: " << isPrime2(5) << endl;
  cout << "4444: " << isPrime2(4444) << endl;
  cout << "123: " << isPrime2(123) << endl;
  cout << "125: " << isPrime2(125) << endl;
  cout << "10004: " << isPrime2(10004) << endl;
  cout << "99999999977: " << isPrime2(99999999977) << endl;
}
