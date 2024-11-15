#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

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

// Hàm kiểm tra số nguyên
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

// Hàm xác định vị trí phép toán trong biểu thức (chỉ các phép toán +, -, *, /)
void xacDinhPhepToan(char* a) {
    printf("Thu tu cac phep toan: ");
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/') {
            printf("%c ", a[i]);
        }
    }
    printf("\n");
}

// Hàm kiểm tra các số hạng trong biểu thức
void kiemTraSoHang(char* a) {
    printf("Cac so hang co trong bieu thuc la: ");
    int i = 0;
    while (a[i] != '\0') {
        if (isdigit(a[i]) || (a[i] == '-' && isdigit(a[i + 1]))) { // Kiểm tra số nguyên
            int start = i;
            while (isdigit(a[i]) || a[i] == '-') {
                i++;
            }
            char num[MAX];
            strncpy(num, &a[start], i - start);
            num[i - start] = '\0';
            printf("%s ", num);
        } else {
            i++;
        }
    }
    printf("\n");
}

// Hàm tìm vị trí ngoặc đóng tương ứng
int vitriNgoacDong(char* a, int m) {
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

    // Xác định các phép toán trong biểu thức
    xacDinhPhepToan(a);

    // Kiểm tra các số hạng trong biểu thức
    kiemTraSoHang(a);
    
    // Kiểm tra vị trí ngoặc trong biểu thức
    printf("\nVị trí ngoặc đóng trong biểu thức: \n");
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '(') {
            int stop = vitriNgoacDong(a, i);
            printf("Ngoac mo o vi tri %d co ngoac dong o vi tri %d\n", i, stop);
        }
    }

    // Tính giá trị của biểu thức
    int n = 0;
    int S = tinhGiaTri(a, &n);  
    printf("\nKet qua cua bieu thuc la: %d\n", S);

    return 0;
}
