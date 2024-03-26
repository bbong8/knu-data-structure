#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20

/* Struct Definition */
typedef struct {
  int id;
  char name[MAX_NAME_SIZE];
} element;

/* Global Variable*/
element queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

/* Function Definition */
int isFull();
int isEmpty();
void add(element e);
element delete();
void qprint();
void data_shift();
void command_error(FILE *fp);



int main(){
  FILE *fp = fopen("input2.txt", "r");
  char command[100];
  if(fp == NULL){
    fprintf(stderr, "Opening file Error");
    exit(EXIT_FAILURE);
  }

  while(fscanf(fp, "%s", command) != EOF){
    if(!strcmp(command, "add")){
      element e = {0};
      if(fscanf(fp, "%d %s", &e.id, e.name) != 2){
        command_error(fp);
        continue;
      }

      add(e);
    }
    else if(!strcmp(command, "delete")){
      delete();
    }
    else if(!strcmp(command, "qprint")){
      qprint();
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

int isEmpty(){
  return front == rear;
}

int isFull(){
  return rear == MAX_QUEUE_SIZE - 1;
}

void data_shift(){
  element null = {0};
  printf("\ndata shift\n");
  for(int i = front + 1; i <= rear; i++){
    queue[i - (front + 1)] = queue[i];
    queue[i] = null;
  }

  rear -= front + 1;
  front = -1;
}

void qprint(){
  for(int i = front + 1; i <= rear; i++){
    printf("%d %s\n", queue[i].id, queue[i].name);
  }
  printf("\n");
}

void add(element e){
  if(front != -1){
    data_shift();
  }

  if(isFull()){
    printf("queue is full, not added\n");
    return;
  }

  queue[++rear ] = e;
}

element delete(){
  element null = {0};
  if(isEmpty()){
    printf("queue is empty, cannot delete element\n");
    return null;
  }

  element e;
  e = queue[++front];
  queue[front] = null;

  return e;
}

void command_error(FILE *fp){
  printf("wrong command! try again!\n");
  char temp[1000];
  fgets(temp, 1000, fp);
}