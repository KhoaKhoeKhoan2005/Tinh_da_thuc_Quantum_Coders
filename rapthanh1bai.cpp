#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100
#define MAX_LEN 100

int kt_dau(char *a) {
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '+') printf("1 ");
        if (a[i] == '-') printf("2 ");
        if (a[i] == '*') printf("3 ");
        if (a[i] == '/') printf("4 ");
    }
}

int songuyen(const char* b) {
    int i = 0;
    // Ki?m tra d?u �m ? d?u
    if (b[0] == '-') {
        i = 1;
    }
    // Duy?t qua t?ng k� t? d? ki?m tra c� ph?i l� s? nguy�n kh�ng
    for (; b[i] != '\0'; i++) {
        if (b[i] < '0' || b[i] > '9') {
            return 0; 
        }
    }
    return 1;
}

// H�m d? quy d? t�m v� in ra c�c s? h?ng trong bi?u th?c
int kt_so_hang(const char* bieu_thuc, int batdau) {
    if (bieu_thuc[batdau] == '\0') return 0; // �i?u ki?n d?ng: h?t chu?i
    int ketthuc = batdau;
    // T�m di?m cu?i c?a s? h?ng hi?n t?i cho d?n khi g?p to�n t? ho?c h?t chu?i
    while (bieu_thuc[ketthuc] != '+' && bieu_thuc[ketthuc] != '-' &&
           bieu_thuc[ketthuc] != '*' && bieu_thuc[ketthuc] != '/' &&
           bieu_thuc[ketthuc] != '(' && bieu_thuc[ketthuc] != ')' && 
           bieu_thuc[ketthuc] != '\0') {
        ketthuc++;
    }
    // Tr�ch xu?t s? h?ng hi?n t?i
    if (ketthuc > batdau) {
        char b[MAX];
        strncpy(b, &bieu_thuc[batdau], ketthuc - batdau);
        b[ketthuc - batdau] = '\0';
        // Ki?m tra n?u l� s? nguy�n v� in ra
        if (songuyen(b)) {
            printf("%s ", b);
        }
    }
    // �? quy d? x? l� ph?n ti?p theo c?a bi?u th?c
    kt_so_hang(bieu_thuc, ketthuc + 1);
}

int Vitri_ngoac(char* a, int m) {
    int dem = 1; // D�ng d? d?m s? lu?ng ngo?c m?
    for (int i = m + 1; i < strlen(a); i++) {
        if (a[i] == '(') {
            dem++;
        } else if (a[i] == ')') {
            dem--;
            if (dem == 0) {
                return i;
            }
        }
    }
    return -1; // Khi kh�ng t�m th?y ngo?c d�ng
}

// H�m lo?i b? c�c k� t? kho?ng tr?ng trong bi?u th?c
void khongKhoangTrang(char* a) {
    int i = 0, j = 0;
    while (a[i]) {
        if (!isspace(a[i])) {  // N?u kh�ng ph?i kho?ng tr?ng th� sao ch�p
            a[j++] = a[i];
        }
        i++;
    }
    a[j] = '\0';  // K?t th�c chu?i
}

// H�m ki?m tra t�nh h?p l? c?a bi?u th?c (ki?m tra ngo?c tr�n)
int kiemTraHople(char* a) {
    int balance = 0;  // D�ng d? d?m s? lu?ng ngo?c m? v� d�ng
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '(') {
            balance++;
        } else if (a[i] == ')') {
            balance--;
            if (balance < 0) return 0;  // C� ngo?c d�ng m� kh�ng c� ngo?c m?
        }
    }
    return balance == 0;  // N?u balance cu?i c�ng l� 0 th� ngo?c h?p l?
}

// H�m t�nh gi� tr? c?a bi?u th?c (ch? c�c ph�p c?ng v� tr?)

int Tinh(char *a) {
    int numbers[100], numbers_count = 0;
    char operators[100];
    int operators_count = 0;
    char temp[100] = "";
    int temp_index = 0;

    for (int i = 0; i < strlen(a); ++i) {
        if (isdigit(a[i])) {
            temp[temp_index++] = a[i];
        } else {
            temp[temp_index] = '\0';
            numbers[numbers_count++] = atoi(temp);
            operators[operators_count++] = a[i];
            temp_index = 0;
        }
    }

    if (temp_index > 0) {
        temp[temp_index] = '\0';
        numbers[numbers_count++] = atoi(temp);
    }

    for (int i = 0; i < operators_count; ++i) {
        if (operators[i] == '*' || operators[i] == '/') {
            int left = numbers[i];
            int right = numbers[i + 1];
            int result = (operators[i] == '*') ? (left * right) : (left / right);
            numbers[i] = result;

            for (int j = i + 1; j < numbers_count - 1; ++j) {
                numbers[j] = numbers[j + 1];
            }
            numbers_count--;

            for (int j = i; j < operators_count - 1; ++j) {
                operators[j] = operators[j + 1];
            }
            operators_count--;
            --i;
        }
    }

    int result = numbers[0];
    for (int i = 0; i < operators_count; ++i) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '-') {
            result -= numbers[i + 1];
        }
    }

    return result;
}

void Thay_The(char *a) {
    int start, end;
    char buffer[100];

    while ((start = strrchr(a, '(') - a) >= 0) {
        char *end_ptr = strchr(a + start, ')');
        if (!end_ptr) break;
        
        end = end_ptr - a;
        char subExpr[100];
        strncpy(subExpr, a + start + 1, end - start - 1);
        subExpr[end - start - 1] = '\0';

        int value = Tinh(subExpr);
        sprintf(buffer, "%d", value);

        memmove(a + start + strlen(buffer), a + end + 1, strlen(a) - end);
        memcpy(a + start, buffer, strlen(buffer));
    }
}

// H�m x? l� bi?u th?c trong h�m main
int main() {
     char a[100];
    printf("Nhap bieu thuc: ");
    fgets(a, sizeof(a), stdin);  
    a[strcspn(a, "\n")] = 0;  // Lo?i b? k� t? '\n' n?u c�

    // Lo?i b? c�c k� t? tr?ng trong bi?u th?c
    khongKhoangTrang(a);
    
    // Ki?m tra t�nh h?p l? c?a bi?u th?c
    if (!kiemTraHople(a)) {
        printf("Bieu thuc khong hop le!\n");  
        return 1;
    }

    // Ki?m tra d?u to�n h?c trong bi?u th?c
    printf("Thu tu cac phep toan: ");
    kt_dau(a);

    // Ki?m tra c�c s? h?ng trong bi?u th?c
    printf("\nCac so hang co trong bieu thuc la: ");
    kt_so_hang(a, 0);
    Thay_The(a);
    int result = Tinh(a);
    printf("Gia tri cua bieu thuc la: %d\n", result);

    return 0;
}
