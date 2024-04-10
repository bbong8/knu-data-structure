#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
  if(!((p) = malloc(sizeof(s)))){\
    fprintf(stderr, "Insufficient memory");\
    exit(EXIT_FAILURE);\
  }

typedef struct node{
  int coeff;
  int exp;
  struct node *link;
}NODE;

NODE* avail = NULL;

NODE* getNode();
void retNode(NODE *return_node);
void insertHead(NODE **last, NODE *new);
void insertTail(NODE **last, NODE *new);
void addPoly(NODE *poly1_last, NODE *poly2_last, NODE **poly3_last);
void printPoly(NODE *last, char *expression);
void retPoly(NODE *last);
void printList();
void freeList();

int main(){
  FILE *ifp[2] = {fopen("a.txt", "r"), fopen("b.txt", "r")};
  if(ifp[0] == NULL || ifp[1] == NULL){
    fprintf(stderr, "File opening error");
    exit(EXIT_FAILURE);
  }
  
  NODE *poly_last[3] = {NULL};
  for(int i = 0; i < 3; i++){
    MALLOC(poly_last[i], sizeof(NODE));
    poly_last[i]->exp = -1;
    poly_last[i]->link = poly_last[i];
  }

  char sort_type;
  int coeff, exp;

  for(int i = 0; i < 2; i++){
    fscanf(ifp[i], "%c", &sort_type);

    if(sort_type == 'a'){
      while(fscanf(ifp[i], "%d %d", &coeff, &exp) != EOF){
        NODE *new = getNode();
        new->coeff = coeff;
        new->exp = exp;

        insertHead(&poly_last[i], new);
      }
    }
    else if(sort_type == 'd'){
       while(fscanf(ifp[i], "%d %d", &coeff, &exp) != EOF){
        NODE *new = getNode();
        new->coeff = coeff;
        new->exp = exp;

        insertTail(&poly_last[i], new);
      }
    }
    else{
      fprintf(stderr, "Sorting type error");
      exit(EXIT_FAILURE);
    }
    fclose(ifp[i]);

    char *expression = (i) ? "b" : "a";
    printPoly(poly_last[i], expression);
  }

  addPoly(poly_last[0], poly_last[1], &poly_last[2]);
  printPoly(poly_last[2], "a+b=c");

  for(int i = 0; i < 3; i++){
    retPoly(poly_last[i]);
  }

  printList();
  freeList();

  return 0;

}
  
NODE* getNode(){
  NODE *new;
  if(avail != NULL){
    new = avail;
    avail = avail->link;
  }
  else{
    MALLOC(new, sizeof(NODE))
  }

  return new;
}

void retNode(NODE *return_node){
  return_node->link = avail;
  avail = return_node;
}

void insertHead(NODE **last, NODE *new){
  NODE *id_node = (*last)->link;

  new->link = id_node->link;
  id_node->link = new;
  if((*last)->exp == -1){
    (*last) = new;
  }
}

void insertTail(NODE **last, NODE *new){
  NODE *id_node = (*last)->link;
  (*last)->link = new;
  new->link = id_node;
  (*last) = new;
}

void addPoly(NODE *poly1, NODE *poly2, NODE **poly3){
  poly1 = poly1->link->link;
  poly2 = poly2->link->link;

  while(poly1->exp != -1 && poly2->exp != -1){
    NODE *new = getNode();
    if(poly1->exp > poly2->exp){
      new->exp = poly1->exp;
      new->coeff = poly1->coeff;
      poly1 = poly1->link;
    }
    else if(poly1->exp < poly2->exp){
      new->exp = poly2->exp;
      new->coeff = poly2->coeff;
      poly2 = poly2->link;
    }
    else{
      new->exp = poly1->exp;
      new->coeff = poly1->coeff + poly2->coeff;
      poly1 = poly1->link;
      poly2 = poly2->link;
    }
    if(new->coeff == 0){
      free(new);
      continue;
    }
    insertTail(poly3, new);
  }

  while(poly1->exp != -1){
    NODE *new = getNode();
    new->exp = poly1->exp;
    new->coeff = poly1->coeff;
    poly1 = poly1->link;
  }

  while(poly2->exp != -1){
    NODE *new = getNode();
    new->exp = poly2->exp;
    new->coeff = poly2->coeff;
    poly2 = poly2->link;
  }
}

void printPoly(NODE *last, char expression[]){
  NODE *tmp = last->link;
  printf("%8s:\n", expression);

  do{
    printf("(%p :%+8dx^%d: %p)\n", tmp, tmp->coeff, tmp->exp, tmp->link);
    tmp = tmp->link;
  } while(tmp->exp != -1);

  printf("\n");
}

void retPoly(NODE *last){
  NODE *id_node = last->link;
  NODE *first_node = id_node->link;
  id_node->link = avail;
  avail = first_node;
}

void printList(){
  printf("%8s:\n", "avail");

  while(avail != NULL){
    printf("(%p :%+8dx^%d: %p)\n", avail, avail->coeff, avail->exp, avail->link);
    avail = avail->link;
  }
}

void freeList(){
  NODE *garbage;
  while(avail != NULL){
    garbage = avail;
    avail = avail->link;
    free(garbage);
  }
}