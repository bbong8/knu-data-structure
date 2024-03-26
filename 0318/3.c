#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_STRING_SIZE 100
#define MAX_PATTERN_SIZE 100

int nfind(char* string, char* pat);

int main(){
  int k;
  char string[MAX_STRING_SIZE];
  char pat[MAX_PATTERN_SIZE];

  printf("문자열을 입력하세요 : ");
  scanf("%s", string);

  printf("비교할 문자열을 입력하세요 : ");
  scanf("%s", pat);

  k = nfind(string, pat);
  
  printf("문자열 %d 번째부터 패턴이 시작됨..", k);
  return 0;
}

int nfind(char* string, char* pat) {
  if (strlen(pat) == 1) {
    for (int i = 0; i < strlen(string); i++) {
      if (string[i] == pat[0]) {
        return i;
      }
    }
    return -1;
  }

  int i = 0, j = 0, start = 0;
  int lasts = strlen(string) - 1;
  int lastp = strlen(pat) - 1;
  int endmatch = lastp;

  for (; endmatch <= lasts; endmatch++, start++) {
    if (string[endmatch] == pat[lastp]) {
      for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++);
    }
    if (j == lastp) {
      return start;
    }
  }

  return -1;
}