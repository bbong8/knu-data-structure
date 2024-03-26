#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_DEGREE 101 /*Max degree of polynomial+1*/

typedef struct {
  int degree;
  float coef[MAX_DEGREE];
} polynomial;

void poly_print(char ch[], polynomial a){
  printf("%s = ", ch);
  for(int i = 0; i < a.degree + 1; i++){
    if(a.coef[i] == 0){
      continue;
    }

    if(i != 0){
      printf(" + ");
    }
    
    if(a.degree - i != 0){
      printf("%.0f", a.coef[i]);
      printf("x^%d", a.degree - i);
    }
    else{
      printf("%.0f", a.coef[i]);
    }
  }
  printf("\n");
}

int main(){
  polynomial a, b, c;
  int a_diff = 0, b_diff = 0;
  printf("<< C(x) = A(x) + B(x) >>\n");

  printf("Input the degree of items of A(x) : ");
  scanf("%d", &a.degree);
  printf("Input the coefficients of A(x) : ");
  for (int i = 0; i < a.degree + 1; i++){
    scanf("%f", &a.coef[i]);
  }

  printf("Input the degree of items of B(x) : ");
  scanf("%d", &b.degree);
  printf("Input the coefficients of B(x) : ");
  for (int i = 0; i < b.degree + 1; i++){
    scanf("%f", &b.coef[i]);
  }

  c.degree = (a.degree > b.degree) ? a.degree : b.degree;
  a_diff = c.degree - a.degree;
  b_diff = c.degree - b.degree;

  for (int i = 0; i < c.degree + 1; i++){
    c.coef[i] = 0;
    if(i - a_diff >= 0){
      c.coef[i] += a.coef[i - a_diff];
    }
    if(i - b_diff >= 0){
      c.coef[i] += b.coef[i - b_diff];
    }
  }

  poly_print("A(x)", a);
  poly_print("B(x)", b);
  poly_print("C(x)", c);

  return 0;
}