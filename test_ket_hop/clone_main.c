#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100
#define MAX_LEN 100


int kt_dau(char *a) 
{
	for (int i = 0; a[i] != '\0'; i++) 
	{
        if (a[i] == '+') printf("1 ");
        if (a[i] == '-') printf("2 ");
        if (a[i] == '*') printf("3 ");
        if (a[i] == '/') printf("4 ");
    }
}


int songuyen (const char* b) 
{
    int i = 0;
// Kiem tra dau am o dau
    if (b[0] == '-') 
	{
        i = 1;
    }
// Duyet qua tung ky tu de kiem tra co phai la so nguyen khong
    for (; b[i] != '\0'; i++) 
	{
        if (b[i] < '0' || b[i] > '9') 
		{
            return 0; 
        }
    }
    return 1;
}
// Ham de quy de tim va in ra cac so nguyen trong bieu thuc
int kt_so_hang (const char* bieu_thuc, int batdau) 
{
    if (bieu_thuc[batdau] == '\0')
	return 0; // �ieu kien dung: het chuoi
    int ketthuc = batdau;
// Tim diem cuoi cua so hang hien tai cho den khi gap toan tu hoac het chuoi
    while (bieu_thuc[ketthuc] != '+' && bieu_thuc[ketthuc] != '-' &&
           bieu_thuc[ketthuc] != '*' && bieu_thuc[ketthuc] != '/' &&
           bieu_thuc[ketthuc] != '(' && bieu_thuc[ketthuc] != ')' && 
           bieu_thuc[ketthuc] != '\0') 
		   {
       ketthuc++;
    }
// Trich xuat so hang hien tai
    if (ketthuc > batdau) 
	{
        char b[MAX];
        strncpy(b, &bieu_thuc[batdau], ketthuc - batdau);
        b[ketthuc - batdau] = '\0';
// Kiem tra neu la so nguyen va in ra
        if (songuyen(b)) 
		{
			printf("%s ", b);
        }
    }
// De quy den phan tiep theo cua bieu thuc
    kt_so_hang (bieu_thuc, ketthuc + 1);
}
int Vitri_ngoac(char* a, int m ) {
    int dem = 1; // Dung dem so luong ngoac mo ah
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
    return -1; // Day la khi k tim duoc ngoac dong
}//Doi ham tinh toan bieu thuc
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
//câu lệnh cũ ko nỡ xóa nên để comment
/*int ktdaumain() 
{
    char a[100];
    printf("Nhap bieu thuc ");
	gets(a);
    printf("\nbieu thuc sau khi nhap: ");
    puts(a);
    printf("\nthu tu cac phep toan: ");
    kt_dau(a);
}

int main_kt_so_hang() 
{
    char bieu_thuc[MAX];
    printf("Nhap bieu thuc bat ky: ");
    fgets(bieu_thuc, sizeof(bieu_thuc), stdin);
// Loai bo ky tu xuong dong o cuoi chuoi neu co
    bieu_thuc[strcspn(bieu_thuc, "\n")] = '\0';
    printf("Cac so hang co trong bieu thuc la: ");
    kt_so_hang(bieu_thuc, 0);
    printf("\n");
    return 0;
}

int main_vi_tri_ngoac() {
    char a[] = "3 + (4 * 5 - 2)";// vd thu 1 bieu thuc
    int i = 0;

    while (i < strlen(a)) {
        if (a[i] == '(') {
            int stop = Vitri_ngoac(a, i);
            int kq = Tinh(a, i + 1, stop - 1);
            // thay bieu thuc thanh ket qua
            final(a + i, a + stop + 1, strlen(a) - stop);
            // Dua ket qua vao tri dau ngoac mo
            printf(a + i, "%d", kq);
            // xuat ra chu so cuoi
            i += strlen(sprintf(NULL, "%d", kq));
        } else {
            i++;
        }
    }

    // ket qua cuoi
    printf("Ket qua: %s\n", a);
    return 0;
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
    printf("Ket qua cua bieu thuc la: %d\n", S);
    return 0;
}*/



// Các hàm hỗ trợ (giả sử bạn đã định nghĩa các hàm này trước đó)


int main() {
    char a[MAX];
    printf("Nhap bieu thuc: ");
    fgets(a, sizeof(a), stdin);  
    a[strcspn(a, "\n")] = 0;  // Loai bo ky tu '\n' nếu có

    // Khu các ký tự trống trong biểu thức
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
    int Tinh(char* a, int start, int end);
    void final(char* start, char* end, int len);


    while (i < strlen(a)) {
        if (a[i] == '(') {
            int stop = Vitri_ngoac(a, i);
            int kq = Tinh(a, i + 1, stop - 1);
            // Thay biểu thức thành kết quả
            final(a + i, a + stop + 1, strlen(a) - stop);
            // Đưa kết quả vào vị trí dấu ngoặc mở
            printf(a + i, "%d", kq);
            // Xử lý kết quả sau khi thay
            char temp[100];  // Tạo mảng đủ lớn
            snprintf(temp, sizeof(temp), "%d", kq);  // Chuyển số nguyên thành chuỗi
            i += strlen(temp);  // Tính độ dài chuỗi

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
