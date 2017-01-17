#include <iostream>
#include "../templates/queue.cpp"

using namespace std;

enum Priority {
  LOW, MEDIUM, HIGH
};

template<typename T>
class PriorityQueue {
public:
  void push(T const &, Priority);
  T pop();
  bool empty() const;
private:
  queue<T> low;
  queue<T> medium;
  queue<T> high;
};

template<typename T>
void PriorityQueue<T>::push(T const & x, Priority p) {
  switch(p) {
    case LOW:
      low.push(x);
      break;
    case MEDIUM:
      medium.push(x);
      break;
    case HIGH:
      high.push(x);
      break;
    default:
      throw "Unknown Priority";
  }
}

template<typename T>
T PriorityQueue<T>::pop() {
  T result;
  if (high.pop(result)) {
    return result;
  }

  if (medium.pop(result)) {
    return result;
  }

  if (low.pop(result)) {
    return result;
  }

  throw "Queue is empty";
}

template<typename T>
bool PriorityQueue<T>::empty() const {
  return low.empty() && medium.empty() && high.empty();
}

int main() {
  PriorityQueue<string> diskoQueue;
  diskoQueue.push("Pesho Studenta", Priority::LOW);
  diskoQueue.push("Ivan Daskala", Priority::MEDIUM);
  diskoQueue.push("Gosho Batkata", Priority::HIGH);

  cout << diskoQueue.pop() << endl;
  cout << diskoQueue.pop() << endl;
  cout << diskoQueue.pop() << endl;
}
