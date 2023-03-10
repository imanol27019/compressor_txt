#ifndef _TARRAYS_T_
#define _TARRAYS_T_

#include <iostream>

template <typename T>
int add(T arr[], int& len, T e)
{
   arr[len] = e;
   len++;
   return len-1;
}

template <typename T>
void insert(T arr[], int& len, T e, int p)
{
   //  arr[p] = e;
   for( int i = len; i>p; i-- )
   {
      T aux = arr[i-1];
      arr[i] = aux;

   }
   arr[p] = e;
   len++;
}

template <typename T>
T remove(T arr[], int& len, int p)
{
   T ret = arr[p];
   for( int i = p; i<len-1; i++ )
   {
      T aux = arr[i+1];
      arr[i] = aux;

   }

   len--;

   return ret;
}

template <typename T, typename K>
int find(T arr[], int len, K k, int cmpTK(T, K))
{
   int i = 0;
   int ret = -1;
   while( len>0 )
   {
      if( cmpTK(arr[i],k)==0 )
      {
         ret = i;
      }
      i++;
      len--;
   }
   return ret;
}

template <typename T>
int orderedInsert(T arr[], int& len, T e, int cmpTT(T, T))
{
   int i;
   if( len==0 )
   {
      add(arr,len,e);
   }
   else
   {

      for( i = 0; i<len and cmpTT(arr[i],e)<0; i++ )
      {
         if( cmpTT(arr[i],e)>0 )
         {
            insert<T>(arr,len,e,i);

         }

      }
      insert<T>(arr,len,e,i);
   }

   return i-1;
}

template <typename T>
void sort(T arr[], int len, int cmpTT(T, T))
{
   int i,j;
   T aux,auxaux;
   for( i = 0; i<len; i++ )
   {
      for( j = 0; j<len-1; j++ )
      {
         if( cmpTT(arr[j],arr[j+1])>0 )
         {
            aux = arr[j];
            auxaux = arr[j+1];
            arr[j] = auxaux;
            arr[j+1] = aux;
         }
      }
   }
}

#endif
