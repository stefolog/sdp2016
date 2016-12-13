#include <iostream>
#include "hashTable2.cpp"

using namespace std;

/*
  key = sorted(lowercase(string))
    e.g.
      sorted("ala bala") == " aaaabll"

  value = set of anagrams (lowercase)
*/
hashTable<string, TreeSet<string> > words;

// A -> a
string lowercase(string s) {
}

// ala -> aal
string sort(string s) {

}

int main() {
  string sampleData[] = { "listen", "stenli", "Listen", "AlaBala" };


  // FOREACH sampleData AS word {
  //   string key = sort(word);
  //   if (!words.contains(key)) {
  //     words.insert(key, TreeSet<string>());
  //   }
  //   words.find(key).add(word);
  // }

  for (int i = 0; i < 4; i++) {
    string word = sampleData[i];
    string key = sort(lowercase(word));

    elem_link1<string>* p = words.find(key);
    if (p == NULL) {
      words.insert(key, TreeSet<string>());
    }

    elem_link1<string>* anagramsForKey = words.find(key);
    (anagramsForKey->inf).add(word);
  }

  return 0;
}
