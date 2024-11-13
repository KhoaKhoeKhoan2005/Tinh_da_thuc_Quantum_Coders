#include <stdio.h>
#include <ctype.h>
#include <string.h>
// ham xac dinh vi tri cuoi cung cua so hang
int chusoovitricuoicung(char *a, int n) {
    int i = n;
    while (isdigit(a[i])) { // kiem tra neu la chu so
        i++;
    }
    return i - 1; // tra ve vi tri cuoi cung cua so hang
}

int main() {
    char a[100];
    printf("Bieu thuc : %s\n", a);
    gets(a);
    printf("Vi tri cuoi cung cua cac so hang :\n");
    for (int i = 0; i < strlen(a); i++) {
        if (isdigit(a[i])) { // khi gap so hang
            int ketthuc = chusoovitricuoicung(a, i);
            printf("so hang bat dau tai %d va ket thuc tai %d\n", i, ketthuc);
            i = ketthuc; // bo qua cac chu so da duyet 
        }
    }

    return 0;
}
