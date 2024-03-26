#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 101
#define FALSE 0
#define TRUE 1
#define MAX_ROW 100
#define MAX_COL 100

/* Struct Definition */
typedef struct{
  short int row;
  short int col;
  short int dir;
} element;

typedef struct{
  short int vert;
  short int horiz;
} offsets;

/* Global Variable*/
offsets move[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
element stack[MAX_STACK_SIZE];
int top = -1;
int maze[MAX_ROW][MAX_COL] = { 0 };
int mark[MAX_ROW][MAX_COL] = { 0 };

/* Function Definition */
void path(int row, int col);
void push(element e);
element pop();
void stack_full();
void stack_empty();


int main(void){
  int row, col, data;
  FILE *fp = fopen("input2.txt", "r");

  if(fp == NULL){
    fprintf(stderr, "Opening file Error");
    exit(EXIT_FAILURE);
  }

  fscanf(fp, "%d %d", &row, &col);

  for(int i = 0; i < row + 2; i++){
    for(int j = 0; j < col + 2; j++){
      if(i == 0 || i == row + 1 || j == 0 || j == col + 1){
        maze[i][j] = 1;
      }
      else{
        fscanf(fp, "%d", &data);
        maze[i][j] = data;
      }
    }
  }

  path(row, col);
  fclose(fp);
}

void path(int exit_row, int exit_col){
  int i, row = 0, col = 0, next_row, next_col, dir, founded = FALSE;
  element position;
  
  mark[1][1] = 1;
  top = 0;
  stack[top].row = 1; stack[top].col = 1; stack[top].dir = 0;
  while(top > -1 && !founded){ 
    position = pop();
    row = position.row; col = position.col;
    dir = position.dir;
    while(dir < 8 && !founded){
      next_row = row + move[dir].vert;
      next_col = col + move[dir].horiz;

      if(next_row == exit_row && next_col == exit_col){
        founded = TRUE;
      }
      else if(!maze[next_row][next_col] && !mark[next_row][next_col]){
        mark[next_row][next_col] = 1;
        position.row = row; position.col = col;
        position.dir = ++dir;
        push(position);
        row = next_row; col = next_col; dir = 0;
      }
      else{
        dir++;
      }
    }
  }

  if(founded){
    printf("The path is:\n");
    printf("row\tcol\n");
    for(i = 0; i <= top; i++){
      printf("%2d\t%2d\n", stack[i].row, stack[i].col);
    }
    printf("%2d\t%2d\n", row, col);
    printf("%2d\t%2d\n", exit_row, exit_col);
  }
  else{
    printf("The maze does not have a path\n");
  }
}

void push(element e){
  if(top >= MAX_STACK_SIZE - 1){
    stack_full();
  }
  stack[++top] = e;
}

element pop(){
  if(top == -1){
    stack_empty();
  }
  return stack[top--];
}

void stack_full(){
  fprintf(stderr, "Stack is full, cannot add element");
  exit(0);
}

void stack_empty(){
  fprintf(stderr, "Stack is empty, cannot delete element");
  exit(0);
}