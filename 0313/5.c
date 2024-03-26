#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_TERMS 100
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

/* Struct Definition */
typedef struct {
	float coef;
	int expon;
}term;

/* Global Variable*/
term terms[MAX_TERMS];
int avail;

/* Function */
void attach(float coefficient, int exponent) {
	if (avail >= MAX_TERMS) {
		printf("Too many terms in the polynomial\n");
	}

	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

void padd(int start_a, int end_a, int start_b, int end_b, int *start_d, int * end_d){
  float coefficient;
  *start_d = avail;

  while(start_a <= end_a && start_b <= end_b){
		switch(COMPARE(terms[start_a].expon, terms[start_b].expon)){
			case -1:
				attach(terms[start_b].coef, terms[start_b].expon);
				start_b++;
				break;
			case 0:
				coefficient = terms[start_a].coef + terms[start_b].coef;
				if(coefficient){
					attach(coefficient, terms[start_a].expon);
				}
				start_a++;
				start_b++;
				break;
			case 1:
				attach(terms[start_a].coef, terms[start_a].expon);
				start_a++;
		}
	}

	for(; start_a <= end_a; start_a++){
		attach(terms[start_a].coef, terms[start_a].expon);
	}

	for(; start_b <= end_b; start_b++){
		attach(terms[start_b].coef, terms[start_b].expon);
	}

	*end_d = avail - 1;
}

void poly_print(char polynomial, int start, int end) {
	int i;
	printf("%c(X) = ", polynomial);

	for (i = start; i < end; i++) {
		printf("%.0fx^%d + ", terms[i].coef, terms[i].expon);
	}

	if (terms[i].expon != 0){
		printf("%.0fx^%d\n", terms[i].coef, terms[i].expon);
  }else{
		printf("%.0f\n", terms[i].coef);
  }
}

int main(){
  int a_size, b_size, i, d_start, d_end;
  printf("<< D(x) = A(x) + B(x) >>\n");
  printf("Input the number of items of A(x) : ");
  scanf("%d", &a_size);
	printf("Input the number of items of B(x) : ");
	scanf("%d", &b_size);

  printf("\ninput in descending order\n");

  printf("coefficient and exponent of A(x)=10x^5+8x^3+7 (10 5, 8 3, 7 0 ) : ");
	for (i = 0; i < a_size; i++) {
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
	}

	printf("coefficient and exponent of B(x)=10x^5+8x^2+3 (10 5, 8 2, 3 0 ) : ");
	for (i = a_size; i < a_size + b_size; i++) {
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
	}

  printf("\n");
  avail = a_size + b_size;
  padd(0, a_size - 1, a_size, a_size + b_size - 1, &d_start, &d_end);

  poly_print('A', 0, a_size - 1);
  poly_print('B', a_size, a_size + b_size - 1);
	poly_print('D', d_start, d_end);

	return 0;
}