#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100
// Hàm loai bo cac ky tu trong trong bieu thuc
void khongKhoangTrang(char* a) {
    int i = 0, j = 0;
    while (a[i]) {
        if (!isspace(a[i])) {  // Neu khong phai khoang trang thì sao chep
            a[j++] = a[i];
        }
        i++;
    }
    a[j] = '\0';  // Ket thuc chuoi
}
// Ham kiem tra tinh hop le cua bieu thuc (kiem tra ngoac tron)
int kiemTraHople(char* a) {
    int balance = 0;  // Dung de dem so luong ngooc mo và dong
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '(') {
            balance++;
        } else if (a[i] == ')') {
            balance--;
            if (balance < 0) return 0;  // Co ngoac dong ma khong co ngoac mo
        }
    }
    return balance == 0;  // Neu balance cuoi cung la 0 thi ngoac hop le
}
// Ham tinh gia tri cua bieu thuc (chi phep cong, tru)
int tinhGiaTri(char* a, int* n) {
    int S = 0, dau = 1;  // dau = 1 cho +, dau = -1 cho -
    while (a[*n] != '\0') {
        if (a[*n] == ' ') {  // Bo qua khoang trang
            (*n)++;
            continue;
        }
        if (a[*n] == '+' || a[*n] == '-') {  // Xu ly dau + hoac -
            dau = (a[*n] == '+') ? 1 : -1;
            (*n)++;
        }
        if (isdigit(a[*n])) {  // Xu ly so nguyen
            int so = 0;
            while (isdigit(a[*n])) {
                so = so * 10 + (a[*n] - '0');
                (*n)++;
            }
            S += dau * so;
        }
        if (a[*n] == '(') {  // Xu ly ngoac mo
            (*n)++;
            S += dau * tinhGiaTri(a, n);  // Goi lai ham de quy voi các tham so dung
        }
        if (a[*n] == ')') {  // Xu ly ngoac dong
            (*n)++;
            return S;
        }
    }
    return S;
}
int main() {
    char a[100];
    printf("Nhap bieu thuc : ");
    fgets(a, 100 , stdin);  
    a[strcspn(a, "\n")] = 0;  // Loai bo ky tu '\n' neu co
    // Khu cac ky tu trang trong bieu thuc
    khongKhoangTrang(a);
    // Kiem tra tinh hop le cua bieu thuc
    if (!kiemTraHople(a)) {
        printf("Bieu thuc khong hop le !\n");  
        return 1;
    }
    int n = 0;
    int S = tinhGiaTri(a, &n);  
    printf("K?t qu? c?a bi?u th?c là: %d\n", S);
    return 0;
}
