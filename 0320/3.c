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
int front = 0;
int rear = 0;

/* Function Definition */
int isFull();
int isEmpty();
void add(element e);
element delete();
void qprint();
void command_error(FILE *fp);

int main(){
  FILE *fp = fopen("input3.txt", "r");
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
  return (rear + 1) % MAX_QUEUE_SIZE == front;
}

void qprint(){
  int i = front;
  while (i != rear) {
    i = (i + 1) % MAX_QUEUE_SIZE;
    printf("%d %s\n", queue[i].id, queue[i].name);
  }
  printf("\n");
}

void add(element e){
  if(isFull()){
    printf("queue is full, not added\n");
    return;
  }

  rear = (rear + 1) % MAX_QUEUE_SIZE;
  queue[rear] = e;
}

element delete(){
  element null = {0};
  if(isEmpty()){
    printf("queue is empty\n");
    return null;
  }

  front = (front + 1) % MAX_QUEUE_SIZE;
  return queue[front];
}

void command_error(FILE *fp){
  printf("wrong command! try again!\n");
  char temp[1000];
  fgets(temp, 1000, fp);
}