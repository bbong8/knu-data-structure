#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 100
#define EXPR_SIZE 100

int stack[STACK_SIZE];
char expr[EXPR_SIZE];
char post[EXPR_SIZE];

int precedence(int op) {
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/'||op=='%') return 2;
    else return 3;
}

int top;

void push(int t) {
    if (top >= STACK_SIZE - 1) {
        printf("\nStack overflow.");
    }
    stack[++top] = t;
}
int pop(void) {
    if (top < 0) {
        printf("\nStack underflow.");
        return -1;
    }
    return stack[top--];
}

int get_top(void) {
    return (top < 0) ? -1 : stack[top];
}

int is_empty(void) {
    return (top < 0);
}

int is_oper(int k) {
    return (k == '+' || k == '-' || k == '*' || k == '/');
}
void init(void) {
    top = -1;
}

void postfix(char* dst, char* src) {
    char c;
    init();
    while (*src) {
        if (*src == '(') {
            push(*src);
            src++;
        }
        else if (*src == ')') {
            while (get_top() != '(') {
                *dst++ = pop();
                *dst++ = ' ';
            }
            pop();
            src++;
        }
        else if (is_oper(*src)) {
            while (!is_empty() &&
                precedence(get_top()) >= precedence(*src)) {
                *dst++ = pop();
                *dst++ = ' ';
            }
            push(*src);
            src++;
        }//?
        else if (*src >= '0' && *src <= '9') {
            do {
                *dst++ = *src++;
            } while (*src >= '0' && *src <= '9');
            *dst++ = ' ';
        }
        else {
            src++;
        }
    }

    while (!is_empty()) {
        *dst++ = pop();
        *dst++ = ' ';
    }
    dst--;
    *dst = 0;
}

int main(void) {
    FILE* f;
    f = fopen("input2.txt", "r");

    fscanf(f, "%s", expr);
    fclose(f);

    f = fopen("output2.txt", "w");
    printf("<<<<<<<<<< infix to postfix >>>>>>>>>>>\n");
    printf("infix expression	: %s\n", expr);

    postfix(post, expr);
    fprintf(f, "%s\n", post);
    printf("postfix expression	: %s\n", post);
}