#ifndef _TARR_BITREADER_
#define _TARR_BITREADER_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "../funciones/strings.hpp"
#include "../funciones/files.hpp"

using namespace std;

struct BitReader
{
   unsigned char a;
   int cont;
   FILE* f;
};

BitReader bitReader(FILE* f)
{
   BitReader br;
   br.a = 0x00;
   br.cont = 8;
   br.f = f;
   br.a = read<unsigned char>(br.f);
   return br;
}

int bitReaderRead(BitReader& br)
{
   int ret;

   if( br.cont==0 )
   {
      br.cont = 8;
      br.a = read<unsigned char>(br.f);
      unsigned char aux = br.a>>(br.cont-1);
      unsigned char aux2 = 0x01;
      aux = aux&aux2;
      if( aux==1 )
      {
         ret = 1;
      }
      else
      {
         ret = 0;
      }
      br.cont--;
   }
   else
   {
      unsigned char aux = br.a>>(br.cont-1);
      unsigned char aux2 = 0x01;
      aux = aux&aux2;
      if( aux==1 )
      {
         ret = 1;
      }
      else
      {
         ret = 0;
      }
      br.cont--;
   }
   return ret;
}

#endif
