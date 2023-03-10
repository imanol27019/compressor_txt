#ifndef _TARR_TAD_
#define _TARR_TAD_

#include <iostream>
#include <stdlib.h>
#include "../funciones/arrays.hpp"

using namespace std;

template <typename T>
struct Array
{
   int cap = 1000;
   T* arr;
   int l;
};

template <typename T>
Array<T> array()
{
   Array<T> ret;
   ret.arr = new T[1000];
   ret.l = 0;
   return ret;
}

template <typename T>
int arrayAdd(Array<T>& a, T t)
{
   if( (a.l)==(a.cap)-2 )
   {
      int i,nuevaCap;
      nuevaCap = a.cap*2;
      T* b;
      b = new T[nuevaCap];
      for( i = 0; i<a.l; i++ )
      {
         b[i] = a.arr[i];
      }
      a.arr = b;
      a.cap = nuevaCap;
   }
   return add<T>(a.arr,a.l,t);
}

template <typename T>
T* arrayGet(Array<T> a, int p)
{
   T* r = &(a.arr[p]);
   return r;
}

template <typename T>
void arraySet(Array<T>& a, int p, T t)
{
   (a.arr[p]) = t;
   //   T* dir = arrayGet<T>(a,p);
   //   *dir = t;
}

template <typename T>
void arrayInsert(Array<T>& a, T t, int p)
{
   if( (a.l)==(a.cap)-2 )
   {
      int i,nuevaCap;
      nuevaCap = a.cap*2;
      T* b;
      b = new T[nuevaCap];
      for( i = 0; i<a.l; i++ )
      {

         b[i] = a.arr[i];
      }
      a.arr = b;
      a.cap = nuevaCap;
   }
   insert<T>(a.arr,a.l,t,p);
}

template <typename T>
int arraySize(Array<T> a)
{
   return a.l;
}

template <typename T>
T arrayRemove(Array<T>& a, int p)
{
   T t = *arrayGet<T>(a,p);
   remove<T>(a.arr,a.l,p);
   return t;
}

template <typename T>
void arrayRemoveAll(Array<T>& a)
{
   a = array<T>();
}

template <typename T, typename K>
int arrayFind(Array<T> a, K k, int cmpTK(T, K))
{
   int pos = find<T,K>(a.arr,a.l,k,cmpTK);
   return pos;
}

template <typename T>
int arrayOrderedInsert(Array<T>& a, T t, int cmpTT(T, T))
{
   return orderedInsert<T>(a.arr,a.l,t,cmpTT);
}

template <typename T>
void arraySort(Array<T>& a, int cmpTT(T, T))
{
   sort<T>(a.arr,a.l,cmpTT);
}

#endif
