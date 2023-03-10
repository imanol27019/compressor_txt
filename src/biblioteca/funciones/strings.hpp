#ifndef _TSTRINGS_T_
#define _TSTRINGS_T_

#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

int length(string s)
{
   int i = 0;
   while( s[i]!='\0' )
   {
      i++;
   }
   return i;
}

int charCount(string s, char c)
{
   int i,cont = 0;
   for( i = 0; length(s)>=i; i++ )
   {
      if( s[i]==c )
      {
         cont++;
      }
   }
   return cont;
}

string substring(string s, int d, int h)
{
   string subCadena;
   int i;
   for( i = 0; i<=length(s); i++ )
   {
      if( i>=d and i<h )
      {

         subCadena = subCadena+s[i];
      }
   }
   return subCadena;
}

string substring(string s, int d) // ok
{
   string subCadena;
   int i;
   for( i = 0; i<=(length(s)-1); i++ )
   {
      if( i>=d )
      {
         subCadena = subCadena+s[i];
      }
   }
   return subCadena;
}

int indexOf(string s, char c) // ok
{
   int i = 0,posicion;
   while( i<length(s) and s[i]!=c )
   {

      i++;
   }
   if( s[i]==c )
   {
      posicion = i;
   }
   else
   {
      posicion = -1;
   }
   return posicion;
}

int indexOf(string s, char c, int offSet) // ok
{
   int posicion;
   while( offSet<length(s) and s[offSet]!=c )
   {

      offSet++;
   }
   if( s[offSet]==c )
   {
      posicion = offSet;
   }
   else
   {
      posicion = -1;
   }
   return posicion;
}

int indexOf(string s, string toSearch) // ok
{
   int i = 0,posicion;
   while( i<length(s) and s[i]!=toSearch[0] )
   {

      i++;
   }
   if( s[i]==toSearch[0] )
   {
      posicion = i;
   }
   else
   {
      posicion = -1;
   }
   return posicion;
}

int indexOf(string s, string toSearch, int offset) // ok
{
   int posicion;
   while( offset<length(s) and s[offset]!=toSearch[0] )
   {

      offset++;
   }
   if( s[offset]==toSearch[0] )
   {
      posicion = offset;
   }
   else
   {
      posicion = -1;
   }
   return posicion;
}

int lastIndexOf(string s, char c)
{
   int i,posicion = -1;
   for( i = 0; i<=length(s); i++ )
   {
      if( s[i]==c )
      {
         posicion = i;
      }
   }
   return posicion;
}

int indexOfN(string s, char c, int n)
{
   int i = 0,ocurrencias = 0,posicion = 0;
   bool stop = false;
   if( n==0 )
   {
      posicion = -1;
   }
   else
   {
      while( i<=length(s) and stop==false )
      {
         if( s[i]==c )
         {
            ocurrencias++;
            if( ocurrencias==n )
            {
               stop = true;
               posicion = i;
            }
         }
         i++;
      }

   }
   if( ocurrencias<n )
   {
      posicion = length(s);
   }
   return posicion;

}

int charToInt(char c)
{
   int a;
   if( c>=48 and c<=57 )
   {
      a = c-48;
   }
   if( c>=65 and c<=90 )
   {
      a = c-55;
   }
   if( c>=97 and c<=122 )
   {
      a = c-87;
   }

   return a;
}

char intToChar(int i)
{
   int a;
   char b;
   if( 0<=i and i<=9 )
   {
      a = i+48;
      b = a;
   }
   if( 10<=i and i<=35 )
   {
      a = i+55;
      b = a;
   }
   return b;
}

int getDigit(int n, int i)
{
   while( i>0 )
   {
      n = n/10;
      i--;
   }
   return n%10;
}

int digitCount(int n)
{
   int cont = 0;
   if( n==0 )
   {
      cont = 1;
   }
   while( n!=0 )
   {
      n = n/10;
      cont++;
   }

   return cont;
}

string intToString(int i)
{
   string a;  //string que retorna
   int cont;     //contador
   for( cont = digitCount(i); cont>0; cont-- )
   {
      int m = getDigit(i,cont-1);
      char letra = intToChar(m);
      a = a+letra;
   }
   return a;
}

int stringToInt(string s, int b) // ok
{
   int c,valorTotal = 0,posicionBase = 0;
   for( c = length(s)-1; 0<=c; c-- )
   {
      int i,aux = 1;
      for( i = 0; i<posicionBase; i++ )
      {
         aux = aux*b;
      }
      char u = s[c];
      valorTotal = valorTotal+(charToInt(u)*(aux));
      posicionBase++;
   }
   return valorTotal;
}

int stringToInt(string s) // ok
{
   int c,valorTotal = 0,posicionBase = 0;
   for( c = length(s)-1; 0<=c; c-- )
   {
      int i,aux = 1;
      for( i = 0; i<posicionBase; i++ )
      {
         aux = aux*10;
      }
      char u = s[c];
      valorTotal = valorTotal+(charToInt(u)*(aux));
      posicionBase++;
   }
   return valorTotal;
}

string charToString(char c)
{
   string a;
   return a = a+c;
}

char stringToChar(string s)
{
   char a = s[0];
   return a;
}

string stringToString(string s)
{
   return s;
}

string doubleToString(double d)
{
   return "";
}

double stringToDouble(string s)
{
   return 1.1;
}

bool isEmpty(string s)
{
   bool aRetornar = false;
   if( length(s)==0 )
   {
      aRetornar = true;
   }
   return aRetornar;
}

