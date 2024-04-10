#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
  if(!((p) = malloc(s))){\
    fprintf(stderr, "Insufficient memory");\
    exit(EXIT_FAILURE);\
  }

typedef struct poly_node{
  int coeff;
  int exp;
  struct poly_node *link;
}NODE;

NODE* createNode(int coeff, int exp);
void insertHead(NODE **head, NODE **rear, NODE *new);
void insertTail(NODE **head, NODE **rear, NODE *new);
void polyAdd(NODE **head1, NODE **head2, NODE **head3, NODE **rear3);
void polyPrint(NODE *head, char expression[]);
void freeList(NODE *head);

int main(){
  FILE *ifp[2] = {fopen("a.txt", "r"), fopen("b.txt", "r")};
  if(ifp[0] == NULL || ifp[1] == NULL){
    fprintf(stderr, "File opening error");
    exit(EXIT_FAILURE);
  }

  NODE *head[3] = {NULL};
  NODE *rear[3] = {NULL};
  int coeff, exp;
  char sort_type;

  for(int i = 0; i < 2; i++){
    fscanf(ifp[i], "%c", &sort_type);

    while(fscanf(ifp[i], "%d %d", &coeff, &exp) != EOF){
      NODE *new = createNode(coeff, exp);
      
      if(sort_type == 'a'){
        insertHead(&head[i], &rear[i], new);
      }
      else if(sort_type == 'd'){
        insertTail(&head[i], &rear[i], new);
      }
      else{
        fprintf(stderr, "sort type error");
        exit(EXIT_FAILURE);
      }
    }
    char *expression = (i) ? "b" : "a";
    polyPrint(head[i], expression);
  }

  polyAdd(&head[0], &head[1], &head[2], &rear[2]);
  polyPrint(head[2], "a+b=c");

  for(int i = 0; i < 3; i++){
    freeList(head[i]);
  }

  return 0;
}

NODE* createNode(int coeff, int exp){
  NODE *new;
  MALLOC(new, sizeof(NODE));
  new->coeff = coeff;
  new->exp = exp;
  new->link = NULL;
  return new;
}

void insertHead(NODE **head, NODE **rear, NODE *new){
  if(*head == NULL){
    *head = new;
    *rear = new;
    return;
  }
  
  new->link = *head;
  *head = new;
}

void insertTail(NODE **head, NODE **rear, NODE *new){
  if(*head == NULL){
    *head = new;
    *rear = new;
    return;
  }

  (*rear)->link = new;
  *rear = new;
}

void polyPrint(NODE *head, char expression[]){
  printf("%8s:\n", expression);
  while(head != NULL){
    printf("(%010X :%+4dx^%d: %010X)\n", head, head->coeff, head->exp, head->link);
    head = head->link;
  }
  printf("\n");
}

void freeList(NODE *head){
  NODE *garbage;
  while(head != NULL){
    garbage = head;
    head = head->link;
    free(garbage);
  }
}

void polyAdd(NODE **head1, NODE **head2, NODE **head3, NODE **rear3) {
  NODE *poly1 = *head1, *poly2 = *head2;

  while(poly1 != NULL && poly2 != NULL){
    if(poly1->exp > poly2->exp){
      insertTail(head3, rear3, createNode(poly1->coeff, poly1->exp));
      poly1 = poly1->link;
    }
    else if(poly1->exp < poly2->exp){
      insertTail(head3, rear3, createNode(poly2->coeff, poly2->exp));
      poly2 = poly2->link;
    }
    else{
      int sum_coeff = poly1->coeff + poly2->coeff;
      insertTail(head3, rear3, createNode(sum_coeff, poly1->exp));
      poly1 = poly1->link;
      poly2 = poly2->link;
    }
  }

  while(poly1 != NULL){
    insertTail(head3, rear3, poly1);
    poly1 = poly1->link;
  }

  while(poly2 != NULL){
    insertTail(head3, rear3, poly2);
    poly2 = poly2->link;
  }
}

