#ifndef _TARR_BITWRITER_
#define _TARR_BITWRITER_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "../funciones/strings.hpp"
#include "../funciones/files.hpp"

using namespace std;

struct BitWriter
{
   unsigned char a;
   int cont;
   FILE* f;
};

BitWriter bitWriter(FILE* f)
{
   BitWriter bw;
   bw.a = 0x00;
   bw.cont = 0;
   bw.f = f;
   return bw;
}

void bitWriterWrite(BitWriter& bw, int bit)
{
   if( bw.cont<8 )
   {
      if( bit==1 )
      {
         bw.a = bw.a<<1;
         unsigned char aux = 0x01;
         bw.a = bw.a|aux;
         bw.cont++;
      }
      if( bit==0 )
      {
         bw.a = bw.a<<1;
         bw.cont++;
      }
   }
   else
   {
      write<unsigned char>(bw.f,bw.a);
      bw.cont = 0;
      bw.a = 0x00;
      if( bit==1 )
      {
         bw.a = bw.a<<1;
         unsigned char aux = 0x01;
         bw.a = bw.a|aux;
         bw.cont++;
      }
      if( bit==0 )
      {
         bw.a = bw.a<<1;
         bw.cont++;
      }
   }
}

void bitWriterWrite(BitWriter& bw, string sbit)
{
}

void bitWriterFlush(BitWriter& bw)
{
   if( bw.cont<8  )
   {
      int aux = 8-bw.cont;
      bw.a = bw.a<<aux;
      write<unsigned char>(bw.f,bw.a);
   }
   else
   {
      write<unsigned char>(bw.f,bw.a);
   }
}

#endif
