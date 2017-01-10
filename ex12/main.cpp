#include <iostream>
#include "../templates/LList.cpp"
// #include "hashTable.cpp"
#include <map>

using namespace std;

struct Tag {
  string key;
  string value;
  double confidence;
};

ostream& operator<<(ostream& out, const Tag& tag) {
  return out << tag.key << ": " << tag.value << " (" << tag.confidence << ")";
}

typedef LList<Tag> Request;

bool operator<(const Request& r1, const Request& r2) {
  return &r1 < &r2;
}

class Wit {
public:
  Request recognize(string text);
};

class Rules {
public:
  void add(Request request, string response) {

  }

  bool contains(Request r) {
    return true;
  }

  string get(Request r) {
    if (!contains(r)) {
      return "";
    }
    return "No marks yet!";
  }
};

class Bot {
public:
  void initWithRules() {
    { // rule 1
      Request request;

      Tag t1 = {"intent", "mark", 0;
      request.ToEnd(t1);

      Tag t2 = {"ala", "bala", 0};
      request.ToEnd(t2);

      rules.add(request, "No marks yet!");
    }

    { // rule 2
      Request request;

      Tag t1 = {"intent", "hi", 0.93};
      result.ToEnd(t1);

      rules.add(request, "Hi, how are you?");
    }

  }

  void ask(string text) {
    Request req = Wit().recognize(text);
    if (req.empty()) {
      cout << "I don't understand you..." << endl;
      return;
    }

    if (rules.contains(req)) {
      cout << rules.get(req) << endl;
    } else {
      cout << "I'm not programmed this way..." << endl;
    }
  }
private:
  Rules rules;
};

Request Wit::recognize(string text) {
  if (text == "What is my mark?") { // "No marks yet!"
    Request result;

    Tag t1 = {"intent", "mark", 0.93};
    result.ToEnd(t1);

    Tag t2 = {"ala", "bala", 0.87};
    result.ToEnd(t2);

    return result;
  }

  if (text == "My mark?") { // "No marks yet!"
    Request result;

    Tag t1 = {"intent", "mark", 0.95};
    result.ToEnd(t1);

    return result;
  }

  if (text == "Hello" || text == "Hi") { // "Hi, how are you?"
    Request result;

    Tag t1 = {"intent", "hi", 0.93};
    result.ToEnd(t1);

    return result;
  }

  return Request();
}

int main() {
  Bot bot;
  while (true) {
    cout << "> ";

    string userInput;
    getline(cin, userInput);

    bot.ask(userInput);
  }
}
