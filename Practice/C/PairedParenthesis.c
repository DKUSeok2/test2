#include <stdio.h>
#include <stdbool.h>

bool examinePairedParenthesis(const char *str){
  int count = 0;

  while(*str != '\0'){
    if(*str == '('){
      count++;
    }
    else if(*str == ')'){
      count--;
    }
    if(count < 0){
      return false;
      }
    str++;
  }
  return count == 0;
}

int main(){
  bool result = examinePairedParenthesis( "((()))" );
  printf("%s", result == true ? "true" : "false");
  
}