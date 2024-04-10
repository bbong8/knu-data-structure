#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 80

/* Global Variable */
int stack[MAX_STACK_SIZE];
int top = -1;

/* Function Definition */
int isFull();
int isEmpty();
void push(int e);
int pop();

int main(){
  FILE *ifp = fopen("input1.txt", "r");
  FILE *ofp = fopen("output1.txt", "w");

  if(ifp == NULL || ofp == NULL){
    fprintf(stderr, "Opening file Error");
    exit(EXIT_FAILURE);
  }
  char command;

  fprintf(ofp, "postfix expression : ");

  while(fscanf(ifp, "%c", &command) != EOF){
    fprintf(ofp, "%c", command);

    if(command == ' '){
      continue;
    }

    if(command == '+'){
      int second = pop();
      int first = pop();

      push(first + second);
    }
    else if(command == '-'){
      int second = pop();
      int first = pop();

      push(first - second);
    }
    else if(command == '*'){
      int second = pop();
      int first = pop();

      push(first * second);
    }
    else if(command == '/'){
      int second = pop();
      int first = pop();

      push(first / second);
    }
    else if(command == '%'){
      int second = pop();
      int first = pop();

      push(first % second);
    }
    else{
      push(command - '0');
    }
  }

  fprintf(ofp, "\nthe evaluation : %d", pop());
  fclose(ifp);
  fclose(ofp);
  return 0;
}

int isFull(){
  return top == MAX_STACK_SIZE;
}

int isEmpty(){
  return top == -1;
}

void push(int e){
  if(isFull()){
    fprintf(stderr, "Stack is full");
    exit(EXIT_FAILURE);
  }
  stack[++top] = e;
}

int pop(){
  if(isEmpty()){
    fprintf(stderr, "Stack is empty");
    exit(EXIT_FAILURE);
  }

  return stack[top--];
}