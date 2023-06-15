#include<stdio.h>
#include <stdbool.h> 

int main() {
    char c = '0';
    char arr[50] = {0};
    int count = -1;
    bool flag = true; // отслеживаем, совпадает ли текущее слово с "cat"
    while (c != '\n') {
        c = getchar();
        count++;
        if ( (c != 'c' && count == 0) || (c != 'a' && count == 1) || (c != 't' && count == 2) || ((c != ' ' && c != '\n') && count == 3) ) {
            flag = false;
        }
        if (c != ' ' && c != '\n') {
            arr[count] = c;
        }
        else {
            if (flag) {
                printf("%s", "cat ");
                count = -1;
            }
            else {
                for (int i = count-1; i >= 0; i--) {
                    printf("%c", arr[i]);
                }
                printf("%c", ' ');
                count = -1;
                flag = true;
            }
        }
    }
}
