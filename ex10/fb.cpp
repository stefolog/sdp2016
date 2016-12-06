#include <iostream>
#include "../templates/graph.cpp"
#include "../templates/llist.cpp"

using namespace std;

struct Person {
  string name;
  int age;
  LList<string> interests;
  string school;

  bool operator==(const Person& other) const {
    return name == other.name;
  }

  bool operator!=(const Person& other) const {
    return name != other.name;
  }
};

ostream& operator<<(ostream& out, const Person& person) {
  out << person.name;
  return out;
}

template <typename T>
LList<T> findNeighbours(graph<T>& g, T node) {
  if (!g.top(node)) {
    return LList<T>();
  }

  LList<T> result;
  elem_link1<T> * p = g.point(node);
  while (p->link) {
    p = p->link;
    result.ToEnd(p->inf);
  }

  return result;
}

// TODO: use findNeighbours
template <typename T>
LList<T> filterNeighbourNodesBy(graph<T>& g, T node, bool (*filter)(T&, T&)) {
  if (!g.top(node)) {
    return LList<T>();
  }

  LList<T> result;
  elem_link1<T> * p = g.point(node);
  while (p->link) {
    p = p->link;
    if (filter(p->inf, node)) {
      result.ToEnd(p->inf);
    }
  }

  return result;
}

template <typename T>
bool contains(LList<T>& list, T& elem) {
  list.IterStart();
  elem_link1<T> * p;
  while ((p = list.Iter())) {
    if (p->inf == elem) {
      return true;
    }
  }
  return false;
}


bool sameAge(Person& p1, Person& p2) {
  return p1.age == p2.age;
}

// Biz domain -> Tech
LList<Person> findFriendsWithAge(graph<Person>& people, Person person, int age) {
  return filterNeighbourNodesBy(people, person, sameAge);
}

LList<Person> findFriendsWithSameAge(graph<Person>& people, Person person) {
  return findFriendsWithAge(people, person, person.age);
}

LList<Person> findFriendsOfFriends(graph<Person>& people, Person person) {
  if (!people.top(person)) {
    return LList<Person>();
  }

  LList<Person> unknownPeople;

  LList<Person> friends = findNeighbours(people, person);
  LList<Person> knownPeople = friends;
  knownPeople.ToEnd(person);

  friends.IterStart();
  elem_link1<Person> * p;
  while ((p = friends.Iter())) {
    LList<Person> friendsOfAFriend = findNeighbours(people, p->inf);

    friendsOfAFriend.IterStart();
    elem_link1<Person> * aFriendOfAFriend;

    while ((aFriendOfAFriend = friendsOfAFriend.Iter())) {
      if (!contains(knownPeople, aFriendOfAFriend->inf)) {
        if (!contains(unknownPeople, aFriendOfAFriend->inf)) {
          unknownPeople.ToEnd(aFriendOfAFriend->inf);
        }
      }
    }
  }

  return unknownPeople;
}

void problem1() {
  Person ivanDimtrov = { "Ivan Dimitrov", 24 };
  Person peterIvanov = { "Peter Ivanov", 22 };
  Person mariaGermanova = { "Maria Germanova", 48 };
  Person peterDimtrov = { "Peter Dimitrov", 24 };

  graph<Person> people;
  people.addTop(ivanDimtrov);
  people.addTop(peterIvanov);
  people.addTop(mariaGermanova);
  people.addTop(peterDimtrov);

  people.addRib(ivanDimtrov, mariaGermanova);
  people.addRib(mariaGermanova, ivanDimtrov);

  people.addRib(ivanDimtrov, peterDimtrov);
  people.addRib(peterDimtrov, ivanDimtrov);

  people.addRib(ivanDimtrov, peterIvanov);
  people.addRib(peterIvanov, ivanDimtrov);

  people.print();
  cout << " ... END OF GRAPH ... " << endl;

  findFriendsWithSameAge(people, ivanDimtrov).print();
}

void problem2() {
  graph<Person> people;

  Person a = { "a" };
  Person b = { "b" };
  Person c = { "c" };
  Person d = { "d" };
  Person e = { "e" };
  Person f = { "f" };
  Person g = { "g" };
  Person h = { "h" };

  people.addTop(a);
  people.addTop(b);
  people.addTop(c);
  people.addTop(d);
  people.addTop(e);
  people.addTop(f);
  people.addTop(g);
  people.addTop(h);

  people.addRib(a, b);
  people.addRib(b, a);
  people.addRib(a, c);
  people.addRib(c, a);
  people.addRib(a, d);
  people.addRib(d, a);

  people.addRib(b, e);
  people.addRib(e, b);
  people.addRib(b, f);
  people.addRib(f, b);
  people.addRib(b, c);
  people.addRib(c, b);

  people.addRib(c, g);
  people.addRib(g, c);
  people.addRib(c, h);
  people.addRib(h, c);
  people.addRib(c, d);
  people.addRib(d, c);

  people.addRib(d, g);
  people.addRib(g, d);
  people.addRib(d, h);
  people.addRib(h, d);

  people.print();
  cout << "END OF Graph..." << endl;

  // TODO homework - 2 common interests
  findFriendsOfFriends(people, a).print();
}

LList<Person> findPossibleSchoolMates(graph<Person>& g, Person person) {
  LList<Person> possibleMates;

  LList<Person> allPeople = g.vertexes();
  allPeople.IterStart();
  elem_link1<Person> * p;

  while ((p = allPeople.Iter())) {
    if (p->inf == person) {
      continue;
    }
    if (!g.rib(p->inf, person)) {
      if (person.age == p->inf.age && person.school == p->inf.school) {
        possibleMates.ToEnd(p->inf);
      }
    }
  }

  return possibleMates;
}

void problem3() {
  graph<Person> people;

  Person a = { "a", 24, LList<string>(), "alabala"};
  Person b = { "b" };
  Person c = { "c" };
  Person d = { "d" };
  Person e = { "e" };
  Person f = { "f" };
  Person g = { "g" };
  Person h = { "h" };
  Person i = { "i", 24, LList<string>(), "alabala"};
  Person j = { "j" };

  people.addTop(a);
  people.addTop(b);
  people.addTop(c);
  people.addTop(d);
  people.addTop(e);
  people.addTop(f);
  people.addTop(g);
  people.addTop(h);
  people.addTop(i);
  people.addTop(j);

  people.addRib(a, b);
  people.addRib(b, a);
  people.addRib(a, c);
  people.addRib(c, a);
  people.addRib(a, d);
  people.addRib(d, a);

  people.addRib(b, e);
  people.addRib(e, b);
  people.addRib(b, f);
  people.addRib(f, b);
  people.addRib(b, c);
  people.addRib(c, b);

  people.addRib(c, g);
  people.addRib(g, c);
  people.addRib(c, h);
  people.addRib(h, c);
  people.addRib(c, d);
  people.addRib(d, c);

  people.addRib(d, g);
  people.addRib(g, d);
  people.addRib(d, h);
  people.addRib(h, d);

  people.addRib(i, j);
  people.addRib(j, i);

  people.print();
  cout << "END OF Graph..." << endl;

  findPossibleSchoolMates(people, a).print();
}

int main() {
  // problem1();
  // problem2();
  problem3();

  return 0;
}
