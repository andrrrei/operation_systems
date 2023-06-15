#include <stdio.h>
#include <stdlib.h>

const int size = 16;
const int arrsize = 24;
const int newsize = 8;
const int strsize = 10;

char* readline(char * p) {
    char c;
	int i = 0;
	int cursize = size;
	int a = scanf("%c", &c);
	while (a != -1) {
		p[i] = c;
		i++;
		if (i >= cursize) {
			cursize += newsize;
			p = (char*)realloc(p, cursize);
		}
		a = scanf("%c", &c);
	}
	p[i] = '\0';
	return p;
}

void printarr(char** arr, int j) {
    for (int i = 0; i < j; i++) {
        printf("%s\n", arr[i]);
    }
    printf("\n");
}

char** makearr(char** p, char* s) {
    int i = 0;
    int j = 0;
    int cursize = arrsize;
    int strcursize = strsize;
    int k;
    while (s[i] != '\0') {
        if (4*j >= cursize - 8) {
            cursize += newsize;
            p = (char**)realloc(p, cursize*sizeof(char*));
        }
        while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r') && s[i] != '\0') {
            i++;
        }
        char* str;
        str = (char*)malloc(strsize);
        strcursize = strsize;
        k = 0;
        while (s[i] != ' ' && s[i] != '\0') {
            if (k >= strcursize - 4) {
                strcursize += newsize;
                str = (char*)realloc(str, strcursize);
            }
            str[k] = s[i];
            i++;
            k++;
        }
        str[k] = '\0';
        p[j] = str;
        j++;
    }
    printf("\n");
    printarr(p, j);
    p[j+1] = NULL;
    return p;
}

void delarr(char** arr) {
    int i = 0;
    while (arr[i] != NULL) {
        free(arr[i]);
        i++;
    }
}

int main() {

    char** arr;
    char* s;
    s = (char*)malloc(size);
    arr = (char**)malloc(arrsize*sizeof(char*));

    printf("%s", "Enter the string: ");
    s = readline(s);
    arr = makearr(arr, s);

    delarr(arr);
    free(s);
    free(arr);

}