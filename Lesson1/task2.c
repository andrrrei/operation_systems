#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    double res_sum = 0;
    char *res_concat = (char *)malloc(16);
    char *cur = res_concat;
    int ressize = 16; // Allocated size of res_concat
    int cursize = 0; // Actual size of res_concat
    double n;
    int size; // Size of the new word
    for (int i = 1; i <= argc; i++) {
        if (argv[i] != 0) {
            n = strtod(argv[i], NULL);
            if (n == 0) {
                size = strlen(argv[i]);
                if (size + cursize >= ressize) {
                    res_concat = (char *)realloc(res_concat, ressize + size);
                    ressize += size;
                }
                memcpy(cur, argv[i], size + 1);
                cursize += size;
                cur += size;
            } else {
                res_sum += n;
            }
        }
    }
    res_concat[cursize + 1] = '\0';
    printf("res_sum = %f \n", res_sum);
    printf("res_concat = %s \n", res_concat);
}