bool startsWith(string s, string x)
{
   int i;
   bool aRetornar = true;
   if( length(s)>=length(x) )
   {
      for( i = 0; i<length(s) and i<length(x); i++ )
      {
         if( s[i]!=x[i] )
         {
            aRetornar = false;
         }
      }
   }
   else
   {
      aRetornar = false;
   }
   return aRetornar;
}

bool endsWith(string s, string x)
{
   int i,b;
   bool aRetornar = true;
   if( length(s)>=length(x) )
   {
      for( i = length(s), b = length(x); b>=0; i--, b-- )
      {
         if( s[i]!=x[b] )
         {
            aRetornar = false;
         }
      }
   }
   else
   {
      aRetornar = false;
   }
   return aRetornar;
}

bool contains(string s, char c)
{
   int i;
   bool aRetornar = false;
   for( i = 0; i<length(s) and aRetornar==false; i++ )
   {
      char aux = s[i];
      if( aux==c )
      {
         aRetornar = true;
      }
   }
   return aRetornar;
}

string replace(string s, char oldChar, char newChar)
{
   int i;
   for( i = 0; i<length(s); i++ )
   {
      if( s[i]==oldChar )
      {
         s[i] = newChar;
      }
   }
   return s;
}

string insertAt(string s, int pos, char c)
{
   string aRetornar = substring(s,0,pos)+c+substring(s,pos);

   return aRetornar;
}

string removeAt(string s, int pos)
{
   string aRetornar = substring(s,0,pos)+substring(s,pos+1);
   return aRetornar;
}

string ltrim(string s)
{
   int i = 0;
   while( s[i]==32 )
   {
      s = removeAt(s,i);
   }
   return s;
}

string rtrim(string s)
{
   while( s[length(s)-1]==32 )
   {
      s = removeAt(s,length(s)-1);
   }
   return s;
}

string trim(string s)
{
   int i = 0;
   while( s[i]==32 )
   {
      s = removeAt(s,i);
   }
   while( s[length(s)-1]==32 )
   {
      s = removeAt(s,length(s)-1);
   }

   return s;
}

string replicate(char c, int n)
{
   int i;
   string aRetornar;
   for( i = 0; i<n; i++ )
   {
      aRetornar = aRetornar+c;
   }
   return aRetornar;
}

string spaces(int n)
{
   int i;
   string aRetornar;
   for( i = 0; i<n; i++ )
   {
      aRetornar = aRetornar+" ";
   }
   return aRetornar;
}

string lpad(string s, int n, char c)
{
   string aRetornar = s;
   int dif;
   for( dif = n-(length(s)); dif>0; dif-- )
   {
      aRetornar = c+aRetornar;
   }
   return aRetornar;
}

string rpad(string s, int n, char c)
{
   int i;
   string aRetornar = s;
   for( i = 0; i<(n-length(s)); i++ )
   {
      aRetornar = aRetornar+c;
   }

   return aRetornar;
}

string cpad(string s, int n, char c)
{
  string aRetornar = s;
   int i;
   int dist1,dist2;
   if( (n-length(s))%2==0 )
   {
      dist1 = ((n-length(s))/2);
      dist2 = ((n-length(s))/2);
   }
   else
   {
      dist1 = ((n-length(s))/2);
      dist2 = ((n-length(s))/2)+1;
   }
   for( i = 0; i<dist1; i++ )
   {
      aRetornar = aRetornar+c;
   }
   for( i = 0; dist2>i; i++ )
   {
      aRetornar = c+aRetornar;
   }
   return aRetornar;
}

bool isDigit(char c)
{
   bool aRetornar = false;
   if( (int)c>=48 and (int)c<=57 )
   {
      aRetornar = true;
   }
   return aRetornar;
}

bool isLetter(char c)
{
   bool aRetornar = false;
   if( ((int)c>=65 and (int)c<=90) or ((int)c>=97 and (int)c<=122) )
   {
      aRetornar = true;
   }
   return aRetornar;
}

bool isUpperCase(char c)
{
   bool aRetornar = false;
   if( (int)c>=65 and (int)c<=90 )
   {
      aRetornar = true;
   }
   return aRetornar;
}

bool isLowerCase(char c)
{
   bool aRetornar = false;
   if( (int)c>=97 and (int)c<=122 )
   {
      aRetornar = true;
   }
   return aRetornar;
}

char toUpperCase(char c)
{
   char aRetornar = c;
   if( c>=97 and c<=122 )
   {
      aRetornar = (int)aRetornar-32;
   }
   return aRetornar;
}

char toLowerCase(char c)
{
   char aRetornar = c;
   if( c>=65 and c<=90 )
   {
      aRetornar = (int)aRetornar+32;
   }
   return aRetornar;
}

string toUpperCase(string s)
{
   int i;
   string aRetornar;
   for( i = 0; i<length(s); i++ )
   {
      char aux = s[i];
      aRetornar = aRetornar+toUpperCase(aux);
   }
   return aRetornar;
}

string toLowerCase(string s)
{
   int i;
   string aRetornar;
   for( i = 0; i<length(s); i++ )
   {
      char aux = s[i];
      aRetornar = aRetornar+toLowerCase(aux);
   }
   return aRetornar;
}

int cmpString(string a, string b)
{
   return a>b?1:a<b?-1:0;
}

int cmpDouble(double a, double b)
{
   return a>b?1:a<b?-1:0;
}

#endif
