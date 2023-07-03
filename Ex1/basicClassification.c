#include <stdio.h>
#include "NumClass.h"


 

int isPrime(int n)
{
   int i;
 
   for ( i = 2 ; i <= n/2 ; i++ )
   { 
      if ( n%i == 0 )
     return 0;
   }
   return 1;
}

int factorial(int n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}


int isStrong(int n) {
   int temp, rem, result = 0;
   temp = n;
   while(temp) {
      rem = temp % 10;
      result = result + factorial(rem);
      temp = temp/10;
   }
   if (result == n)
      return 1;
   else
      return 0;
}

