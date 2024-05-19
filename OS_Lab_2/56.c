/*Description: rogram to measure how much time is taken to execute 100 getppid ( )
system call using time stamp counter
*/
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
unsigned long long rdtsc()
{
   unsigned long long dst;
   __asm__ __volatile__("rdtsc"
                        : "=A"(dst));
   return dst;
}
int main()
{
   long long int start, end;

   start = rdtsc();

   for (int i = 0; i < 100; i++)
   {
      getppid();
   }

   end = rdtsc();

   printf(" time taken is : %llu CPU cycles\n", end - start);
}
