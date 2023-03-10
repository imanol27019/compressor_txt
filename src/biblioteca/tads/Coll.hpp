#ifndef _TCOLL_T_
#define _TCOLL_T_

#include <iostream>
#include "../funciones/strings.hpp"

using namespace std;

template<typename T>
struct Coll
{
};

template<typename T>
Coll<T> coll(char sep)
{
   Coll<T> c;
   return c;
}

template<typename T>
Coll<T> coll()
{
   Coll<T> c;
   return c;
}

template<typename T>
int collSize(Coll<T> c)
{
   return 0;
}

template<typename T>
void collRemoveAll(Coll<T>& c)
{
}

template<typename T>
void collRemoveAt(Coll<T>& c, int p)
{
}

template<typename T>
int collAdd(Coll<T>& c,T t,string tToString(T))
{
   return 0;
}

template <typename T>
void collSetAt(Coll<T>& c,T t,int p,string tToString(T))
{
}

template <typename T>
T collGetAt(Coll<T> c,int p,T tFromString(string))
{
   T t;
   return t;
}

template <typename T, typename K>
int collFind(Coll<T> c,K k,int cmpTK(T,K),T tFromString(string))
{
   return 0;
}

template <typename T>
void collSort(Coll<T>& c,int cmpTT(T,T),T tFromString(string),string tToString(T))
{
}

template<typename T>
bool collHasNext(Coll<T> c)
{
   return true;
}

template<typename T>
T collNext(Coll<T>& c,T tFromString(string))
{
   T t;
   return t;
}

template<typename T>
T collNext(Coll<T>& c,bool& endOfColl,T tFromString(string))
{
   T t;
   return t;
}

template<typename T>
void collReset(Coll<T>& c)
{
}

#endif
