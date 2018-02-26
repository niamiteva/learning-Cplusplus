#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "llist.cpp"

template <typename T>
class graph
{
	public:
		void addTop(const T&); // adds top in the graph
		void deleteTop(const T&); //deletes top from the graph
		void addRib(const T&, const T&); // adds rib from top a to top b in the graph
		void deleteRib(const T&, const T&); // delete rib from the graph
		bool top(const T&); // checks if there is top x
		bool rib(const T&, const T&); // checks if there is rib from top x to top y
		bool empty() const; // checks if the graph is empty
		elem_link1<T>* point(const T&); // returns the adress of a top x
		LList<T> vertexes(); // returns linked list with all the vertexes of the graph
		void print(); // prints the graph
	private:
		LList< LList<T> > g; //graph g
};

// adds a as a top(node) of the graph
template <typename T>
void graph<T>::addTop(const T& a)
{ 
	//creating a linked list, containing a
	LList<T> l;
	l.ToEnd(a);
	// adding the top in the graph
	g.ToEnd(l);
}

// deleting the top a from the graph
template <typename T>
void graph<T>::deleteTop(const T& a)
{ 
	// searching in the graph for all ribs from the current top to top a to be deleted
	g.IterStart();
	elem_link1<LList<T> >* p = g.Iter(), *r;
	while(p)
	{
		p->inf.IterStart();
		elem_link1<T>* q = p->inf.Iter();
		if(rib(q->inf, a)) deleteRib(q->inf, a);
		p = p->link;
	}
	
	// deleting the linked list representing the top a and its childs
	g.IterStart();
	elem_link1<T>* q;
	do
	{
		r = g.Iter();
		r->inf.IterStart();
		q = r->inf.Iter();
	}
	while(q->inf != a); // a is top of the graph
	LList<T> x;
	g.deleteElem(r, x);
}

//adding rib a from top b in the graph
template <typename T>
void graph<T>::addRib(const T& a, const T& b)
{
	elem_link1<T>* q = point(a), // finding a pointer to the adsress of the top a
		*p;

	// inserting the top b in the top a's childslist
	p = new elem_link1<T>;

	p->inf = b;
	p->link = q->link;
	q->link = p;
}

//deleteing the rib from top a to top b
template <typename T>
void graph<T>::deleteRib(const T& a, const T& b)
{
	g.IterStart();
	elem_link1<LList<T> > *p;
	elem_link1<T> *q;
	do
	{
		p = g.Iter();
		p->inf.IterStart();
		q = p->inf.Iter();
	}
	while(q->inf != a);
	q = q->link;
	// finding pointer to the child b of the top a
	while(q->inf != b) q = q->link;
	T x;
	p->inf.deleteElem(q, x);
}

//checking if a is a top of the graph
template <typename T>
bool graph<T>::top(const T& a)
{
	if(g.empty()) return false;
	g.IterStart();
	elem_link1<LList<T> > *p = g.Iter();
	elem_link1<T> *q;
	do
	{
		p->inf.IterStart();
		q = p->inf.Iter();
		p = p->link;
	}
	while(q->inf != a && p);

	return q->inf == a;
}

//checking if there is rib from top a to top b
template <typename T>
bool graph<T>::rib(const T& a, const T& b)
{
	elem_link1<T>* p = point(a); // pointer to the top a
	p = p->link;
	while(p && p->inf != b) p = p->link;
	return p != NULL;
}

// check if the graph is empty
template <typename T>
bool graph<T>::empty() const
{
	return g.empty();
}

// finds pointer to the tp of the graph
template <typename T>
elem_link1<T>* graph<T>::point(const T& a)
{
	g.IterStart();
	elem_link1<LList<T> > *p;
	elem_link1<T> *q;
	do
	{
		p = g.Iter();
		p->inf.IterStart();
		q = p->inf.Iter();
	}
	while(q->inf != a);
	return q;
}

//return list of the nodes
template <typename T>
LList<T> graph<T>::vertexes()
{
	LList<T> l;
	g.IterStart();
	elem_link1<LList<T> > *p = g.Iter();
	while(p)
	{
		p->inf.IterStart();
		elem_link1<T>* q = p->inf.Iter();
		l.ToEnd(q->inf);
		p = p->link;
	}
	return l;
}

template <typename T>
void graph<T>::print()
{
	g.IterStart();
	elem_link1<LList<T> > *p = g.Iter();
	while(p)
	{
		p->inf.print();
		p = p->link;
	}
	cout << endl;
}


#endif // !GRAPH_H_INCLUDED
