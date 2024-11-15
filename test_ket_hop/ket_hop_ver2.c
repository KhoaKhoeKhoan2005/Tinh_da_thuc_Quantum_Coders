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
    // Kiểm tra dấu âm ở đầu
    if (b[0] == '-') {
        i = 1;
    }
    // Duyệt qua từng ký tự để kiểm tra có phải là số nguyên không
    for (; b[i] != '\0'; i++) {
        if (b[i] < '0' || b[i] > '9') {
            return 0; 
        }
    }
    return 1;
}

// Hàm đệ quy để tìm và in ra các số hạng trong biểu thức
int kt_so_hang(const char* bieu_thuc, int batdau) {
    if (bieu_thuc[batdau] == '\0') return 0; // Điều kiện dừng: hết chuỗi
    int ketthuc = batdau;
    // Tìm điểm cuối của số hạng hiện tại cho đến khi gặp toán tử hoặc hết chuỗi
    while (bieu_thuc[ketthuc] != '+' && bieu_thuc[ketthuc] != '-' &&
           bieu_thuc[ketthuc] != '*' && bieu_thuc[ketthuc] != '/' &&
           bieu_thuc[ketthuc] != '(' && bieu_thuc[ketthuc] != ')' && 
           bieu_thuc[ketthuc] != '\0') {
        ketthuc++;
    }
    // Trích xuất số hạng hiện tại
    if (ketthuc > batdau) {
        char b[MAX];
        strncpy(b, &bieu_thuc[batdau], ketthuc - batdau);
        b[ketthuc - batdau] = '\0';
        // Kiểm tra nếu là số nguyên và in ra
        if (songuyen(b)) {
            printf("%s ", b);
        }
    }
    // Đệ quy để xử lý phần tiếp theo của biểu thức
    kt_so_hang(bieu_thuc, ketthuc + 1);
}

int Vitri_ngoac(char* a, int m) {
    int dem = 1; // Dùng để đếm số lượng ngoặc mở
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
    return -1; // Khi không tìm thấy ngoặc đóng
}

// Hàm loại bỏ các ký tự khoảng trắng trong biểu thức
void khongKhoangTrang(char* a) {
    int i = 0, j = 0;
    while (a[i]) {
        if (!isspace(a[i])) {  // Nếu không phải khoảng trắng thì sao chép
            a[j++] = a[i];
        }
        i++;
    }
    a[j] = '\0';  // Kết thúc chuỗi
}

// Hàm kiểm tra tính hợp lệ của biểu thức (kiểm tra ngoặc tròn)
int kiemTraHople(char* a) {
    int balance = 0;  // Dùng để đếm số lượng ngoặc mở và đóng
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '(') {
            balance++;
        } else if (a[i] == ')') {
            balance--;
            if (balance < 0) return 0;  // Có ngoặc đóng mà không có ngoặc mở
        }
    }
    return balance == 0;  // Nếu balance cuối cùng là 0 thì ngoặc hợp lệ
}

// Hàm tính giá trị của biểu thức (chỉ các phép cộng và trừ)
int tinhGiaTri(char* a, int* n) {
    int S = 0, dau = 1;  // dau = 1 cho phép cộng, dau = -1 cho phép trừ
    while (a[*n] != '\0') {
        if (a[*n] == ' ') {  // Bỏ qua khoảng trắng
            (*n)++;
            continue;
        }
        if (a[*n] == '+' || a[*n] == '-') {  // Xử lý dấu cộng hoặc trừ
            dau = (a[*n] == '+') ? 1 : -1;
            (*n)++;
        }
        if (isdigit(a[*n])) {  // Xử lý số nguyên
            int so = 0;
            while (isdigit(a[*n])) {
                so = so * 10 + (a[*n] - '0');
                (*n)++;
            }
            S += dau * so;
        }
        if (a[*n] == '(') {  // Xử lý ngoặc mở
            (*n)++;
            S += dau * tinhGiaTri(a, n);  // Gọi đệ quy
        }
        if (a[*n] == ')') {  // Xử lý ngoặc đóng
            (*n)++;
            return S;
        }
    }
    return S;
}

// Hàm xử lý biểu thức trong hàm main
int main() {
    char a[MAX];
    printf("Nhap bieu thuc: ");
    fgets(a, sizeof(a), stdin);  
    a[strcspn(a, "\n")] = 0;  // Loại bỏ ký tự '\n' nếu có

    // Loại bỏ các ký tự trống trong biểu thức
    khongKhoangTrang(a);
    
    // Kiểm tra tính hợp lệ của biểu thức
    if (!kiemTraHople(a)) {
        printf("Bieu thuc khong hop le!\n");  
        return 1;
    }

    // Kiểm tra dấu toán học trong biểu thức
    printf("Thu tu cac phep toan: ");
    kt_dau(a);

    // Kiểm tra các số hạng trong biểu thức
    printf("\nCac so hang co trong bieu thuc la: ");
    kt_so_hang(a, 0);
    
    // Kiểm tra vị trí ngoặc trong biểu thức
    int i = 0;
    while (i < strlen(a)) {
        if (a[i] == '(') {
            int stop = Vitri_ngoac(a, i);
            int kq = tinhGiaTri(a + i + 1, &stop);
            // Thay biểu thức thành kết quả
            printf("%d", kq);
            i += stop;  // Tiến lên sau khi thay
        } else {
            i++;
        }
    }

    // Tính giá trị cuối cùng của biểu thức
    int n = 0;
    int S = tinhGiaTri(a, &n);  
    printf("\nKet qua cua bieu thuc la: %d\n", S);

    return 0;
}
