#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "llist.cpp"

template <typename T>
class graph
{
	public:
		void addTop(const T&);
		void deleteTop(const T&);
		void addRib(const T&, const T&);
		void deleteRib(const T&, const T&);
		bool top(const T&);
		bool rib(const T&, const T&);
		bool empty() const;
		elem<T>* point(const T&);
		LList<T> vertexes();
		void print();
	private:
		LList< LList<T> > g;
};

// включва а като връх
template <typename T>
void graph<T>::addTop(const T& a)
{ // създаване на линеен списък, съдържащ елемента a
	LList<T> l;
	l.ToEnd(a);
	// включване на върха a към графа
	g.ToEnd(l);
}

// изключва върха а
template <typename T>
void graph<T>::deleteTop(const T& a)
{ // обхождане на графа с цел изтриване на всички
	// ребра от произволен връх до върха a
	g.IterStart();
	elem<LList<T> >* p = g.Iter(), *r;
	while(p)
	{
		p->inf.IterStart();
		elem<T>* q = p->inf.Iter();
		if(rib(q->inf, a)) deleteRib(q->inf, a);
		p = p->link;
	}
	// изтриване на линейния списък, представящ
	// върха a и неговите наследници
	g.IterStart();
	elem<T>* q;
	do
	{
		r = g.Iter();
		r->inf.IterStart();
		q = r->inf.Iter();
	}
	while(q->inf != a); // a е връх на графа
	LList<T> x;
	g.deleteElem(r, x);
}

// включва ребро от върха a до върха b
template <typename T>
void graph<T>::addRib(const T& a, const T& b)
{ // намиране на указател към върха a
	elem<T>* q = point(a), // намира указател към върха a
		*p;
	// включване на върха b в списъка от наследниците на върха a
	p = new elem<T>;

	p->inf = b;
	p->link = q->link;
	q->link = p;
}

// изключва реброто от върха a до върха b
template <typename T>
void graph<T>::deleteRib(const T& a, const T& b)
{
	g.IterStart();
	elem<LList<T> > *p;
	elem<T> *q;
	do
	{
		p = g.Iter();
		p->inf.IterStart();
		q = p->inf.Iter();
	}
	while(q->inf != a);
	q = q->link;
	// намиране на указател към наследника b на върха a
	while(q->inf != b) q = q->link;
	T x;
	p->inf.deleteElem(q, x);
}

// проверява дали a е връх
template <typename T>
bool graph<T>::top(const T& a)
{
	if(g.empty()) return false;
	g.IterStart();
	elem<LList<T> > *p = g.Iter();
	elem<T> *q;
	do
	{
		p->inf.IterStart();
		q = p->inf.Iter();
		p = p->link;
	}
	while(q->inf != a && p);

	return q->inf == a;
}

// проверява дали има ребро от върха a до върха b
template <typename T>
bool graph<T>::rib(const T& a, const T& b)
{
	elem<T>* p = point(a); // намира указател към върха a
	p = p->link;
	while(p && p->inf != b) p = p->link;
	return p != NULL;
}

// проверява дали графът е празен
template <typename T>
bool graph<T>::empty() const
{
	return g.empty();
}

// намира указател към върха a на графа
template <typename T>
elem<T>* graph<T>::point(const T& a)
{
	g.IterStart();
	elem<LList<T> > *p;
	elem<T> *q;
	do
	{
		p = g.Iter();
		p->inf.IterStart();
		q = p->inf.Iter();
	}
	while(q->inf != a);
	return q;
}

// връща списък от върховете
template <typename T>
LList<T> graph<T>::vertexes()
{
	LList<T> l;
	g.IterStart();
	elem<LList<T> > *p = g.Iter();
	while(p)
	{
		p->inf.IterStart();
		elem<T>* q = p->inf.Iter();
		l.ToEnd(q->inf);
		p = p->link;
	}
	return l;
}

template <typename T>
void graph<T>::print()
{
	g.IterStart();
	elem<LList<T> > *p = g.Iter();
	while(p)
	{
		p->inf.print();
		p = p->link;
	}
	cout << endl;
}


#endif // !GRAPH_H_INCLUDED
