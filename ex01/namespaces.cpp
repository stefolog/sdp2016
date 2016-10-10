#include <iostream>

using namespace std;
  // cin
  // cout

namespace facebook {
  class User {
  public:
    void print() const {
      cout << "Facebook user" << endl;
    }
  };
}

namespace twitter {
  class User {
  public:
    void print() const {
      cout << "Twitter user" << endl;
    }
  };
}

void printTwitterUser() {
    using namespace twitter;
    User user;
    user.print();
}
void printFacebookUser() {
    using namespace facebook;
    User user;
    user.print();
}

int main() {
  int x;

  printTwitterUser();
  printFacebookUser();
}









