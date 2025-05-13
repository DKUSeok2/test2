#include <stdio.h>

int countWords(const char *str) {
    int count = 0;
    int word = 0;
    while (*str != '\0') {
        if (*str == ' ' || *str == '\t' || *str == '\n') {
            word = 0;
        }
        else {
            if (!word) {
                count++;
                word = 1;
            }
        }
        str++;

    }
    return count;
}

int main(){
    int nWords = countWords("Hello World. Here is the train\n");
    printf ("%d", nWords); //6개가 출력됨.
    
    return 0;
}