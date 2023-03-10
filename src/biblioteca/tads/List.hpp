#ifndef _TLIST_TAD_
#define _TLIST_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template <typename T>
struct List
{
   Node<T>* p;
   Node<T>* aux;


};

template <typename T>
List<T> list()
{
   List<T> lst;
   lst.p = NULL;
   lst.aux = NULL;
   return lst;
}

template <typename T>
T* listAdd(List<T>& lst, T e)
{
   Node<T>* ret = add<T>(lst.p,e);
   return &ret->info;
}

template <typename T>
T* listAddFirst(List<T>& lst, T e)
{
   Node<T>* ret = addFirst<T>(lst.p,e);
   return &ret->info;
}

template <typename T, typename K>
T listRemove(List<T>& lst, K k, int cmpTK(T, K))
{
   T t = remove<T, K>(lst.p,k,cmpTK);
   return t;
}

template <typename T>
T listRemoveFirst(List<T>& lst)
{
   T t = removeFirst<T>(lst.p);
   return t;
}

template <typename T, typename K>
T* listFind(List<T> lst, K k, int cmpTK(T, K))
{
   Node<T>* ret = find<T>(lst.p,k,cmpTK);

   return &ret->info;
}

template <typename T>
bool listIsEmpty(List<T> lst)
{
   return isEmpty(lst.p);
}

template <typename T>
int listSize(List<T> lst)
{
   Node<T>* p = lst.p;
   int i = 0;

   while( p!=NULL )
   {
      p = p->sig;
      i++;
   }

   return i;
}

template <typename T>
void listFree(List<T>& lst)
{
   lst.p = NULL;
}

template <typename T>
T* listOrderedInsert(List<T>& lst, T t, int cmpTT(T, T))
{
   Node<T>* ret =orderedInsert<T>(lst.p,t,cmpTT);
   return &ret->info;
}

template <typename T>
void listSort(List<T>& lst, int cmpTT(T, T))
{
   sort<T>(lst.p,cmpTT);
}

template <typename T>
void listReset(List<T>& lst)
{
   lst.aux=lst.p;
}

template <typename T>
bool listHasNext(List<T> lst)
{

   return lst.aux!=NULL;
}

template <typename T>
T* listNext(List<T>& lst)
{
   T* ret = &lst.aux->info;
   lst.aux = lst.aux->sig;
   return ret;


}

template <typename T>
T* listNext(List<T>& lst, bool& endOfList)
{
   lst.aux = lst.p.sig;
   endOfList = lst.aux.sig==NULL;
   return &lst.aux->info;
}

#endif
