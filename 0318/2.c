#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERM 101
#define MALLOC(p, s) \
  if (!((p) = malloc(s))){\
    fprintf(stderr, "Insufficient memory");\
    exit(EXIT_FAILURE);\
  }

typedef struct{
  int col;
  int row;
  int value;
} term;

void fast_transpose(term a[MAX_TERM], term b[MAX_TERM]);
void print_sparse_matrix(char *name, term a[MAX_TERM]);

int main(){
  int i = 0;
  term a[MAX_TERM] = {0}, b[MAX_TERM] ={0};
  FILE *ifp = fopen("a.txt", "r");
  FILE *ofp = fopen("b.txt", "w");

  if(ifp == NULL || ofp == NULL){
    fprintf(stderr, "File Pointer Error");
    return 0;
  }

  while(!feof(ifp)){
    fscanf(ifp, "%d %d %d", &a[i].row, &a[i].col, &a[i].value);
    i++;
  }

  fast_transpose(a, b);

  for(int i = 0; i < b[0].value + 1; i++){
    fprintf(ofp, "%4d%4d%4d\n", b[i].row, b[i].col, b[i].value);
  }

  print_sparse_matrix("A", a);
  print_sparse_matrix("B", b);

  fclose(ifp);
  fclose(ofp);

  return 0;
}

void fast_transpose(term a[MAX_TERM], term b[MAX_TERM]){
  int *row_terms, *starting_pos, j;
  int num_cols = a[0].col, num_terms = a[0].value;
  MALLOC(row_terms, sizeof(int) * a[0].col);
  MALLOC(starting_pos, sizeof(int) * a[0].col);

  b[0].row = a[0].col;
  b[0].col = a[0].row;
  b[0].value = a[0].value;
  
  for(int i = 0; i < num_cols; i++){
    row_terms[i] = 0;
  }

  for(int i = 1; i <= num_terms; i++){
    row_terms[a[i].col]++;
  }

  starting_pos[0] = 1;

  for(int i = 1; i < num_cols; i++){
    starting_pos[i] = starting_pos[i-1] + row_terms[i-1];
  }

  for(int i = 1; i <= num_terms; i++){
    j = starting_pos[a[i].col]++;
    b[j].row = a[i].col;
    b[j].col = a[i].row;
    b[j].value = a[i].value;
  }

  free(row_terms);
  free(starting_pos);
}

void print_sparse_matrix(char *name, term a[MAX_TERM]){
  printf("%s\n", name);
  int flag = 1, zero = 0;

  for(int i = 0; i < a[0].row; i++){
    for(int j = 0; j < a[0].col; j++){
      if(flag <= a[0].value && a[flag].row == i && a[flag].col == j){
        printf("%4d", a[flag].value);
        flag++;
      }
      else{
        printf("%4d", zero);
      }
    }
    printf("\n");
  }
}