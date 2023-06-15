#include <stdio.h>
#include <stdlib.h>

struct tree {
    struct tree * left;
    struct tree * right;
    int val;
};

struct list {
    int val;
    struct list * next;
};

struct tree * insert(struct tree * tr, int n) {
    if (tr == NULL) {
        tr = (struct tree *)malloc(sizeof(struct tree));
        tr->val = n;
        tr->left = NULL;
        tr->right = NULL;
    }
    else {
        if (n < tr->val) { tr->left = insert(tr->left, n); }
        else { tr->right = insert(tr->right, n); }
    }
    return tr;
}

struct tree * createtree(FILE *f, struct tree * tr) {
    tr = (struct tree *)malloc(sizeof(struct tree));
    tr->val = 0;
    int num;
    while (feof(f) == 0) {
        fscanf(f, "%d", &num);
        tr = insert(tr, num);
    }
    return tr;
    
}

void printtree(struct tree * tr) {
    if (tr != NULL) {
        printf("%d\n", tr->val);
        printtree(tr->left);
        printtree(tr->right);
    }
}

int find(struct tree * tr, int n, int height) {
    if (tr == NULL) { return -1 * (height + 1); }
    else if (tr->val == n) { return 0; }
    else if (n > tr->val) {
        height += 1;
        return 1 + find(tr->right, n, height); 
    }
    else {
        height += 1;
        return 1 + find(tr->left, n, height); 
    }
}

void deletetree(struct tree * tr) {
    if (tr != NULL) {
        deletetree(tr->left); 
        deletetree(tr->right);
        free(tr);
    }
}

int main(int argc, char* argv[]) {

    struct tree *tr;
    tr = NULL;
    FILE *f;
    f = fopen(argv[1], "r");
    tr = createtree(f, tr);

    int num;
    printf("%s", "Enter the number you'd like to find: ");
    scanf("%d", &num);
    int len = find(tr, num, 0);
    printf("%s", "The length of the way: ");
    printf("%d\n", len);
    if (len == -1) {
        insert(tr, num);
    }
    printtree(tr);

    deletetree(tr);
    fclose(f);
}