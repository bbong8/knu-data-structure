#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_SIZE 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

element multistack[10];
//void add(char* a) {
//	//if()
//}
int main() {
	FILE* fp = fopen("input3.txt", "r");

	int stack_size = 0, stack_top[10] = {0}, i;
	char c[100], trname[100], tr;

	printf("How Many Stacks ? : ");
	scanf("%d", &stack_size);
	printf("\n");
	
	while (fscanf(fp, "%s", c) != EOF) {
		if (strcmp(c, "add") == 0) {
			fscanf(fp, "%d", &i);
			if (i + 1 > stack_size) {
				printf("stack number error, try again\n");
				fscanf(fp, "%s", trname);
			}
			else if (i + 1 == stack_size) {
				if (stack_top[i] >= 10 / stack_size + 10 % stack_size) {
					printf("Stack %d is Full\n", i);
					fscanf(fp, "%s", trname);
				}
				else {
					multistack[stack_top[i]+i*stack_size].id = i;
					fscanf(fp, "%s", multistack[stack_top[i] + i*stack_size].name);
					printf("%s is Pushed in Stack No. %d\n", multistack[stack_top[i] + i * stack_size].name, i);
					stack_top[i]++;
				}
			}
			else {
				if (stack_top[i] >= 10 / stack_size) {
					printf("Stack %d is Full\n", i);
					fscanf(fp, "%s", trname);
				}
				else {
					multistack[stack_top[i] + i*stack_size].id = i;
					fscanf(fp, "%s", multistack[stack_top[i]+i*stack_size].name);
					printf("%s is Pushed in Stack No. %d\n", multistack[stack_top[i] + i * stack_size].name, i);
					stack_top[i]++;
				}
			}
			
		}
		else if (strcmp(c, "delete") == 0) {
			fscanf(fp, "%d", &i);
			if (stack_top[i] == 0) {
				printf("Stack %d is Empty\n", i);
			}
			else {
				printf("%s is popped from Stack No. %d\n", multistack[i * stack_size + stack_top[i]-1].name, i);
				stack_top[i]--;
			}
		}
		else if (strcmp(c, "sprint") == 0) {
			fscanf(fp, "%d", &i);
			
			if (i >= stack_size) {
				printf("stack number error, try again\n");
				continue;
			}
			int f = 0;
			printf("\n");
			//printf("stack %d\n", i);
			for (f = stack_top[i]-1; f >=0; f--) {
				printf("%s\n", multistack[i * stack_size + f].name);
			}
			printf("\n");
		}
		else if (strcmp(c, "quit") == 0) {
			printf("\nProgram end\n\n");
			int f = 0,l=0;
			for (f = 0; f < stack_size; f++) {
				printf("stack %d :\n", f);
				for (l = stack_top[f] - 1; l >= 0; l--) {
					printf("%s\n", multistack[f * stack_size + l].name);
				}
				printf("\n");
			}
		}
		else {
			printf("wrong command, try again!!\n");
			fscanf(fp, "%[^\n]s %c", trname, &tr);
		}

	}

}