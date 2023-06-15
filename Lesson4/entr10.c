#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

char * readfile(int f1) {
    int fsize = 32;
    int newsize = 32;
    char * buf = (char *)calloc(fsize, sizeof(char));
    int check;
    int realsize = 0;
    while(1) {
        check = read(f1, buf + fsize - newsize, newsize);
        realsize += check;
        if (check == 0) { break; }
        else {
            fsize += newsize;
            buf = (char *)realloc(buf, fsize);
        }
    }
    buf[realsize - 1] = '\0';
    return buf;
}

int rfind(char * buf, int * len) {
    int i;
    int end;
    for (i = strlen(buf) - 1; i >= 0; i--) {
        if (buf[i] != '\n' && buf[i] != '\0' && buf[i] != '\t' && buf[i] != ' ') { 
            end = i;
            break; 
    }
    }
    for (i - 1; i >= 0; i--) {
        if (buf[i] == '\n' || buf[i] == '\0' || buf[i] == '\t' || buf[i] == ' ') { break; }
    }
    *len = end - i;
    return i + 1;
}

int lfind(char * buf, int * len) {
    int i;
    int start;
    for (i = 0; i < strlen(buf); i++) {
        if (buf[i] != '\n' && buf[i] != '\0' && buf[i] != '\t' && buf[i] != ' ') { 
            start = i;
            break; 
        }
    }
    for (i + 1; i < strlen(buf); i++) {
        if (buf[i] == '\n' || buf[i] == '\0' || buf[i] == '\t' || buf[i] == ' ') { break; }
    }
    *len = i - start;
    return start;

}

void copyfile(int f2, char * buf) {
    int llen;
    int rpos = rfind(buf, &llen);
    int flen; //size of the first word
    int lpos = lfind(buf, &flen);

    write(f2, buf, lpos); // trash from the start
    write(f2, buf + rpos, llen); //last word
    write(f2, buf + lpos + llen + 1, rpos - lpos - flen); // the middle part
    write(f2, buf + lpos, flen); //first word
    write(f2, buf + rpos + llen, strlen(buf) - rpos - llen); // trash from the end
}

void casedir(char * dirname) {
    char * name = NULL;
    int namesize = 256;
    struct dirent * info;
    struct stat st;
    DIR * d = opendir(dirname);
    chdir(dirname);
    while ((info = readdir(d))) {
        lstat(info->d_name, &st);
        if (S_ISLNK(st.st_mode)) {
            printf("Link name: %s\nLink ID: %lu\n", info->d_name, st.st_ino);
            stat(info->d_name, &st);
            name = (char*)calloc(sizeof(char), namesize);
            readlink(info->d_name, name, namesize);
            //name[namesize] = '\0';
            printf("File name: %s\nFile ID: %lu\n\n", name, st.st_ino);
            free(name);
            name = NULL;
        }
    }
    symlink("filename", "fsymlinkname");
    closedir(d);
}

int casereg(char * filename, struct stat p) { 
    int size = strlen(filename);
    char * name = (char *)calloc(size + 4, sizeof(char));
    char * new = "new";
    memcpy(name, filename, size);
    memcpy(name + size, new, strlen(new));
    int f2 = open(name, O_CREAT | O_EXCL | O_WRONLY, p.st_mode);
    if (errno == EEXIST) {
        printf("%s%c%s%c%s", "File ", '"', name, '"', " is already exists. Would you like to change it? [y/n] ");
        char c;
        scanf("%c", &c);
        if (c == 'n') { return 0; }
        f2 = open(name, O_CREAT | O_TRUNC | O_WRONLY, p.st_mode);
    }
    int f1 = open(filename, O_RDONLY);
    char * buf = readfile(f1);
    copyfile(f2, buf);
    free(name);
    free(buf);
    close(f1);
    close(f2);
}


int main(int argc, char * argv[]) {
    
    struct stat p;
    stat(argv[1], &p);
    if (S_ISDIR(p.st_mode)) {
        casedir(argv[1]);
    }
    else if (S_ISREG(p.st_mode)) {
        casereg(argv[1], p);
    }

    return 0;
}