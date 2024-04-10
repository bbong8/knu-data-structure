#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
  if (!((p) = malloc(s))){\
    fprintf(stderr, "Insufficient memory");\
    exit(EXIT_FAILURE);\
  }
#define LECTURE_CNT 3

typedef struct node{
  int class_id;
  int score;
  struct node *link;
} NODE;

NODE* createNode(int class_id, int score);
void push(NODE **top, NODE *new);
NODE* pop(NODE **top);

int main(){
  FILE *ifp = fopen("input.txt", "r");
  if(ifp == NULL){
    fprintf(stderr, "File opening error");
    exit(EXIT_FAILURE);
  }

  NODE *top[LECTURE_CNT] = { NULL };
  int lecture_id = 0, class_id = 0, score = 0;
  while(fscanf(ifp, "%d %d %d", &lecture_id, &class_id, &score) != EOF){
    NODE *new = createNode(class_id, score);
    push(&top[lecture_id], new);
  }

  printf("과목번호, 학반, 성적\n");

  for(int i = 0; i < 3; i++){
    printf("********************\n");
    while(top[i] != NULL){
      NODE *pop_node = pop(&top[i]);
      printf("\t%d    %d    %d\n", i, pop_node->class_id, pop_node->score);
      free(pop_node);
    }
  }

  fclose(ifp);
  return 0;
}

NODE* createNode(int class_id, int score){
  NODE *new;
  MALLOC(new, sizeof(NODE));
  new->class_id = class_id;
  new->score = score;
  new->link = NULL;

  return new;
}

void push(NODE **top, NODE *new){
  if(*top == NULL){
    *top = new;
  }
  else{
    new->link = *top;
    *top = new;
  }
}

NODE* pop(NODE **top){
  NODE *pop_node;
  if(*top == NULL){
    fprintf(stderr, "Stack is empty");
    exit(EXIT_FAILURE);
  }
  pop_node = *top;
  *top = (*top)->link;
  
  return pop_node;
}