#include <stdio.h>

int countMatchedNumberLetterInString(const char *str, int digit){
  int count = 0;

  while(*str !=  '\0'){
    if(*str - '0' == digit){
      count++;
    }
    str++;
  }
  return count;
}

int main(){
  int count = countMatchedNumberLetterInString("112233443311334913201234", 4);
  printf("%d\n", count);

  return 0;
}