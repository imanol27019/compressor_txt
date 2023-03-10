#ifndef _TMAP_TAD_
#define _TMAP_TAD_

#include <iostream>
#include "Array.hpp"

using namespace std;
template <typename K>
int cmpK(K a, K b)
{
   return a==b?0:a<b?-1:1;
}
template <typename K, typename V>
struct Map
{
   Array<K> keys;
   Array<V> values;
   int pos = 0;
};

template <typename K, typename V>
Map<K, V> map()
{
   Map<K, V> m;
   m.keys = array<K>();
   m.values = array<V>();
   return m;
}

template <typename K, typename V>
V* mapGet(Map<K, V> m, K k)
{
   int pos = arrayFind(m.keys,k,cmpK);
   if( pos<0 )
   {
      return NULL;
   }
   else
   {
      return arrayGet(m.values,pos);
   }
}

template <typename K, typename V>
V* mapPut(Map<K, V>& m, K k, V v)
{
   int pos = arrayFind(m.keys,k,cmpK);
   if( pos<0 )
   {
      arrayAdd(m.values,v);
      arrayAdd(m.keys,k);
   }
   else
   {
      arraySet(m.values,pos,v);
   }
   pos = arrayFind(m.keys,k,cmpK);
   return arrayGet(m.values,pos);
}

template <typename K, typename V>
bool mapContains(Map<K, V> m, K k)
{
   int pos = arrayFind(m.keys,k,cmpK);

   return pos<0?false:true;
}

template <typename K, typename V>
V mapRemove(Map<K, V>& m, K k)
{
   int pos = arrayFind(m.keys,k,cmpK);
   V v = arrayRemove(m.values,pos);
   arrayRemove(m.keys,pos);
   return v;
}

template <typename K, typename V>
void mapRemoveAll(Map<K, V>& m)
{
   m = map<K, V>();
}

template <typename K, typename V>
int mapSize(Map<K, V> m)
{
   return arraySize<K>(m.keys);
}

template <typename K, typename V>
bool mapHasNext(Map<K, V> m)
{
   if( m.pos<arraySize(m.keys)&&m.pos<arraySize(m.values) )
   {
      return true;
   }
   else
   {
      return false;
   }
}

template <typename K, typename V>
K mapNextKey(Map<K, V>& m)
{
   K* k = arrayGet(m.keys,m.pos);
   m.pos++;
   return *k;
}

template <typename K, typename V>
V* mapNextValue(Map<K, V>& m)
{
   V* v = arrayGet(m.values,m.pos);
   m.pos++;
   return v;
}

template <typename K, typename V>
void mapReset(Map<K, V>& m)
{
   m.pos = 0;
}

template <typename K, typename V>
void mapSortByKeys(Map<K, V>& m, int cmpKK(K, K))
{
   int i,j;
   K aux,auxaux;
   V auxV,auxauxV;
   for( i = 0; i<m.keys.l; i++ )
   {
      for( j = 0; j<m.keys.l-1; j++ )
      {
         if( cmpKK(m.keys.arr[j],m.keys.arr[j+1])>0 )
         {
            aux = m.keys.arr[j];
            auxaux = m.keys.arr[j+1];
            m.keys.arr[j] = auxaux;
            m.keys.arr[j+1] = aux;

            auxV = m.values.arr[j];
            auxauxV = m.values.arr[j+1];
            m.values.arr[j] = auxauxV;
            m.values.arr[j+1] = auxV;
         }
      }
   }
}

template <typename K, typename V>
void mapSortByValues(Map<K, V>& m, int cmpVV(V, V))
{
   int i,j;
   K aux,auxaux;
   V auxV,auxauxV;
   for( i = 0; i<m.values.l; i++ )
   {
      for( j = 0; j<m.values.l-1; j++ )
      {
         if( cmpVV(m.values.arr[j],m.values.arr[j+1])>0 )
         {
            auxV = m.values.arr[j];
            auxauxV = m.values.arr[j+1];
            m.values.arr[j] = auxauxV;
            m.values.arr[j+1] = auxV;
            aux = m.keys.arr[j];
            auxaux = m.keys.arr[j+1];
            m.keys.arr[j] = auxaux;
            m.keys.arr[j+1] = aux;
         }
      }
   }
}

#endif
