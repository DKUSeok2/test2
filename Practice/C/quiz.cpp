#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//���� 1
int countMatchedNumberLetterInString(const char* str, int digit) {
    int count = 0;           
    while (*str != '\0'){      //null ������ ����ϱ����� while�� ���    //���ڿ� ���� ������ ������ �ݺ�
        if (*str - '0' == digit) {       //*str�� �ּҰ��� �ƴ� �ش� ���̰� �� �ش� ������ 0�� ���� �� �� ���� digit�� ��ġ�ϸ� count�� ����
            count++;            
        }
        str++;                 //��ġ���� �ʴ´ٸ� ���� ���ڷ� �̵�
    }
    return count;             //count���� ��ȯ����
}

//���� 2
void excludeRedundantLetters(char* str) {
    int n = 0;
    int i, j;
    for (i = 0; str[i] != '\0'; i++) {       //���ڿ� ���� ������ ������ �ݺ�
        char c = str[i];               //���� ���� ����
        int repeat = 0;               //�ߺ� ���� �Ǻ� ���� �ʱ�ȭ

        for (j = 0; j < n; j++) {        //n������ �������� �ߺ��� �ִ��� �˻�
            if (str[j] == c) {
                repeat = 1;             //�ߺ��� �ִٸ� repeat ������ 1�� �����ϰ� �ݺ��� ����
                break;
            }
        }
        if (repeat == 0) {             //�ߺ����� �ʴ´ٸ� ���ڸ� �ߺ��� ���� ���ڿ��� �߰�
            str[n] = c;
            n++;                    // n�� 1 ����
        }
    }
    str[n] = '\0';              //�ߺ��� ���� ���ڿ� ���� �����ϱ� ���� null �߰�
}


//���� 3
int countWords(const char *str) {
    int count = 0;
    int word = 0;
    while (*str != '\0') {          //���ڿ� ���� ������ ������ �ݺ�
        if (*str == ' ' || *str == '\t' || *str == '\n') {        
            word = 0;            //���� �ܾ� ������ ���� ���Ͽ� 0���� �ʱ�ȭ
        }
        else { 
            if (word == 0) {    
                count++;
                word = 1;
            }
        }
        str++;

    }
    return count;
}

//���� 4
bool examinePairedParenthesis(const char* str) {
    int count = 0;
    int i;
    for (i = 0; str[i] != '\0'; i++) {           //���ڿ��� ���� ������ �ݺ�
        if (str[i] == '(') {
            count++;                        //���ڿ� Ž�� �� ���� ��ȣ�� �� count�� ����
        }
        else if (str[i] == ')') {
            count--;                    //���ڿ� Ž�� �� ���� ��ȣ�� �� count�� ����
            if (count < 0) {             
                return false;          //���ڿ� ��ü Ž���� ������ ���� count ���� ������ ������ false�� ��ȯ
            }                         /*������� "(()))(()"�� ��� Ž���� ������ count ���� 0������ Ž�� �߰��� count���� ������ ���ϴ�
                                        ���������� �����̹Ƿ� ���� 0�̴��� fasle�� ��ȯ�ؾ���*/
        }
    }
    return count == 0;             // count ���� 0�̸� true ��ȯ, 0�� �ƴϸ� false ��ȯ
}

//���� 5
void convertString(char* input) {
    int count = 0;
    int length = strlen(input);
    int i;

    for (i = 0; i < length; i++) {   
        if (input[i] == ' ') {
            count++; 
        }
    }

    int n_length = length + count * 2;   //���ο� ���ڿ��� ���̴� ���� ���ڿ��� ���鿡 %20�� ���� �ϹǷ� %20�� �� ������ 2�� ������
    input[n_length] = '\0';            //���ο� ���ڿ��� ���� ǥ���ϱ� ���� null �߰�

    for (i = length - 1; i >= 0; i--) {   //���ڿ� �ε����� 0���� �����ϱ� ������ length - 1���� ����
        if (input[i] == ' ') {
            input[n_length - 1] = '0';
            input[n_length - 2] = '2';
            input[n_length - 3] = '%';
            n_length = n_length - 3;         //%20�� ���鿡 �ְ� �� ��ġ�� ���� �����ϱ� ���� %20�� 3���� �����̹Ƿ� 3��ŭ ������ �̵�
        }
        else {
            input[n_length - 1] = input[i];   //���� ���ڰ� �ƴϸ� ���� ���ڸ� ���ο� ���ڿ��� ����
            n_length--;     //���ο� ���ڿ� ������ ���ڸ� �����Ƿ� n_length�� ����
        }
    }
}

int main() {
    //���� 1
    int count = countMatchedNumberLetterInString("112233443311334913201234", 4);
    // �Է����� ���޵� ���ڿ� �߿��� 4��� ���ڿ� ������ ��4�����ڰ� ��Ÿ�� Ƚ���� ���
    printf("%d\n\n", count);    // 4�� ��µ�
    //����

    //���� 2
    char data[100]{"Hello World"};
    excludeRedundantLetters(data);
    printf("%s\n\n", data); // ��Helo Wrd�� �� ���
    //����

    //���� 3
    int nWords = countWords("Hello World.   Here    is the train\n");
    printf ("%d\n\n", nWords); //6���� ��µ�.
    //����

    //���� 4
    bool result = examinePairedParenthesis("((()))");
    printf("%s\n\n", result == true ? "true" : "false"); // ��true���� ����
    //����
    
    //���� 5
    char input[100] = "Hello World. Nice to Meet   you.";
    convertString(input);
    printf("%s\n\n", input);
    //����


    return 0;
}
