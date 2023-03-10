#ifndef _TLIST_T_
#define _TLIST_T_

#include <iostream>
#include <stdio.h>

template <typename T>
struct Node
{
   T info;
   Node* sig;
};

template <typename T>
Node<T>* add(Node<T>*& p, T e)
{
   Node<T>* nuevo = new Node<T>();
   nuevo->info = e;
   nuevo->sig = NULL;
   if( p!=NULL )
   {
      Node<T>* aux = p;
      while( aux->sig!=NULL )
      {
         aux = aux->sig;
      }
      aux->sig = nuevo;
   }
   else
   {
      p = nuevo;
   }

   return nuevo;
}

template <typename T>
Node<T>* addFirst(Node<T>*& p, T e)
{
   Node<T>* nuevo = new Node<T>();
   nuevo->info = e;
   nuevo->sig = p;
   p = nuevo;
   return p;
}

template <typename T, typename K>
T remove(Node<T>*& p, K k, int cmpTK(T, K))
{
   T t;
   Node<T>* aux = p;
   Node<T>* anterior = NULL;
   while( aux!=NULL&&cmpTK(aux->info,k)!=0 )
   {
      anterior = aux;
      aux = aux->sig;
   }
   if( anterior==NULL )
   {
      p = aux->sig;
   }
   else
   {
      anterior->sig = aux->sig;
   }
   t = aux->info;
   delete aux;
   return t;
}

template <typename T>
T removeFirst(Node<T>*& p)
{
   Node<T>* aux = p;
   p = p->sig;
   T ret = aux->info;
   delete aux;
   return ret;
}

template <typename T, typename K>
Node<T>* find(Node<T>* p, K k, int cmpTK(T, K))
{
   Node<T>* aRetornar = NULL;
   Node<T>* aux = p;
   while( aux!=NULL )
   {
      if( cmpTK(aux->info,k)==0 )
      {
         aRetornar = aux;
      }
      aux = aux->sig;
   }

   return aRetornar;
}

template <typename T>
Node<T>* orderedInsert(Node<T>*& p, T e, int cmpTT(T, T))
{

   Node<T>* nuevo = new Node<T>();
   nuevo->info = e;

   Node<T>* aux = NULL;

   if( p==NULL||cmpTT(e,p->info)<0 )
   {
      nuevo->sig = p;
      p = nuevo;
   }
   else
   {
      aux = p;

      while( aux->sig!=NULL&&cmpTT(e,aux->sig->info)>0 )
      {
         aux = aux->sig;
      }
      nuevo->sig = aux->sig;
      aux->sig = nuevo;
   }
   return nuevo;
}

template <typename T>
Node<T>* searchAndInsert(Node<T>*& p, T e, bool& enc, int cmpTT(T, T))
{

   Node<T>* ret = find<T, T>(p,e,cmpTT);
   enc = true;
   if( ret==NULL )
   {
      ret = orderedInsert<T>(p,e,cmpTT);

      enc = false;
   }
   return ret;
}

template <typename T>
void sort(Node<T>*& p, int cmpTT(T, T))
{
   Node<T>* i = p;
   T t;
   while( i!=NULL )
   {
      Node<T>* aux = i->sig;
      while( aux!=NULL )
      {
         if( cmpTT(i->info,aux->info)>0 )
         {
            t = aux->info;
            aux->info = i->info;
            i->info = t;
         }
         aux = aux->sig;
      }
      i = i->sig;
   }
}

template <typename T>
bool isEmpty(Node<T>* p)
{

   return p==NULL;
}

template <typename T>
void free(Node<T>*& p)
{
   p = NULL;
}

template <typename T>
Node<T>* push(Node<T>*& p, T e)
{
   return addFirst<T>(p,e);
}

template <typename T>
T pop(Node<T>*& p)
{
   T t = removeFirst<T>(p);
   return t;
}

template <typename T>
Node<T>* enqueue(Node<T>*& p, Node<T>*& q, T e)
{
   return NULL;
}

template <typename T>
Node<T>* enqueue(Node<T>*& q, T e)
{
   return NULL;
}

template <typename T>
T dequeue(Node<T>*& p, Node<T>*& q)
{
   T t;
   return t;
}

template <typename T>
T dequeue(Node<T>*& q)
{
   T t;
   return t;
}

#endif
