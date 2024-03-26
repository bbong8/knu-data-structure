#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char name[10];
  int age;
  float salary;
} human;

int humansEqual(human *person1, human *person2){
  if(strcmp(person1->name, person2->name)){
    return 0;
  }
  if(person1->age != person2->age){
    return 0;
  }
  if(person1->salary != person2->salary){
    return 0;
  }

  return 1;
}

int main(){
  human person1, person2;

  printf("Input person1's name, age, salary :\n");
  fgets(person1.name, 20, stdin);
  scanf("%d", &person1.age);
  scanf("%f", &person1.salary);


  printf("Input person2's name, age, salary :\n");
  getchar();
  fgets(person2.name, 20, stdin);
  scanf("%d", &person2.age);
  scanf("%f", &person2.salary);

  if(humansEqual(&person1, &person2)){
    printf("The two human beings are the same");
  }else{
    printf("The two human beings are not the same");
  }
  
  return 0;
}