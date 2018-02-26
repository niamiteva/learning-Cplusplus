#ifndef LLIST_H_INCLUDED
#define LLIST_H_INCLUDED

#include <iostream>

using namespace std;

template <class T>
struct elem_link1
{
  T inf; // cointains the data of the current element
  elem_link1 *link; // pointer to the next element
};

template <class T>
class LList
{
public:
  LList();// constructor
  ~LList(); //destructor
  LList(LList const&); //copy constructor
  LList& operator=(LList const &); // operator=
  
  void print();//prints the list
  void IterStart(elem_link1<T>* = NULL);//puts the pointer at the beginning of the list
  elem_link1<T>* Iter();//iterator
  void ToEnd(T const &);//adds element at the end of the list

  void InsertAfter(elem_link1<T> *, T const &); // adds element after the pointed element
  void InsertBefore(elem_link1<T> *, T const &);// add element before the pointed element

  int DeleteAfter(elem_link1<T> *, T &); // deletes element after the pointed element
  int DeleteBefore(elem_link1<T> *, T &); //deletes element before the pointed element
  void DeleteElem(elem_link1<T> *, T &); // deletes element from position p

  bool empty();// checks if the list is empty
  int len(); // returns the length of the list
  void concat(LList const&);// concatenate two lists
  void reverse(); // reverse list

  T operator[](int idx);
private:
  elem_link1<T> *Start, *End, *Current; // pointers
  void DeleteList(); // helepr functions
  void CopyList(LList<T> const &);
};

//constructor
template <class T>
LList<T>::LList()
{
  Start = NULL;
  End = NULL;
}
//destructor
template <class T>
LList<T>::~LList()
{
  DeleteList();
}
//copy constructor
template <class T>
LList<T>::LList(LList<T> const& r)
{
  CopyList(r);
}
//operator=
template <class T>
LList<T>& LList<T>::operator=(LList<T> const & r)
{
  if(this!=&r)
  {
    DeleteList();
    CopyList(r);
  }
  return *this;
}
//helper
template <class T>
void LList<T>::DeleteList()
{
  //deletes all elements from the start to the end
  elem_link1<T> *p;
  while(Start)
  {
    p = Start;
    Start = Start->link;
    delete p;
  }
  End = NULL;
}
//helper
template <class T>
void LList<T>::CopyList(LList<T> const & r)
{
  //copy all the elemnts from a list 
  Start = End = NULL;
  if(r.Start)
  {
    elem_link1<T> *p = r.Start;
    while(p)
    {
      ToEnd(p->inf);
      p=p->link;
    }
  }
}

template <class T>
void LList<T>::print()
{
  IterStart();
  elem_link1<T>* e = Iter();
  while(e)
  {
    cout << e->inf << " ";
    e = Iter();
  }
  cout << endl;
}

template <class T>
void LList<T>::IterStart(elem_link1<T> *p)
{
  if (p) Current = p;
  else Current = Start;
}

template <class T>
elem_link1<T>* LList<T>::Iter()
{
  elem_link1<T> *p = Current;
  if(Current)Current = Current->link;
  return p;
}

template <class T>
void LList<T>::ToEnd(T const & x)
{
  Current = End;
  End = new elem_link1<T>;
  End->inf = x;
  End->link = NULL;
  if(Current) Current->link = End; 
  else Start = End;// if this is the first element of the list
}

template <class T>
void LList<T>::InsertAfter(elem_link1<T> *p, T const & x)
{
  elem_link1<T> *q = new elem_link1<T>;
  q->inf = x;
  q->link = p->link;
  if(p==End) End = q;//if the current element is the last the new elemnt wil now be the last
  p->link = q;
}

template <class T>
void LList<T>::InsertBefore(elem_link1<T> * p, T const& x)
{
  elem_link1<T> *q = new elem_link1<T>;
  *q = *p;// we exchange the addresses
  if(p==End) End = q;
  p->inf = x;
  p->link = q;
}

template <class T>
int LList<T>::DeleteAfter(elem_link1<T> *p, T &x)
{
  if(p->link)
  {
    elem_link1<T> *q = p->link;
    x = q->inf;
    p->link = q->link;
    if(q==End) End = p;
    delete q;
    return 1;
  }
  else return 0;
}

template <class T>
void LList<T>::DeleteElem(elem_link1<T> *p, T &x)
{
  if(p==Start)
  {
    x = p->inf;
    if(Start == End){Start = End = NULL;}
    else Start = Start->link;
    delete p;
  }
  else
  {
    elem_link1<T> *q = Start;
    while(q->link!=p)q = q->link;
    DeleteAfter(q, x);
  }
}

template <class T>
int LList<T>::DeleteBefore(elem_link1<T> *p, T &x)
{
  if(p!=Start)
  {
    elem_link1<T> *q=Start;
    while(q->link!=p)q = q->link;
    DeleteElem(q, x);
    return 1;
  } else return 0;
}

template <class T>
bool LList<T>::empty()
{
  return End == NULL;
}

template <class T>
int LList<T>::len()
{
  int n = 0;
  IterStart();
  elem_link1<T> *p= Iter();
  while(p)
  {
    n++;
    p = Iter();
  }
  return n;
}

template <class T>
void LList<T>::concat(LList<T> const &L)
{
  elem_link1<T> *p = L.Start;
  while(p)
  {
    ToEnd(p->inf);
    p = p->link;
  }
}

template <class T>
void LList<T>::reverse()
{
  LList<T> l;
  IterStart();
  elem_link1<T> *p = Iter();
  if(p)
  {
    l.ToEnd(p->inf);
    p = p->link;
    while(p)
    {
      l.InsertBefore(l.Start, p->inf);
      p = p->link;
    }
  }
  *this = l;
}

#endif // !LLIST_H_INCLUDED
