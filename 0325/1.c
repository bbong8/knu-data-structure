#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SIZE 20
#define MALLOC(p, s) \
  if (!((p) = malloc(s * sizeof(element)))){\
    fprintf(stderr, "Insufficient memory");\
    exit(EXIT_FAILURE);\
  }

/* Struct Definition */
typedef struct {
  int id;
  char name[MAX_NAME_SIZE];
} element;

/* Global Variable*/
int capacity = 2;
int front = 0;
int rear = 0;
element *queue;

/* Function Definition */
int isFull();
int isEmpty();
void double_queue();
void add(element e);
element delete();
void qprint();
void command_error(FILE *fp);

int main(){
  FILE *fp = fopen("input1.txt", "r");
  char command[100];

  if(fp == NULL){
    fprintf(stderr, "Opening file Error");
    exit(EXIT_FAILURE);
  }

  MALLOC(queue, capacity);

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
      printf("end of program!!\n");
      return 0;
    }
    else{
      command_error(fp);
    }
  }

  fclose(fp);
  free(queue);
  return 0;
}

int isEmpty(){
  return front == rear;
}

int isFull(){
  return (rear + 1) % capacity == front;
}

void qprint(){
  int i = front + 1;
  while(i != rear + 1){
    printf("%d, %s\n", queue[i].id, queue[i].name);
    i++;
  }
  printf("\n");
}

void double_queue(){
  element *tmp = queue;
  element null = {0};
  capacity *= 2;

  MALLOC(queue, capacity);
  queue[0] = null;
  for(int i = 1; i < (capacity / 2) + 1; i++){
    front = (front + 1) % (capacity / 2);
    queue[i] = tmp[front];
  }

  rear = (capacity / 2) - 1;
  front = 0;

  free(tmp);
}

void add(element e){
  int boolean = 0;
  if(isFull()){
    double_queue();
    printf("queue capacity is doubled\n");
    printf("current queue capacity is %d\n", capacity);
    boolean = 1;
  }

  rear = (rear + 1) % capacity;
  queue[rear] = e;
  if(boolean){
    qprint();
  }
}

element delete(){
  element null = {0};
  element e = {0};
  if(isEmpty()){
    printf("queue is empty\n");
    return null;
  }

  front = (front + 1) % capacity;
  e = queue[front];
  queue[front] = null;
  return e;
}

void command_error(FILE *fp){
  printf("wrong command! try again!\n");
  char temp[1000];
  fgets(temp, 1000, fp);
}