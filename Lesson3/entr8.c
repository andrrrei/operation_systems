#include <stdio.h>
#include <stdlib.h>

struct inf {
    int num;
    int len;
    int offset;
    struct inf * next;
};


int linescounter(FILE * f) {
    int cnt = 0;
    char c;
    while (feof(f) == 0) {
        c = fgetc(f);
        if (c == '\n') {
            cnt += 1;
        }
    }
    return cnt+1;
}


int lenofstr(FILE * f) {
    int len = 0;
    char c = fgetc(f);
    while (c != '\n' && c != EOF) {
        len++;
        c = fgetc(f);
    }
    return len;
}


struct inf * create(FILE * f, struct inf * arr, int cnt) {
    arr = (struct inf *)malloc(sizeof(struct inf));
    struct inf * p = arr;
    int cur_sum_len = 0;
    for (int i = 0; i < cnt; i++) {
        arr->num = i+1;
        arr->len = lenofstr(f);
        arr->offset = cur_sum_len;
        cur_sum_len += arr->len+1;
        if (i < cnt - 1) {
            arr->next = (struct inf *)malloc(sizeof(struct inf));
            arr = arr->next;
        }
    }
    return p;
}


void printstr(FILE * f, struct inf * arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        arr = arr->next;
    }
    int offset = arr->offset;
    fseek(f, offset, SEEK_SET);
    char * s = (char *)malloc(arr->len+1);
    fgets(s, arr->len+1, f);
    printf("%s\n", s);
    free(s);
}


/*void printlist(struct inf * lst)
{
    while (lst != NULL)
    {
        printf("%d\n", (lst->num));
        lst = lst->next;
    }
}*/

struct inf * sortlist(struct inf * arr, int cnt) {
    struct inf * p;
    int o, n, l;
    for (int i = cnt - 1; i >= 0; i--) {
        p = arr;
        for (int j = 0; j < i; j++) {
            if (p->len > p->next->len) {
                n = p->num;
                l = p->len;
                o = p->offset;
                p->len = p->next->len;
                p->num = p->next->num;
                p->offset = p->next->offset;
                p = p->next;
                p->len = l;
                p->num = n;
                p->offset = o;
            }
            else { p = p->next; }
        }
    }
    return arr;
}

void copy(FILE * f1, FILE * f2, struct inf * arr, int cnt) {
    int offset;
    for (int i = 0; i < cnt; i++) {
        fseek(f1, 0, SEEK_SET);
        offset = arr->offset;
        fseek(f1, offset, SEEK_SET);
        char * s = (char *)malloc(arr->len+1);
        fgets(s, arr->len+1, f1);
        printf("%s\n", s);
        fprintf(f2, "%s\n", s);
        free(s);
        arr = arr->next;
    }
}

struct inf* dellist(struct inf* list) {
    struct inf* p = list;
    while (p != NULL) {
        list = p;
        p = list->next;
        free(list);
    }
    return(list);
}



int main(int argc, char* argv[]) {

    FILE *f1;
    f1 = fopen(argv[1], "r");
    
    int cnt = linescounter(f1);
    printf("There is %d strings in the file\n", cnt);

    struct inf * arr;
    fseek(f1, 0, SEEK_SET);
    arr = create(f1, arr, cnt);

    int n;
    printf("%s", "Enter the number of the string y'd like to see: ");
    scanf("%d", &n);
    fseek(f1, 0, SEEK_SET);
    printstr(f1, arr, n);

    arr = sortlist(arr, cnt);

    FILE * f2 = fopen("res.txt", "w");
    copy(f1, f2, arr, cnt);

    fclose(f1);
    fclose(f2);

    dellist(arr);
}