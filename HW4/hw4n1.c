#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct cnt
{
    long int num;
    int count;
    struct cnt *next;
};

int len(struct cnt * lst) {
    int l = 0;
    while (lst != NULL) {
        l++;
        lst = lst->next;
    }
    return l;
}

struct cnt * newlist(struct cnt *list, long int a)
{
    struct cnt *p;
    p = (struct cnt *)malloc(sizeof(struct cnt));
    p->num = a;
    p->next = NULL;
    p->count = 1;
    list = p;
    return (list);
}

struct cnt * add(struct cnt *list, long int n)
{
    struct cnt *newelem, *p;
    newelem = (struct cnt *)malloc(sizeof(struct cnt));
    p = list;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = newelem;
    newelem->num = n;
    newelem->count = 1;
    newelem->next = NULL;
    return list;
}

struct cnt * inlist(struct cnt *list, long int n)
{
    if (list == NULL)
    {
        list = newlist(list, n);
    }
    else
    {
        bool flag = false;
        struct cnt *p = list;
        while (p != NULL && !(flag))
        {
            if (p->num == n)
            {
                flag = true;
                p->count += 1;
            }
            p = p->next;
        }
        if (flag == false)
        {
            list = add(list, n);
        }
    }
    return (list);
}


void printlist(struct cnt *list)
{
    struct cnt *p = list;
    printf("\n");
    while (p != NULL)
    {
        printf("%ld ", (p->num));
        p = p->next;
    }
}

struct cnt * makelist(struct cnt *list)
{
    long int c = 0;
    int a = scanf("%ld", &c);
    while (a != -1)
    {
        list = inlist(list, c);
        a = scanf("%ld", &c);
    }
    return (list);
}

struct cnt * sortlist(struct cnt * list) {
    struct cnt *f1, *f2, *lst;
    int n = len(list->next);
    for (int i = n-1; i >= 0; i--) {
        lst = list;
        for (int j = 0; j < i; j++) {
            if ((lst->next->count < lst->next->next->count) || (lst->next->count == lst->next->next->count && lst->next->num > lst->next->next->num)) {
                f1 = lst->next;
                lst->next = f1->next;
                f1->next = f1->next->next;
                lst->next->next = f1;
            }
            lst = lst->next;
        }
    }
    return list->next;
}

struct cnt * dellist(struct cnt *list)
{
    struct cnt *p = list;
    while (p != NULL)
    {
        list = p;
        p = list->next;
        free(list);
    }
    return (list);
}


int main() {

    struct cnt *list = (struct cnt *)malloc(sizeof(struct cnt));
    list->num = 0;
    list->count = 0;
    list->next = NULL;

    list->next = makelist(list->next);
    printlist(list->next);
    list->next = sortlist(list);
    printlist(list->next);
    printf("\n");

    list = dellist(list);
}
