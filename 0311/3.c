#include <stdio.h>
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
  FILE *fp = fopen("output_3.txt", "w");
  int i, n, step = 10;
  int a[MAX_SIZE];
  double duration;

  printf("     n     repetitions     time\n");
  fprintf(fp, "     n     repetitions     time\n");
  for(n = 0; n <= 2000; n += step){
    
    long repetitions = 0;
    clock_t start = clock();

    do{
      repetitions++;

      for(i = 0; i < n; i++){
        a[i] = n - i;
      }

      sort(a, n);
    } while(clock() - start < 1000);

    duration = ((double) (clock() - start)) / CLOCKS_PER_SEC;
    duration /= repetitions;

    printf("%6d    %9ld     %f\n", n, repetitions, duration);
    fprintf(fp, "%6d    %9ld     %f\n", n, repetitions, duration);
    if (n == 100) step = 100;
  }

  fclose(fp);
  return 0;
}