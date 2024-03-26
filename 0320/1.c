#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 20

/* Struct Definition */
typedef struct{
  int id;
  char name[MAX_NAME_SIZE];
} element;

/* Global Variable*/
element stack[MAX_STACK_SIZE];
int top = -1;

/* Function Definition */
int isFull();
int isEmpty();
void push(element e);
element pop();
void sprint();
void command_error(FILE *fp);


int main(){
  FILE *fp = fopen("input1.txt", "r");
  char command[100];
  if(fp == NULL){
    fprintf(stderr, "Opening file Error");
    exit(EXIT_FAILURE);
  }

  while(fscanf(fp, "%s", command) != EOF){
    if(!strcmp(command, "push")){
      element e = {0};
      if(fscanf(fp, "%d %s", &e.id, e.name) != 2){ 
        command_error(fp);
        continue;
      }
      push(e);
    }
    else if(!strcmp(command, "pop")){
      pop();
    }
    else if(!strcmp(command, "sprint")){
      printf("\n");
      sprint();
    }
    else if(!strcmp(command, "quit")){
      printf("Quit this process\n");
      return 0;
    }
    else{
      command_error(fp);
    }
  }

  fclose(fp);
  return 0;
}

int isFull(){
  return top == MAX_STACK_SIZE - 1;
}

int isEmpty(){
  return top == -1;
}

void sprint(){
  for(int i = top; i >= 0; i--){
    printf("%d %s\n", stack[i].id, stack[i].name);
  }

  printf("\n");
}

void push(element e){
  if(isFull()){
    printf("\nstack is full, cannot add element\n");
    printf("current stack elements :\n");
    sprint();
    return;
  }

  stack[++top] = e;

}

element pop(){
  element null = {0};
  if(isEmpty()){
    printf("stack is empty, cannot pop element\n");
    return null;
  }

  element e = stack[top];
  stack[top--] = null;

  return e;
}

void command_error(FILE *fp){
  printf("wrong command! try again!\n");
  char temp[1000];
  fgets(temp, 1000, fp);
}