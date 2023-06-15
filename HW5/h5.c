#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

void readparams(bool  * s, int * num, int * linenum, int argc, char * argv[]) {
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(argv[i], "-s") == 0) { *s = true; }
        else if (argv[i][0] == '-') { *num = atoi(argv[i] + 1); }
        else { *linenum = atoi(argv[i] + 1); };
    }
}

char * readline(FILE * f) {
    int cursize = 16;
    int newsize = 4;
    char * tmp = NULL;
    tmp = (char *)calloc(cursize, sizeof(char));
    char c;
    int i = 0;
    c = fgetc(f);
    while(feof(f) == 0 && c != '\n') {
        if (i >= cursize - 1) {
            cursize += newsize;
            tmp = (char *)realloc(tmp, cursize);
        }
        tmp[i] = c;
        i++;
        c = fgetc(f);
    }
    tmp[i] = '\0';
    return tmp;
}

void more(bool s, int num, int linenum, FILE * f) {
    char * str = NULL;
    for (int i = 0; i < linenum; i++) { 
        str = readline(f); 
        free(str);
        str = NULL;
    }
    
    bool prevstr = false;
    char c = '.';
    while (c != 'q' && feof(f) == 0) {
        c = getchar();
        if (c == ' ') {
            int i = 1;
            while(feof(f) == 0 && i <= num) {
                str = readline(f);
                if (s == false || prevstr == false || (prevstr == true && strlen(str) != 0)) {
                    printf("%s\n", str);
                    i++;
                }
                if (strlen(str) == 0) { prevstr = true; }
                else { prevstr = false; }
                
                free(str);
                str = NULL;
            }
        }
    }
}


int main(int argc, char* argv[]) {

    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); //сохранение текущего режима
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // изменение
    

    bool s = false;
    int num = 10;
    int linenum = 0;
    readparams(&s, &num, &linenum, argc, argv);
    FILE * f = fopen(argv[argc - 1], "r");
    more(s, num, linenum, f);


    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // восстановление исходного режима
    fclose(f);
    return 0;
}
