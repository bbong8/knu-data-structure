#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(p, s) \
  if (!((p) = malloc(s))){\
    fprintf(stderr, "Insufficient memory");\
    exit(EXIT_FAILURE);\
  }
#define MALE 1
#define FEMALE 0
#define PRINT_SEX(sex) ((sex) ? "남자" : "여자")

typedef struct node{
  char name[20];
  char org[100];
  int sex;
  struct node *link;
} NODE;

NODE* create_new_node(char name[], char org[]);
NODE* insert_node(NODE *head, NODE *new);
NODE* concat_list(NODE *fir, NODE *sec);
NODE* inverse_list(NODE *head);
void divide_by_sex(NODE *total, NODE **male, NODE **female);
void print_list(NODE *head);
void free_list(NODE *head);

int main(){
  FILE *ifp = fopen("input2.txt", "r");
  if(ifp == NULL){
    fprintf(stderr, "File opening error");
    exit(EXIT_FAILURE);
  }

  NODE *total = NULL, *male = NULL, *female = NULL;
  char name[20], org[100], sex[20];
  int sex_int = 0;

  while(fscanf(ifp, "%s %s %s", name, org, sex) != EOF){
    NODE *new = create_new_node(name, org);

    if(!strcmp(sex, "남자")){
      new->sex = MALE;
    }
    else{
      new->sex = FEMALE;
    }

    total = insert_node(total, new);
  }
  
  printf("전체 리스트\n");
  print_list(total);

  divide_by_sex(total, &male, &female);

  printf("남자 리스트\n");
  print_list(male);
  printf("여자 리스트\n");
  print_list(female);

  total = concat_list(female, male);
  printf("합친 리스트\n");
  print_list(total);

  total = inverse_list(total);
  printf("inversed list\n");
  print_list(total);

  free_list(total);
  fclose(ifp);

  return 0;
}

NODE* create_new_node(char name[], char org[]){
  NODE *new;
  MALLOC(new, sizeof(NODE));
  strcpy(new->name, name);
  strcpy(new->org, org);
  new->sex = 0;
  new->link = NULL;

  return new;
}

NODE* insert_node(NODE *head, NODE *new){
  NODE *tmp = head;
  if(head == NULL){
    return new;
  }
  else{
    while(tmp->link != NULL){
      tmp = tmp->link;
    }
    tmp->link = new;
  }

  return head;
}

NODE* concat_list(NODE *fir, NODE *sec){
  if(fir == NULL){
    return sec;
  }
  if(sec == NULL){
    return fir;
  }

  NODE *tmp = fir;
  while(tmp->link != NULL){
    tmp = tmp->link;
  }
  tmp->link = sec;

  return fir;
}

NODE* inverse_list(NODE *head){
  NODE *trail = NULL, *middle = NULL, *lead = head;
  while(lead != NULL){
    trail = middle;
    middle = lead;
    lead = lead->link;
    middle->link = trail;
  }

  return middle;
}

void divide_by_sex(NODE *total, NODE **male, NODE **female){
  NODE *save;
  while(total != NULL){
    save = total;
    total = total->link;
    save->link = NULL;
    if(save->sex){
      *male = insert_node(*male, save);
    }
    else{
      *female = insert_node(*female, save);
    }
  }
}

void print_list(NODE *head){
  int cnt = 0;
  while(head != NULL){
    cnt++;
    printf("(%p, %s, %s, %s, %p)", head, head->name, head->org, PRINT_SEX(head->sex), head->link);
    head = head->link;
    if(cnt == 2){
      printf("\n");
      cnt = 0;
    }
  }
  if(cnt != 0){
    printf("\n");
  }
  printf("\n");
}

void free_list(NODE *head){
  NODE *tmp = NULL;
  while(head != NULL){
    tmp = head;
    head = head->link;
    free(tmp);
  }
}