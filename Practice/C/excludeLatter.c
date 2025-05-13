#include <stdio.h>

void excludeRedundantLetters(char *str){

  if(str == NULL) {
    return;
  }

  for (int i = 0; str[i] != '\0'; ++i){
    for (int j = 0; str[j] != '\0'; ++j){
      if(str[i] == str[j] && i != j){
        for(int k = j;  str[k] != '\0'; ++k){
          str[k] = str[k+1];
        }
        --j;
      }
    }
  }
}

int main(){
  char data[100] = "Hello World";
  excludeRedundantLetters( data );
  printf("%s", data);
}