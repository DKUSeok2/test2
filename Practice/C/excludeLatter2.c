#include <stdio.h>

void excludeRedundantLetters(char *str) {
    if (str == NULL) {
        return;
    }

    int newData[256] = {0};
    int newIndex = 0; 

    for (int i = 0; str[i] != '\0'; ++i) {
        if (newData[str[i]] == 0) { 
            str[newIndex++] = str[i]; 
            newData[str[i]] = 1; 
        }
    }

    str[newIndex] = '\0';
}

int main() {  
    char data[100] = "Hello World";
    excludeRedundantLetters(data);
    printf("%s", data);
    return 0;
}