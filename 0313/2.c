#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
  if (!((p) = malloc(s * sizeof(int)))){\
    fprintf(stderr, "Insufficient memory");\
    exit(EXIT_FAILURE);\
  }\

int** make2dArray(int rows, int cols){
  int **pp;
  MALLOC(pp, rows);
  for(int i = 0; i < rows; i++){
    MALLOC(pp[i], cols);
    for(int j = 0; j < cols; j++){
      pp[i][j] = rand() % 100;
    }
  }

  return pp;
}

int main(){
  int **ipp;
  int i, j, rows, cols;

  printf("이차원 배열의 행과 열의 수를 입력 하세요 : ");
  scanf("%d %d", &rows, &cols);
  ipp = make2dArray(rows, cols);

  for(i = 0; i < rows; i++){
    for(j = 0; j < cols; j++){
      printf("ipp[%d][%d] =%2d ", i, j, ipp[i][j]);
    }
    printf("\n");
  }

  return 0;
}