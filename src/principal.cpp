#ifndef _MAIN
#define _MAIN

#include <iostream>
#include "biblioteca/funciones/strings.hpp"
#include "biblioteca/funciones/tokens.hpp"
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/tads/Array.hpp"
#include "biblioteca/tads/Map.hpp"
#include "biblioteca/tads/List.hpp"
#include "biblioteca/tads/Stack.hpp"
#include "biblioteca/tads/Queue.hpp"
#include "biblioteca/tads/Coll.hpp"
#include "biblioteca/tads/BitWriter.hpp"
#include "biblioteca/tads/BitReader.hpp"
#include "biblioteca/tads/huffman/HuffmanSetup.hpp"
#include "principal.hpp"
using namespace std;
int cmpHuffmanTreeInfo(HuffmanTreeInfo a, HuffmanTreeInfo b)
{
   int ret;
   if( a.n>b.n )
   {
      ret = 1;
   }
   if( a.n<b.n )
   {
      ret = -1;
   }
   if( a.n==b.n )
   {
      if( a.c>b.c )
      {
         ret = 1;
      }
      else
      {
         ret = -1;
      }
   }
   return ret;
}
void inicializoArray(HuffmanTable tabla[])
{
   unsigned int a = 0;
   while( a<256 )
   {
      unsigned int cero = 0;
      string vacio = "";
      tabla[a].n = cero;
      tabla[a].cod = vacio;
      a++;
   }

}
void contarOcurrencias(string fName, HuffmanTable tabla[])
{
   // cargo el array con los contadores en 0
   inicializoArray(tabla);

   // abro el archivo
   const char * c = fName.c_str();
   FILE* f = fopen(c,"r+b");

   // recorro el archivo y sumo al contador
   unsigned char a = read<unsigned char>(f);
   while( !feof(f) )
   {
      unsigned int codA = a;
      tabla[codA].n++;
      a = read<unsigned char>(f);
   }
   fclose(f);
}
void crearLista(List<HuffmanTreeInfo>& lista, HuffmanTable tabla[])
{
   // recorro el array de contadores y agrego a la lista los que son mayores a 0
   // los contadores menores a 0 los ignoro
   for( int i = 0; i<256; i++ )
   {
      if( tabla[i].n>0 )
      {
         HuffmanTreeInfo aux;
         aux.c = i;
         aux.n = tabla[i].n;
         aux.left = NULL;
         aux.right = NULL;
         listAdd<HuffmanTreeInfo>(lista,aux);
      }
   }

   // ordeno la lista
   listSort<HuffmanTreeInfo>(lista,cmpHuffmanTreeInfo);

}
HuffmanTreeInfo* crearArbol(List<HuffmanTreeInfo>& lista)
{
   //inicializo la raiz
   HuffmanTreeInfo* ret;

   unsigned int i = 0;
   while( listSize<HuffmanTreeInfo>(lista)>1 ) //mientras la lista tenga mas de un elemento
   {
      // paso 3.a
      HuffmanTreeInfo* aux1 = new HuffmanTreeInfo;   // creamos los hijos de
      HuffmanTreeInfo* aux2 = new HuffmanTreeInfo;   // derecha e izquierda
      *aux1 = listRemoveFirst<HuffmanTreeInfo>(lista);
      *aux2 = listRemoveFirst<HuffmanTreeInfo>(lista);

      // paso 3.b
      HuffmanTreeInfo add;
      add.c = 256+i;
      add.n = aux1->n+aux2->n;
      add.right = aux1;
      add.left = aux2;

      // paso 3.c
      listOrderedInsert<HuffmanTreeInfo>(lista,add,cmpHuffmanTreeInfo);
      i++;
   }

   // obtengo la raiz del arbol
   listReset<HuffmanTreeInfo>(lista);
   ret = listNext<HuffmanTreeInfo>(lista);

   return ret;
}
void cargarCodigosEnTabla(HuffmanTreeInfo* raiz, HuffmanTable tabla[])
{

   HuffmanTree ht = huffmanTree(raiz);
   while( huffmanTreeHasNext(ht) )
   {
      string cod;
      HuffmanTreeInfo* hoja = huffmanTreeNext(ht,cod);
      tabla[hoja->c].cod = cod;

   }

}
void grabarArchivoComprimido(string fName, HuffmanTable tabla[])
{

   // abro el archivo
   const char * fO = fName.c_str();
   FILE* fOriginal = fopen(fO,"r+b");

   // creo el archivo comprimido vacio
   string fNamePuntoHuff = fName+".huf";
   const char * fC = fNamePuntoHuff.c_str();
   FILE* fComprimido = fopen(fC,"w+b");

   // cuento cuantos caracteres distintos hay y escribo la cantidad
   // en el archivo comprimido con formato de unsigned char
   unsigned int cD = 0;
   for( unsigned int i = 0; i<256; i++ )
   {
      if( tabla[i].n>0 )
      {
         cD++;
      }
   }
   unsigned char tRegistros = cD;
   write<unsigned char>(fComprimido,tRegistros);

   // escribo los t registros
   for( unsigned int i = 0; i<256; i++ )
   {
      if( tabla[i].n>0 )
      {
         // escribo caracter
         string cod = tabla[i].cod;
         unsigned char caracter = i;
         write<unsigned char>(fComprimido,caracter);

         // escribo numero de bits del codigo huffman del caracter
         unsigned char nroBits = length(cod);
         write<unsigned char>(fComprimido,nroBits);

         // escribo bit por bit del codigo huffman del caracter
         for( int f = 0; f<length(cod); f++ )
         {
            unsigned char bit = cod[f];
            write<unsigned char>(fComprimido,bit);
         }
      }
   }
   // escribo el tamanio del archivo original al final de los t registros
   int sFO = fileSize<unsigned char>(fOriginal);
   unsigned int sizeFOriginal = sFO;
   write<unsigned int>(fComprimido,sizeFOriginal);

   // escribo la informacion del archivo original comprimido
   seek<unsigned char>(fOriginal,0);
   BitWriter bw = bitWriter(fComprimido);

   unsigned char c = read<unsigned char>(fOriginal);
   while( !feof(fOriginal) )
   {
      unsigned int pos = c;
      string bitsAEscribir = tabla[pos].cod;
      for( int i = 0; i<length(bitsAEscribir); i++ )
      {
         unsigned char bit = bitsAEscribir[i];
         if( bit==48 )
         {
            bitWriterWrite(bw,0);
         }
         if( bit==49 )
         {
            bitWriterWrite(bw,1);
         }
      }

      c = read<unsigned char>(fOriginal);
   }
   bitWriterFlush(bw);
   fclose(fOriginal);
   fclose(fComprimido);
}
void comprimir(string fName)
{

   // paso 1
   HuffmanTable tabla[256];
   contarOcurrencias(fName,tabla);

   // paso 2
   List<HuffmanTreeInfo> lista = list<HuffmanTreeInfo>();
   crearLista(lista,tabla);

   // paso 3
   HuffmanTreeInfo* raiz = crearArbol(lista);

   // Recorro el arbol para obtener los codigos y los cargo
   // en el array de contadores, en el campo code
   cargarCodigosEnTabla(raiz,tabla);

   // Grabo el archivo comprimido
   grabarArchivoComprimido(fName,tabla);

   cout<<"EL ARCHIVO A SIDO COMPRIMIDO"<<endl;
}
HuffmanTreeInfo* recomponerElArbol(FILE* fComprimido)
{
   HuffmanTreeInfo* raiz = new HuffmanTreeInfo;
   raiz->left = NULL;
   raiz->right = NULL;

   unsigned char nroHojas = read<unsigned char>(fComprimido);
   unsigned int nroHojasInt = nroHojas;

   for( unsigned int i = 0; i<nroHojasInt; i++ )
   {
      unsigned char caracterHoja = read<unsigned char>(fComprimido);

      unsigned char nroBits = read<unsigned char>(fComprimido);
      unsigned int nroBitsHoja = nroBits;
      HuffmanTreeInfo* aux = raiz;
      for( unsigned int f = 0; f<nroBitsHoja; f++ )
      {
         unsigned char bit = read<unsigned char>(fComprimido);
         if( bit==48 )
         {
            if( aux->left==NULL )
            {
               HuffmanTreeInfo* createLeft = new HuffmanTreeInfo;
               createLeft->left = NULL;
               createLeft->right = NULL;
               aux->left = createLeft;
               aux = aux->left;
            }
            else
            {
               aux = aux->left;
            }
         }
         if( bit==49 )
         {
            if( aux->right==NULL )
            {
               HuffmanTreeInfo* createRight = new HuffmanTreeInfo;
               createRight->left = NULL;
               createRight->right = NULL;
               aux->right = createRight;
               aux = aux->right;
            }
            else
            {
               aux = aux->right;
            }
         }

      }
      aux->c = caracterHoja;

   }

   return raiz;
}
void grabarArchivoOriginal(FILE* fComprimido, HuffmanTreeInfo* raiz, string fName)
{
   // creo el archivo original para recomponerlo
   string final = removeAt(fName,length(fName)-1);
   final = removeAt(final,length(final)-1);
   final = removeAt(final,length(final)-1);
   final = removeAt(final,length(final)-1);

   const char * fO = final.c_str();
   FILE* fDescomprimido = fopen(fO,"w+b");

   // leemos el tama�o del archivo original
   unsigned int nroBytes = read<unsigned int>(fComprimido);

   //recomponemos el arhcivo original
   unsigned int i = 0;
   BitReader br = bitReader(fComprimido);
   while (i<nroBytes)
   {

      HuffmanTreeInfo* aux=raiz;
      while(aux->left!=NULL && aux->right!=NULL)
      {
         int bit = bitReaderRead(br);
         if(bit==0)
         {
            aux=aux->left;
         }
         if(bit==1)
         {
            aux=aux->right;
         }
      }
      unsigned char caraterAEscribir = aux->c;
      write<unsigned char>(fDescomprimido,caraterAEscribir);
      i++;
   }

}
void descomprimir(string fName)
{

   // abro el archivo
   const char * fC = fName.c_str();
   FILE* fComprimido = fopen(fC,"r+b");

   // recomponemos el arbol
   HuffmanTreeInfo* raiz = recomponerElArbol(fComprimido);

   // restauramos el archivo original
   grabarArchivoOriginal(fComprimido,raiz,fName);

   cout<<"EL ARCHIVO A SIDO DESCOMPRIMIDO"<<endl;
}

int main()
{

   //recibo el nombre del archivo
   string fName = "prueba.txt.huf";

   //si no termina con ".huf" comprimo
   if( !endsWith(fName,".huf") )
   {
      comprimir(fName);
   }
   else //descomprimo
   {
      descomprimir(fName);
   }

   return 0;
}

#endif

