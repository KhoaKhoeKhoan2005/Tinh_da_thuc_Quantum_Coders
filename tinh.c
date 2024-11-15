#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50

float b[MAX_SIZE], c[MAX_SIZE], d[MAX_SIZE];
float tinh();
int length(float a[]);
float tinhngoac(int i, int j);
float congtru(int i, int j);
float nhanchia(int i, int j);

int main() {
    int n, m;

    // Nhap mang b
    printf("Nhap so phan tu mang b: ");
    scanf("%d", &n);
    printf("\nNhap mang b: ");
    for (m = 0; m < n; m++) {
        printf("b[%d]= ", m);
        scanf("%f", &b[m]);
    }

    // Nhap mang c
    printf("\nNhap mang c (1,2,3,4): ");
    for (m = 0; m < n - 1; m++) {
        printf("c[%d]= ", m);
        scanf("%f", &c[m]);
    }

    // Nhap mang d
    printf("\nNhap mang d: ");
    for (m = 0; m < n; m++) {
        printf("d[%d]= ", m);
        scanf("%f", &d[m]);
    }

    // Tinh ket qua
    tinh();
    printf("Ket qua: %f\n", b[0]);

    return 0;
}

float tinh() {
    int max = d[0];
    for (int i = 0; i < length(d); i++) {
        if (d[i] > max) {
            max = d[i];
        }
    }

    // X? lý các ph?n t? theo giá tr? c?a d[i]
    for (; max >= 0; max--) {
        for (int i = 0; i < length(b); i++) {
            if (d[i] == max) {
                for (int j = i; j < length(b); j++) {
                    if (d[j] != max) {
                        tinhngoac(i, j);
                        break;
                    } else if (j == length(b) - 1) { // S?a so sánh j = length(b)
                        tinhngoac(i, j);
                        break;
                    }
                }
            }
        }
    }

    return b[0];  // Tr? v? k?t qu? cu?i cùng sau khi tính toán
}

int length(float a[]) {
    int len = 0;
    while (len < MAX_SIZE && a[len] != 0) {
        len++;
    }
    return len;
}

float tinhngoac(int i, int j) {
    int k = i + 1;
    float kqua = congtru(i, j);
    b[i] = kqua;
    d[i] = d[i] - 1;

    // Di chuy?n các ph?n t? trong m?ng b
    for (; k < length(b) - (j - i); k++) {
        b[k] = b[k + j - i];
    }
    if (k < length(b)) {
        for (k = length(b) - (j - i); k < length(b); k++) {
            b[k] = 0;
        }
    }

    // Di chuy?n các ph?n t? trong m?ng c
    for (; k < length(c) - (j - i); k++) {
        c[k] = c[k + j - i];
    }
    if (k < length(c)) {
        for (k = length(c) - (j - i); k < length(c); k++) {
            c[k] = 0;
        }
    }

    // Di chuy?n các ph?n t? trong m?ng d
    for (; k < length(d) - (j - i); k++) {
        d[k] = d[k + j - i];
    }
    if (k < length(d)) {
        for (k = length(d) - (j - i); k < length(d); k++) {
            d[k] = 0;
        }
    }

    return kqua;
}

float congtru(int i, int j) {
    float kq = nhanchia(i, j);
    int k = i;
    while (k < j) {
        float temp = nhanchia(i, j);
        if (c[i] == 1) {
            kq += temp;
            k++;
        } else if (c[i] == 2) {
            kq -= temp;
            k++;
        }
    }
    return kq;
}
float nhanchia(int i, int j) {
    float kq = 1;
    int k = i;
    while (k < j) {
        if (c[k] == 1 || c[k] == 2) {
            kq = b[k];
            i = i + 1;
            break;
        } else if (c[k] == 3) {
            kq = b[k];
            while ((k < j) && c[k] == 3) {
                kq *= b[k + 1];
                i = i + 1;
            }
            break;
        } else if (c[k] == 4) {
            kq = b[k];
            while ((k < j) && c[k] == 4) {
                kq /= b[k + 1];
                i = i + 1;
            }
            break;
        }
    }
    return kq;
}
