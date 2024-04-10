#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
  if (!((p) = malloc(s))){\
    fprintf(stderr, "Insufficient memory");\
    exit(EXIT_FAILURE);\
  }

typedef struct node{
  int data;
  struct node *link;
} NODE;

NODE* create_node(int data);
NODE* insert_node(NODE *head, int num);
NODE* delete_odd_data_node(NODE *head);
void print_list(NODE *head);
void free_list(NODE *head);

int main(){
  FILE *ifp = fopen("input1.txt", "r");
  if(ifp == NULL){
    fprintf(stderr, "File opening error");
    exit(EXIT_FAILURE);
  }

  NODE *head = NULL;
  int num;

  while(fscanf(ifp, "%d", &num) != EOF){
    head = insert_node(head, num);
  }

  print_list(head);

  head = delete_odd_data_node(head);
  print_list(head);

  free_list(head);
  fclose(ifp);

  return 0;
}

NODE *create_node(int data){
  NODE *new_node;
  MALLOC(new_node, sizeof(NODE));
  new_node->data = data;
  new_node->link = NULL;

  return new_node;
}

NODE *insert_node(NODE *head, int num){
  NODE *new = create_node(num);
  if(head == NULL){
    return new;
  }
  if(head->data >= num){
    new->link = head;
    return new;
  }
  
  NODE *trail = NULL;
  NODE *tmp = head;
  while(tmp != NULL && tmp->data <= num){
    trail = tmp;
    tmp = tmp->link;
  }
  trail->link = new;
  new->link = tmp;

  return head;
}

NODE *delete_odd_data_node(NODE *head){
  NODE *tmp = head;
  NODE *trail = NULL;
  NODE *delete = NULL;

  while(tmp != NULL){
    if(tmp -> data % 2 == 1){
      if(trail == NULL){
        head = tmp->link;
      }
      else{
        trail->link = tmp->link;
      }
      delete = tmp;
      tmp = tmp->link;
      free(delete);
    }
    else{
      trail = tmp;
      tmp = tmp->link;
    }
  }

  printf("\n\nAfter deleting nodes with odd value\n\n");

  return head;
}

void print_list(NODE *head){
  printf("The ordered list contains:\n");
  int cnt = 0;
  while(head != NULL){
    cnt++;
    printf("(%08X, %3d, %08X)", head, head->data, head->link);
    head = head->link;
    if(cnt == 3){
      printf("\n");
      cnt = 0;
    }
  }
}

void free_list(NODE *head){
  NODE *tmp = NULL;
  while(head != NULL){
    tmp = head;
    head = head->link;
    free(tmp);
  }
}