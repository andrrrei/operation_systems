#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct cnt {
    long int num;
    int count;
    struct cnt* next;
};

struct cnt * newlist(struct cnt * list, long int a) {
    struct cnt *p;
    p = (struct cnt*)malloc(sizeof(struct cnt));
    p->num = a;
    p->next = NULL;
    p->count = 1;
    list = p;
    return(list);
}

struct cnt* add(struct cnt* list, long int n) {
    struct cnt *newelem, *p;
    newelem = (struct cnt*)malloc(sizeof(struct cnt));
    p = list;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newelem;
    newelem->num = n;
    newelem->count = 1;
    newelem->next = NULL;
    return list;
}

struct cnt* inlist(struct cnt* list, long int n) {
    if (list == NULL) {
        list = newlist(list, n);
    }
    else {
        bool flag = false;
        struct cnt* p = list;
        while (p != NULL && !(flag)) {
            if (p->num == n) {
                flag = true;
                p->count += 1;
            }
            p = p->next;
        }
        if (flag == false) {
            list = add(list, n);
        }
    }
    return(list);
}

struct cnt* makelist(struct cnt* list) {
    long int c = 0;
    int a = scanf("%ld", &c);
    while (a != -1) {
        list = inlist(list, c);
        a = scanf("%ld", &c);
    }
    return(list);
}

void printlist(struct cnt* list, int n) {
    struct cnt *p = list;
    printf("\n");
    while (p != NULL) {
        if (p->count == n) {
            printf("%ld ", (p->num));
        }
        p = p->next;
    }
}

struct cnt* dellist(struct cnt* list) {
    struct cnt* p = list;
    while (p != NULL) {
        list = p;
        p = list->next;
        free(list);
    }
    return(list);
}

int main() {

    struct cnt* list = NULL;

    int n;
    printf("%s", "Enter N: ");
    scanf("%d", &n);

    list = makelist(list);
    printlist(list, n);

    list = dellist(list);

}