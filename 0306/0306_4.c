#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define SWAP(x, y, tmp) ((tmp) = (x), (x) = (y), (y) = (tmp))

void selection_sort(int arr[], int n){
  int min = 0, tmp = 0;

  for(int i = 0; i < n - 1; i++){
    min = i;
    for(int j = i + 1; j < n; j++){
      if(arr[min] > arr[j]){
        min = j;
      }
    }
    SWAP(arr[i], arr[min], tmp);
  }
}

int binary_search(int arr[], int t, int left, int right){
  int middle;

  while(left <= right){
    middle = (left + right) / 2;

    if(arr[middle] == t){
      return middle;
    }
    else if(arr[middle] < t){
      return binary_search(arr, t, middle+1, right);
    }
    else if(arr[middle] > t){
      return binary_search(arr, t, left, middle-1);
    }
  }

  return -1;
}

int main(){
  int n, t, arr[MAX_SIZE] = {0};
  printf("Enter the number of numbers to generate: ");
  scanf("%d", &n);

  for(int i = 0; i < n; i++){
    arr[i] = rand() % 1000;
    printf("%-5d", arr[i]);
  }
  printf("\n\n");

  printf("Sorted array:\n");
  selection_sort(arr, n);

  for(int i = 0; i < n; i++){
    printf("%-5d", arr[i]);
  }
  printf("\n\n");

  printf("Enter the number to search: ");
  scanf("%d", &t);
  printf("The search number is present in list[%d]\n", binary_search(arr, t, 0, n-1));

  return 0;
}