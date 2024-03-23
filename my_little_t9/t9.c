#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Structure for T9 node
struct T9 {
    struct T9 *arr[26];
    int counter;
    bool visited;
};

// Structure for list node
struct list {
    char *s;
    int len;
    int freq;
    struct list *next;
};

// Function to read a single word from stdin
void readword(char **word) {
    int str_size = 12;
    int newsize = 4;
    int i = 0;
    char *s = (char *)malloc(str_size);
    char c = getchar();
    while (c != ' ' && c != '\n') {
        if (i >= str_size - 1) {
            str_size += newsize;
            s = (char *)realloc(s, str_size);
        }
        s[i] = c;
        i++;
        c = getchar();
    }
    s[i] = '\0';
    *word = s;
}

// Function to read a single word from file
void readfile(FILE *f, char **word, int *tmp) {
    int str_size = 12;
    int newsize = 4;
    int i = 0;
    char *s = (char *)malloc(str_size);
    char c;
    int a = fscanf(f, "%c", &c);
    while (c != ' ' && c != '\n' && a != -1) {
        if (i >= str_size - 1) {
            str_size += newsize;
            s = (char *)realloc(s, str_size);
        }
        s[i] = c;
        i++;
        a = fscanf(f, "%c", &c);
    }
    s[i] = '\0';
    if (c == '\n' || a == -1) {
        *tmp = 0;
    }
    *word = s;
}

// Function to add a word to the T9 dictionary
void add(struct T9 *dict, char *s) {
    int i = 0;
    char c = s[i];
    while (1) {
        dict->arr[c - 'a'] = (struct T9 *)malloc(sizeof(struct T9));
        dict = dict->arr[c - 'a'];
        dict->counter = 0;
        dict->visited = false;
        for (int q = 0; q < 26; q++) {
            dict->arr[q] = NULL;
        }
        if (s[i + 1] == '\0') {
            dict->counter++;
            break;
        }
        i++;
        c = s[i];
    }
}

// Function to insert a word into the T9 dictionary
void insert(struct T9 *dict, char *s) {
    int i = 0;
    while (1) {
        if (dict->arr[s[i] - 'a'] != NULL) {
            dict = dict->arr[s[i] - 'a'];
            if (s[i + 1] == '\0') {
                dict->counter++;
                break;
            }
            i++;
        } else {
            add(dict, s + i);
            break;
        }
    }
}

// Function to construct the T9 dictionary from a file
struct T9 *maketree(FILE *f, struct T9 *dict, int *height) {
    int tmp = 1;
    char *s;
    while (tmp) {
        readfile(f, &s, &tmp);
        if (strlen(s) > *height) {
            *height = strlen(s);
        }
        insert(dict, s);
        free(s);
        s = NULL;
    }
    return dict;
}

// Function to print the T9 dictionary
void printtree(struct T9 *dict) {
    for (int i = 0; i < 26; i++) {
        if (dict->arr[i] != NULL) {
            printf("%c %d\n", 'a' + i, dict->arr[i]->counter);
            printtree(dict->arr[i]);
        }
    }
}

// Function to calculate the length of a linked list
int len(struct list *lst) {
    int l = 0;
    while (lst != NULL) {
        l++;
        lst = lst->next;
    }
    return l;
}

// Function to sort a linked list based on frequency and length of strings
struct list *sortlist(struct list *lst1) {
    struct list *f1, *lst, *tmp;
    tmp = (struct list *)malloc(sizeof(struct list));
    tmp->next = lst1;
    int n = len(lst1);
    for (int i = n - 1; i >= 0; i--) {
        lst = tmp;
        for (int j = 0; j < i; j++) {
            if ((lst->next->freq < lst->next->next->freq) || 
                (lst->next->freq == lst->next->next->freq && lst->next->len > lst->next->next->len)) {
                f1 = lst->next;
                lst->next = f1->next;
                f1->next = f1->next->next;
                lst->next->next = f1;
            }
            lst = lst->next;
        }
    }
    struct list *p = tmp->next;
    free(tmp);
    return p;
}

