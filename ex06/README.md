README.md

Упражнение 6
===

 * Цикличен списък (templates/cyclicList.cpp)
 * Двусвързан списък (templates/DLList.cpp)

Задача 1
---
Да се промени фунцкията tail, така че да използва цъкличен списък вместо масив като буфер.

void tail(string filename, int lines) {
  ifstream fin(filename);
  if (!fin) {
    throw "File not found";
  }

  int linesCount = 0;

  string * bufferLines = new string[lines];
  char buf[2000];
  while (fin.getline(buf, 2000)) {
    bufferLines[linesCount % lines] = string(buf);
    linesCount++;
  }
  fin.close();

  if (linesCount < lines) {
    for (int i = 0; i < linesCount; i++) {
      cout << bufferLines[i] << endl;
    }
  } else {
    for (int i = 0; i < lines; i++) {
      cout << bufferLines[(i + linesCount) % lines] << endl;
    }
  }

  delete[] bufferLines;
}


Задача 2
---
Напишете програма, която отпечатва едносвързан списък в обратен ред.
Напишете програма, която отпечатва двусвързан списък в обратен ред.
Направете сравнение в скоростите, при наличието на голям брой елементи (10000).


Задача 3
---
Да се реалзиира клас Range, който позволява взимането на произволна поредица от елементи от списък (едно или двусвързан).
Конструктори:
  Range(LList<T>, int startIdx, int endIdx)
  Range(DLList<T>, int startIdx, int endIdx)
  взимат частта от списъка от между индексите startIdx и endIdx включително.

  Range(LList<T>, elem_link1<T>* startElement, int count)
  Range(DLList<T>, elem_link2<T>* startElement, int count)
  взимат частта от списъка с начало startElement и брой елемент count. Ако count е отрицателно число се взимат предходните елементи.

Ако елементите в списъка не са достатъчни, да се лимитира частта до съществуващи такива. Например:
Ако имаме списък с 5 елемента, а вземе Range(list, 0, 10), трябва да са достъпни елементите с индекси [0, 4].

Реализирайте следните функции:
  int size() - връща броят елементи в поредицата
  Iterator<T> iterator() - връща итератор за елементите в поредицата

Интерфейс за класа на итератора:
Iterator<T>
  bool hasNext()
  T next()
