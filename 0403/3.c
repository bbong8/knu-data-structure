#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
  if(!((p) = malloc(s))){\
    fprintf(stderr, "Insufficient memory");\
    exit(EXIT_FAILURE);\
  }

typedef struct node{
  int data;
  struct node *link;
} NODE;

NODE* createNode(int data);
void deleteOddNode(NODE **last);
void pushList(NODE **last, NODE *new);
void printList(NODE *last);
void freeList(NODE *last);

int main(){
  FILE *ifp = fopen("input3.txt", "r");
  if(ifp == NULL){
    fprintf(stderr, "File opening error");
    exit(EXIT_FAILURE);
  }

  int data = 0;
  NODE *last = NULL;

  while(fscanf(ifp, "%d", &data) != EOF){
    NODE *new = createNode(data);
    pushList(&last, new);
  }

  printList(last);
  
  deleteOddNode(&last);
  printf("\n\nAfter deleting nodes with odd values\n\n");
  printList(last);

  freeList(last);
  fclose(ifp);
  return 0;
}

NODE* createNode(int data){
  NODE *new;
  MALLOC(new, sizeof(NODE));
  new->data = data;
  new->link = NULL;

  return new;
}

void deleteOddNode(NODE **last){
  NODE *tmp = (*last)->link;
  NODE *trail = *last;
  NODE *end = *last;

  while(tmp != end){
    if(tmp->data % 2 == 1){
      NODE *garbage = tmp;
      (*last)->link = tmp->link;
      tmp = tmp->link;
      free(garbage);
    }
    else{
      *last = tmp;
      tmp = tmp->link;
    }
  }

  if(tmp->data % 2 == 1){
    (*last)->link = tmp->link;
    free(tmp);
  }
  else{
    *last = tmp;
  }
}

void pushList(NODE **last, NODE *new){
  if(*last == NULL){
    new->link = new;
    *last = new;
  }
  else{
    new->link = (*last)->link;
    (*last)->link = new;
    *last = new;
  }
}

void printList(NODE *last){
  NODE *end = last;
  int cnt = 0;
  last = last->link;
  printf("The Circularly Linked List contains:\n");
  while(last != end){
    printf("(%p, %4d, %p)", last, last->data, last->link);
    cnt++;
    if(cnt == 3){
      printf("\n");
      cnt = 0;
    }
    last = last->link;
  }
  printf("(%p, %4d, %p)", last, last->data, last->link);
  cnt++;
  if(cnt != 0 || cnt == 3){
    printf("\n");
  }
}

void freeList(NODE *last){
  NODE *end = last;
  NODE *garbage;
  last = last->link;
  while(last != end){
    garbage = last;
    last = last->link;
    free(garbage);
  }
  free(last);
}