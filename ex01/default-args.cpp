#include <iostream>

using namespace std;

int power(int x, int n = 2) {
  int res = 1;
  for (int i = 0; i < n; i++) {
    res *= x;
  }
  return res;
}

// overloading
int p2(int x) {
  return power(x, 2);
}

int p3(int x) {
  return power(x, 3);
}

class AppConfig {
private:
    bool debug;
public:
    bool isDebug() const {
      return debug;
    }

    AppConfig(bool debug) {
      this->debug = debug;
    }

    static AppConfig dev() {
      return AppConfig(true);
    }

    static AppConfig prod() {
      return AppConfig(false);
    }
};

AppConfig currentConfiguration() {
  bool isProd = false;
  return isProd ? AppConfig::prod() : AppConfig::dev();
}

void printDebugMessage(string mesg, AppConfig config) {
  if (config.isDebug()) {
    cout << mesg;
  }
}

void printDebugMessage(string mesg) {
  printDebugMessage(mesg, currentConfiguration());
}


int main() {
  printDebugMessage("Hello there");
  cout << power(6) << endl;
}
