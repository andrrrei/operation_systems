#include <stdio.h>
#include <stdbool.h> 

int main() {
    char c = '0';
    char arr[50] = {0};
    int count = -1;
    bool flag = true; // Track if the current word matches "cat"
    while (c != '\n') {
        c = getchar();
        count++;
        // Check if the current character does not match the expected character for "cat"
        // or if it's not a space or newline character for a word separation
        if ((c != 'c' && count == 0) || 
            (c != 'a' && count == 1) || 
            (c != 't' && count == 2) || 
            ((c != ' ' && c != '\n') && count == 3)) {
            flag = false;
        }
        if (c != ' ' && c != '\n') {
            arr[count] = c; // Store non-space characters into an array
        }
        else {
            if (flag) {
                printf("%s", "cat "); 
                count = -1; 
            }
            else {
                // Print characters in reverse order if the word is not "cat"
                for (int i = count - 1; i >= 0; i--) {
                    printf("%c", arr[i]);
                }
                printf("%c", ' '); 
                count = -1; 
                flag = true;
            }
        }
    }
}
