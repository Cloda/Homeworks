#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

uint32_t xorshift32(void);
uint32_t xorshift128(void);

/* Псевдослучайный генератор: */
uint32_t MyRand(void);
/* и его инициализация: */
void MySrand(uint32_t seed);

int main(void) {

  uint32_t x = 1U;

  // srand(time(NULL));
  int sum = 0;
  for(int  i =0; i<1000000000; i++){
    x = xorshift32();
    // fprintf(stdout, "%u ", x % 2);
    sum += x % 2;

  }
  printf("%u \n", sum);

  // printf("\t \t MyRand \n");
  // MySrand((uint32_t)time(NULL));
  // for(int  i =0; i<10; i++){
  //   x = MyRand();
  //   fprintf(stdout, "%u\n", x);
  // }

  // printf("\t \t xorshift32\n");
  // for(int  i =0; i<10; i++){
  //   x = xorshift32();
  //   fprintf(stdout, "%u\n", x);
  // }

  // printf("\t \t xorshift128\n");
  // for(int  i =0; i<10; i++){
  //   x = xorshift128();
  //   fprintf(stdout, "%u\n", x);
  // }

  // printf("\t \t rand\n");
  // srand(time(NULL));
  // for(int  i =0; i<10; i++){
  //   x = rand();
  //   fprintf(stdout, "%u\n", x);
  // }

  // printf("\t \t lrand48\n");
  // srand48(time(NULL));
  // for(int  i =0; i<20; i++){
  //   x = lrand48();
  //   fprintf(stdout, "%u\n", x);
  // }


  return 0;
}

uint32_t next = 1U;
void MySrand(uint32_t seed) {
/* инициализация стартового значения */
  next = seed;
  return;
}
uint32_t MyRand(void) {
/* конгруэнтный линейный генератор Парка-Миллера
   для целых псевдослучайных чисел: */
  uint64_t A = 16807LLU;       // 7^5
  uint64_t M = 2147483647LLU;  // 2^31 - 1
  next = (uint32_t)((A * next) % M);
  return next;
}

uint32_t w = 1U;
uint32_t xorshift32(void){
	uint32_t x = w;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return w = x;
}

uint32_t v = 2U, x = 3U, y = 4U, z = 5U;
uint32_t xorshift128(void){
  uint32_t t = x;
  x = y; y = z; z = v;
  t ^= t << 11U;
  t ^= t >> 8U;
  v ^= v >> 19U;
  v ^= t;
  return v;
}
