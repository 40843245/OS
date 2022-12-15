#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>

int turn;
int flag[2];

void die(const char* fmt,...)
{
 printf("The die func was called.\n");
 va_list ap;
 va_start(ap,fmt);
 vfprintf(stderr,fmt,ap);
 va_end(ap);
 if(fmt[0]&& fmt[strlen(fmt)-1]==':')
 {
   fputc(' ',stderr);
   perror(NULL);
 }else
 {
   fputc('\n',stderr);
 }
 exit(1);
}

void*f0(void* arg)
{
  printf("The func f0 was called.");
  while(1)
  {
   flag[0]=1;
   turn=1;
   while(flag[1] && turn==1)
   ;//NOTHING
   puts("hello");
   flag[0]=0;
   sleep(1);

  }
}
void*f1(void* arg)
{
 printf("The func f1 was called.");
 while(1)
 {
   flag[1]=1;
   turn=0;
   while(flag[0] && turn==0)
   ;//NOTHING
   puts("world");
   flag[1]=0;
   sleep(1);

 }
}
int main()
{
  pthread_t t0,t1;
  if(pthread_create(&t0, NULL,f0,NULL))
  {
    die("unable to create thread t0.");
  }
  if(pthread_create(&t1, NULL,f1,NULL))
  {
    die("unable to create thread t1.");
  }

  printf("The func f0 and f1 was NOT die.\n");
  while(1)
  ;//NOTHING

  printf("The program will normally exit!!!\n");
  printf("Bye Bye!!!");

  return 0;
}
