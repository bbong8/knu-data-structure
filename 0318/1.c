#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MATRIX_ROW 20
#define MATRIX_COL 20

typedef struct{
  int col;
  int row;
  int value;
} term;

void create_matrix(int matrix[MATRIX_ROW][MATRIX_COL], int item);
void create_sparse_matrix(int matrix[MATRIX_ROW][MATRIX_COL], term sparse[MATRIX_COL * MATRIX_COL], int item);
void print_matrix(int matrix[MATRIX_ROW][MATRIX_COL]);
void print_sparse_matrix(term sparse[MATRIX_COL * MATRIX_COL], int item);


int main(){
  int matrix[MATRIX_ROW][MATRIX_COL] = {0};
  int item;
  term sparse[MATRIX_COL * MATRIX_COL] = {0, 0, 0};

  printf("원소의 개수를 쓰시오 .. ");
  scanf("%d", &item);

  srand(time(NULL));

  create_matrix(matrix, item);
  create_sparse_matrix(matrix, sparse, item);
  print_matrix(matrix);
  print_sparse_matrix(sparse, item);

  return 0;
}

void create_matrix(int matrix[MATRIX_ROW][MATRIX_COL], int item){
  int x, y, cnt = 0;
  while (cnt != item){
    x = rand() % MATRIX_COL;
    y = rand() % MATRIX_ROW;

    while(matrix[x][y] == 0){
      matrix[x][y] = rand() % (MATRIX_COL * MATRIX_ROW);
    }
    cnt++;
  }
}
void create_sparse_matrix(int matrix[MATRIX_ROW][MATRIX_COL], term sparse[MATRIX_COL * MATRIX_COL], int item){
  int cnt = 1;
  sparse[0].row = MATRIX_ROW;
  sparse[0].col = MATRIX_COL;
  sparse[0].value = item;

  for(int i = 0; i <= MATRIX_ROW; i++){
    for(int j = 0; j <= MATRIX_COL; j++){
      if(matrix[i][j] != 0){
        sparse[cnt].row = i;
        sparse[cnt].col = j;
        sparse[cnt].value = matrix[i][j];
        cnt++;
      }
    }
  }
}
void print_matrix(int matrix[MATRIX_ROW][MATRIX_COL]){
  printf("Random generated Matrix(%d,%d)\n", MATRIX_ROW, MATRIX_COL);
  for(int i = 0; i < MATRIX_ROW; i++){
    for(int j = 0; j < MATRIX_COL; j++){
      printf("%5d", matrix[i][j]);
    }
    printf("\n");
  }
}
void print_sparse_matrix(term sparse[MATRIX_COL * MATRIX_COL], int item){
  printf("sparse matrix\n");
  for(int i = 0; i < item + 1; i++){
    printf("%5d,%5d,%5d\n", sparse[i].row, sparse[i].col, sparse[i].value);
  }
}