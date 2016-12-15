#include <iostream>
#include <ostream>
#include "../templates/graph.cpp"
#include "../templates/treeSet.cpp"

using namespace std;

struct Person
{
  string name;
  int age;
  LList<string> likes;
  string school;

  bool operator==(const Person& other) const {
    return this->name == other.name;
  }

  bool operator<(const Person& other) const {
    return this->name < other.name;
  }

  bool operator!=(const Person& other) {
    return this->name != other.name;
  }
};

ostream& operator<<(ostream& out, const Person& person) {
  out << person.name; //  << " " << person.age;
  return out;
}

template <typename T>
LList<T> findNeighbours(graph<T>& g, const T x) {
  if (!g.top(x)) {
    return LList<T>();
  }

  LList<T> result;
  elem_link1<T> *p = g.point(x);
  while (p->link) {
    p = p->link;
    result.ToEnd(p->inf);
  }

  return result;
}

template <typename T>
LList<T> filterNeighbours(graph<T>& g, const T x, bool (*filter)(T, T)) {
  if (!g.top(x)) {
    return LList<T>();
  }

  LList<T> result;
  elem_link1<T> *p = g.point(x);
  while (p->link) {
    p = p->link;
    if (filter(x, p->inf)) {
      result.ToEnd(p->inf);
    }
  }

  return result;
}

bool filterBySameAge(Person x, Person y) {
  return x.age == y.age;
}

LList<Person> findAllFriendWithSameAge(graph<Person>& people, Person person) {
  return filterNeighbours(people, person, filterBySameAge);
}

void problem1() {
  Person ivanDimtrov = { "Ivan Dimitrov", 24 };
  Person peterIvanov = { "Peter Ivanov", 22 };
  Person mariaGermanova = { "Maria Germanova", 48 };
  Person peterDimtrov = { "Peter Dimitrov", 24 };

  // init
  graph<Person> people;

  people.addTop(ivanDimtrov);
  people.addTop(peterIvanov);
  people.addTop(mariaGermanova);
  people.addTop(peterDimtrov);

  people.addRib(ivanDimtrov, peterIvanov);
  people.addRib(peterIvanov, ivanDimtrov);

  people.addRib(ivanDimtrov, mariaGermanova);
  people.addRib(mariaGermanova, ivanDimtrov);

  people.addRib(ivanDimtrov, peterDimtrov);
  people.addRib(peterDimtrov, ivanDimtrov);



  people.addRib(peterIvanov, mariaGermanova);
  people.addRib(mariaGermanova, peterIvanov);

  people.addRib(peterIvanov, peterDimtrov);
  people.addRib(peterDimtrov, peterIvanov);

  people.print();

  cout << "findAllFriendWithSameAge" << endl;
  findAllFriendWithSameAge(people, ivanDimtrov).print();
  // result: Peter Dimitrov
}

template <typename T>
TreeSet<T> toSet(LList<T> list) {
  TreeSet<T> set;

  elem_link1<T> *p;
  list.IterStart();
  while ((p = list.Iter())) {
    set.add(p->inf);
  }

  return set;
}

TreeSet<Person> friendsOfTheFriends(graph<Person>& people, Person person) {
  TreeSet<Person> friends = toSet(findNeighbours(people, person));
  TreeSet<Person> friendsOfFriends;

  TreeSetIterator<Person> iter = friends.iterator();
  while (iter.hasNext()) {
    Person aFriend = iter.next();
    friendsOfFriends = friendsOfFriends.unionSet(toSet(findNeighbours(people, aFriend)));
  }

  friendsOfFriends = friendsOfFriends.minusSet(friends);
  friendsOfFriends.remove(person);

  return friendsOfFriends;
}

int main() {
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

  friendsOfTheFriends(people, a).print();
}


