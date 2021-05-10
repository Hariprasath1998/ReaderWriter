#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int MYFILE = 100;

int mutexS = 1, writeS = 1; 

void wait( S)
{  
while( S <= 0) ;  
S--;  
}  
    
void signal( S)  
{  
S++;  
}  

void *readProcess(){
  static int readcount = 0;
  readcount ++;
  if (readcount == 1)  
  {  
    wait (writeS);  
  }  
  signal(mutexS);
  printf("File Value: %d\n",MYFILE);

  wait(mutexS);  
  readcount --;
  if (readcount == 0)  
  {  
    signal (writeS);  
  }  
  signal(mutexS);
  return NULL;
}

void *writeProcess(){
  wait(writeS);  
  MYFILE += 10;
  printf("After write operation: %d\n", MYFILE);
  signal(writeS);
  return NULL;
}



int main(void)
{
  int num = 10;
  
  pthread_t threadN[10];

  for(int i = 0;i < num; i++){
    printf("Thread Number: %d\n", i);
    if (i % 2 == 0){
      pthread_create( &threadN[i], NULL, *readProcess, NULL);
    }else{
      pthread_create( &threadN[i], NULL, *writeProcess, NULL);
    }
  }
  for (int i=0; i < num; i++){
    pthread_join(threadN[i], NULL);
  }


  return 0;
}