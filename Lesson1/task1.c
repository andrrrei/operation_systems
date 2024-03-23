#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int size = 16;
const int newsize = 8;

// Function to read a line of input
char* readline(char * p) {
    char c = '0';
    int i = 0;
    int cursize = size;
    while (c != '\n') {
        p[i] = c;
        i++;
        if (i >= cursize) {
            cursize += newsize;
            p = (char*)realloc(p, cursize);
        }
        c = getchar();
    }
    p[i] = '\0';
    return p;
}

// Function to copy characters from one array to another
char* copy(char * s1, char * s0, int * i, int * k, int * cursize, bool * flag) {
    char c = s1[*i];
    while (c == ' ') {
        (*i)++;
        c = s1[*i];
    }
    while (c != ' ' && c != '\0') {
        if (*k >= *cursize-4) {
            *cursize += newsize;
            s0 = (char*)realloc(s0, (*cursize));
        }
        s0[*k] = c;
        (*i)++;
        (*k)++;
        c = s1[*i];
    }
    s0[*k] = ' ';
    (*k)++;
    if (c == '\0') {
        *flag = false;
    }
    return s0;
}

// Function to concatenate words from two arrays
char * make(char* p, char* s1, char* s2) {
    bool flag = true;
    int i = 0;
    int j = 0;
    int k = 0;
    int cursize = size;
    while (flag) {
        p = copy(s1, p, &i, &k, &cursize, &flag);
        p = copy(s2, p, &j, &k, &cursize, &flag);
    }
    flag = true;
    while (flag) {
        p = copy(s1, p, &i, &k, &cursize, &flag);
    }
    flag = true;
    while (flag) {
        p = copy(s2, p, &j, &k, &cursize, &flag);
    }
    p[k] = '\0';
    return p;
}
