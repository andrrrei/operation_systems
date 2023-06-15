#include <stdio.h>
#include <stdlib.h>

const int elem = 8;
const int matrsize = 50;

void printmatr(int matr[matrsize][matrsize], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void makematrconst(int matr[matrsize][matrsize], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matr[i][j] = elem;
        }
    }
}

void makematrrand(int matr[matrsize][matrsize], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matr[i][j] = rand() % 100;
        }
    }
}

void mult(int matr1[matrsize][matrsize], int m1, int n1, int matr2[matrsize][matrsize], int n2) {
    int res[50][50] = {0};
    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n2; j++) {
            for (int k = 0; k < n1; k++) {
                res[i][j] += matr1[i][k]*matr2[k][j];
            }
        }
    }
    printf("%s\n", "Multiplication: ");
    printmatr(res, m1, n2);
}

void transp(int matr[matrsize][matrsize], int m, int n) {
    int res[matrsize][matrsize];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res[i][j] = matr[j][i];
        }
    }
    printmatr(res, n, m);
}

int main() {

    int matr1[matrsize][matrsize];
    int matr2[matrsize][matrsize];
    int m1, n1, m2, n2;
    printf("%s\n", "Enter the size of the 1st matrix:");
    printf("%s", "M1: ");
    scanf("%d", &m1);
    printf("%s", "N1: ");
    scanf("%d", &n1);
    printf("%s\n", "Enter the size of the 2nd matrix:");
    printf("%s", "M2: ");
    scanf("%d", &m2);
    printf("%s", "N2: ");
    scanf("%d", &n2);
    printf("\n");

    makematrconst(matr1, m1, n1);
    makematrrand(matr2, m2, n2);
    printf("%s\n", "The 1st matrix:");
    printmatr(matr1, m1, n1);
    printf("%s\n", "The 2nd matrix:");
    printmatr(matr2, m2, n2);

    if (n1 != m2) {
        printf("%s\n", "Matrix multiplication can`t be performed because you`ve entered incorrect dimensions");
        printf("\n");
    }
    else {
        mult(matr1, m1, n1, matr2, n2);
    }

    printf("%s\n", "Transportation of the 1st matrix:");
    transp(matr1, m1, n1);
    printf("%s\n", "Transportation of the 2nd matrix:");
    transp(matr2, m2, n2);

}