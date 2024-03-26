#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 1001
#define SWAP(x, y, tmp) ((tmp) = (x), (x) = (y), (y) = (tmp))

void sort(int a[], int n){
  int min, tmp;
  for(int i = 0; i < n; i++){
    min = i;
    for(int j = i + 1; j < n; j++){
      if(a[min] > a[j]){
        min = j;
      }
    }
    SWAP(a[i], a[min], tmp);
  }
}

int main(void){
  FILE *fp = fopen("output_4.txt", "w");
  int i, n, step = 10;
  int a[MAX_SIZE];
  double durationOrder, durationReverse, durationRandom;

  printf("     n     order     reverse     random\n");
  fprintf(fp, "     n     order     reverse     random\n");
  for(n = 0; n <= 2000; n += step){
    
    long repetitions = 0;
    clock_t start_1 = clock();

    do{
      repetitions++;

      for(i = 0; i < n; i++){
        a[i] = i;
      }

      sort(a, n);
    } while(clock() - start_1 < 1000);

    durationOrder = ((double) (clock() - start_1)) / CLOCKS_PER_SEC;
    durationOrder /= repetitions;

    repetitions = 0;
    clock_t start_2 = clock();

    do{
      repetitions++;

      for(i = 0; i < n; i++){
        a[i] = n - i;
      }

      sort(a, n);
    } while(clock() - start_2 < 1000);

    durationReverse = ((double) (clock() - start_2)) / CLOCKS_PER_SEC;
    durationReverse /= repetitions;

    repetitions = 0;
    clock_t start_3 = clock();

    do{
      repetitions++;

      for(i = 0; i < n; i++){
        a[i] = rand() % 1000;
      }

      sort(a, n);
    } while(clock() - start_3 < 1000);

    durationRandom = ((double) (clock() - start_3)) / CLOCKS_PER_SEC;
    durationRandom /= repetitions;

    printf("%6d    %f    %f    %f\n", n, durationOrder, durationReverse, durationRandom);
    fprintf(fp, "%6d    %f    %f    %f\n", n, durationOrder, durationReverse, durationRandom);
    if (n == 100) step = 100;
  }

  fclose(fp);
  return 0;
}