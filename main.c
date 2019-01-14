#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *prefixMaxim(int n, ...) {
    char *sir, *common = NULL;
    va_list siruri;
    va_start(siruri, n);
    for (int i = 0; i < n; i++) {
        sir = va_arg(siruri, char*);
        if (common == NULL) {
            common = malloc((strlen(sir) + 1) * sizeof(char));
            strcpy(common, sir);
        } else {
            int j = 0;
            while (j < strlen(common) && j < strlen(sir) && common[j] == sir[j])
                j++;
            if (j < strlen(common) && j < strlen(sir))
                strcpy(common + j, common + (strlen(common)));
            else if (j >= strlen(sir))
                strcpy(common, sir);
        }

    }

    va_end(siruri);
    return common;
}

char *prefixMaximNull(char *s, ...) {
    char *sir, *common = NULL;
    va_list siruri;
    if (s == NULL) {
        common = malloc(sizeof(char));
        strcpy(common, "");
        return common;
    }
    common = malloc(strlen(s) + 1);
    strcpy(common, s);
    va_start(siruri, s);
    while ((sir = va_arg(siruri, char*)) != NULL) {
        int j = 0;
        while (j < strlen(common) && j < strlen(sir) && common[j] == sir[j])
            j++;
        if (j < strlen(common) && j < strlen(sir))
            strcpy(common + j, common + (strlen(common)));
        else if (j >= strlen(sir))
            strcpy(common, sir);
    }

    va_end(siruri);
    return common;
}


int numarAparitii(int x, int nr, ...) {
    int numarAparitii = 0;
    va_list sir;
    va_start(sir, nr);
    for (int i = 0; i < nr; i++) {
        int number = va_arg(sir, int);
        if (number == x)
            numarAparitii++;
    }
    va_end(sir);
    return numarAparitii;
}

int numarAparitiiPanaLa0(int x, ...) {
    int numarAparitii = 0;
    va_list sir;
    va_start(sir, x);
    int number;
    while ((number = va_arg(sir, int)) != 0) {
        if (number == x)
            numarAparitii++;
    }
    va_end(sir);
    return numarAparitii;
}


int cmpIntreg(const void *a, const void *b) {
    int va = *(int *) a;
    int vb = *(int *) b;
    if (va == vb)
        return 0;
    else return -1;
}

int cmpSiruri(const void *a, const void *b) {
    return strcmp(*(char **) a, *(char **) b);
}

int
comparaVectori(const void *vector1, const void *vector2, int nrElementeVector1, int nrElementeVector2, int dimensiune,
               int (*cmp)(const void *, const void *)) {

    if (nrElementeVector1 != nrElementeVector2)
        return -1;
    for (int i = 0; i < nrElementeVector1; i++) {
        char *a = (char *) vector1 + i * dimensiune;
        char *b = (char *) vector2 + i * dimensiune;
        if (cmp(a, b) != 0)
            return -1;
    }
    return 1;
}

int cmpIntegers(const void *a, const void *b) {
    int va = *(int *) a;
    int vb = *(int *) b;
    if (va == vb)
        return 0;
    else return -1;
}

int cmpStrings(const void *a, const void *b) {
    return strcmp(*(char **) a, (char *) b);
}

void inlocuire(const void *vector, const void *x, const void *y, int nrElementeVector, int dimensiune,
               int(*cmp)(const void *, const void *)) {
    for (int i = 0; i < nrElementeVector; i++) {
        char *a = (char *) vector + i * dimensiune;
        if (cmp(a, x) == 0)
            memcpy(a, y, dimensiune);
    }
}

int max(int a, int b) {
    int max = a > b ? a : b;
    return max;
}

int findMinRec(int vector[], int n) {
    if (n == 1)
        return vector[0];
    return max(vector[n - 1], findMinRec(vector, n - 1));
}

int rev(int n, int temp) {
    if (n == 0)
        return temp;
    temp = (temp * 10) + (n % 10);
    return rev(n / 10, temp);
}

int main() {
    char *firstCommonSuffix = prefixMaxim(4, "anananassss", "ananas", "ananana", "anana");
    char *secondCommonSuffix = prefixMaximNull("abadd", "abac", "aba", NULL);
    printf("%s %s\n", firstCommonSuffix, secondCommonSuffix);
    int numarAparitii1 = numarAparitii(1, 4, 1, 2, 1, 3);
    int numarAparitii2 = numarAparitiiPanaLa0(1, 1, 2, 1, 3, 0);
    printf("%d %d \n", numarAparitii1, numarAparitii2);

    int a[] = {1, 3, 3, 4, 5}, b[] = {1, 2, 3, 4, 5};
    char *d[3] = {"ana", "are", "mere"};
    char *e[3] = {"ana", "are", "mere"};
    int x = comparaVectori(a, b, 5, 5, sizeof(int), cmpIntreg);
    int y = comparaVectori(d, e, 3, 3, sizeof(char *), cmpSiruri);
    printf("%d %d\n", x, y);
    int var1 = 3, var2 = 10;
    inlocuire(a, &var1, &var2, 5, sizeof(int), cmpIntegers);
    for (int i = 0; i < 5; i++)
        printf("%d ", a[i]);
    return 0;
}