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
void add(NODE **rear, NODE *new, NODE **front);
NODE* delete(NODE **front);

int main(){
  FILE *ifp = fopen("input.txt", "r");
  if(ifp == NULL){
    fprintf(stderr, "File opening error");
    exit(EXIT_FAILURE);
  }

  NODE *front[LECTURE_CNT] = { NULL }, *rear[LECTURE_CNT] = { NULL };
  int lecture_id = 0, class_id = 0, score = 0;

  while(fscanf(ifp, "%d %d %d", &lecture_id, &class_id, &score) != EOF){
    NODE *new = createNode(class_id, score);
    add(&rear[lecture_id], new, &front[lecture_id]);
  }

  printf("과목번호, 학반, 성적\n");

  for(int i = 0; i < 3; i++){
    printf("********************\n");

    while(front[i] != NULL){
      NODE *delete_node = delete(&front[i]);
      printf("\t%d    %d    %d\n", i, delete_node->class_id, delete_node->score);
      free(delete_node);
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

void add(NODE **rear, NODE *new, NODE **front){
  if(*front == NULL){
    *front = new;
    *rear = new;
  }
  else{
    (*rear)->link = new;
    *rear = new;
  }
}

NODE* delete(NODE **front){
  NODE *delete_node;
  if(*front == NULL){
    fprintf(stderr, "Queue is empty");
    exit(EXIT_FAILURE);
  }

  delete_node = *front;
  *front = (*front) -> link;
  
  return delete_node;
}