// Function to print k elements of a linked list with a given prefix
void printlist(char *pref, struct list *lst, int k) {
    for (int p = 0; p < k; p++) { 
        printf("%s%s %d\n", pref, lst->s, lst->freq);
        lst = lst->next;
    }
}

// Function to append a new node to a linked list
struct list *append(struct list *lst, char *buf, int size, int fr, int preflen) {
    struct list *tmp = lst;
    lst = (struct list *)malloc(sizeof(struct list));
    lst->freq = fr;
    lst->len = size + preflen;
    lst->next = tmp;
    lst->s = (char *)calloc(size + 1, sizeof(char));
    memcpy(lst->s, buf, size);
    return lst;
}

// Function to delete a linked list
struct list *dellist(struct list *lst) {
    struct list *p = lst;
    while (p != NULL) {
        lst = p;
        p = lst->next;
        free(lst->s);
        free(lst);
    }
    return lst;
}

// Function to recursively traverse the tree and find relevant strings
struct list *go(struct T9 *dict, int *num, struct list *lst, char *buf, int bufsize, int preflen) {
    if (dict->counter != 0 && dict->visited == false) { 
        lst = append(lst, buf, bufsize, dict->counter, preflen);
        (*num)++;
    }
    dict->visited = true;
    for (int i = 0; i < 26; i++) {
        if (dict->arr[i] != NULL) {
            buf[bufsize] = i + 'a';
            bufsize++;
            lst = go(dict->arr[i], num, lst, buf, bufsize, preflen);
            buf[bufsize] = '\0';
            bufsize--;
        }
    }
    return lst;
}

// Function to search for relevant words in the tree
void search(struct T9 *dict, char *s, int k, int height) {
    int len = strlen(s);
    int i = 0;
    struct T9 **way = (struct T9 **)malloc(sizeof(struct T9 *) * len);
    way[0] = dict;
    for (i = 0; i < len; i++) {
        if (dict->arr[s[i] - 'a'] != NULL) {
            dict = dict->arr[s[i] - 'a'];
            way[i] = dict;
        }
        else { break; }
    } 
    
    struct list *lst = NULL;
    char *buf = NULL; // Buffer string
    char *pref = NULL;
    int k1, num, words; // k1 - number of the words to print, num - number of found words, words - number of remaining words
    words = k;
    printf("%s\n", "Perhaps you meant: ");
    while (words > 0 && i > 0) {
        char *pref = (char *)calloc(i + 1, sizeof(char));
        memcpy(pref, s, i);
        buf = (char *)calloc(height - i + 1, sizeof(char));
        num = 0;
    
        lst = go(way[i - 1], &num, lst, buf, 0, i); // Function that creates list of relevant strings with information of them
        
        way[i - 1]->visited = true;
        i--;
        if (num <= words) { k1 = num; }
        else { k1 = words; }
        lst = sortlist(lst);
        printlist(pref, lst, k1);

        lst = dellist(lst); // Preparing to next func call
        lst = NULL;
        free(pref);
        pref = NULL;
        free(buf);
        buf = NULL;

        words -= k1;
    }
    free(way);
}

// Function to recursively delete the tree
void deltree(struct T9 *dict) {
    for (int i = 0; i < 26; i++) {
        if (dict->arr[i] != NULL) {
            deltree(dict->arr[i]);
        }
    }
    free(dict);
}

// Main function
int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");

    struct T9 *dict = (struct T9 *)malloc(sizeof(struct T9));
    for (int q = 0; q < 26; q++) { dict->arr[q] = NULL; }
    int height = 0;
    maketree(f, dict, &height);

    char *str;
    printf("%s", "Enter the word you'd like to find: ");
    readword(&str);
    int k;
    printf("%s", "Enter the number of similar words: ");
    scanf("%d", &k);
    search(dict, str, k, height);

    deltree(dict);
    fclose(f);
    free(str);
}
