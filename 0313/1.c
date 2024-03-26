#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
  if (!((p) = malloc(s * sizeof(int)))){\
    fprintf(stderr, "Insufficient memory");\
    exit(EXIT_FAILURE);\
  }

int* make1dArray(int num){
  int *p;
  MALLOC(p, num);

  for (int i = 0; i < num; i++){
    *(p + i) = rand() % 100;
  }

  return p;
}

int main(){
  int *ipp;
  int i, num;

  printf("일차원 배열의 수를 입력하세요: ");
  scanf("%d", &num);

  ipp = make1dArray(num);
  for (i = 0; i < num; i++) {
    printf("ipp[%2d] =%2d ", i, ipp[i]);
    if ((i % 5) == 4)
      printf("\n");
  }
  
  return 0;
}