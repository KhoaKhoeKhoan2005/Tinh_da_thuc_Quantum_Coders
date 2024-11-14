#include <stdio.h>
#include <string.h>
#define MAX 100

int songuyen (const char* a) 
{
    int i = 0;
// Kiem tra dau am o dau
    if (a[0] == '-') 
	{
        i = 1;
    }
// Duyet qua tung ky tu de kiem tra co phai la so nguyen khong
    for (; a[i] != '\0'; i++) 
	{
        if (a[i] < '0' || a[i] > '9') 
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
	return; // Ðieu kien dung: het chuoi
    int ketthuc = batdau;
// Tim diem cuoi cua so hang hien tai cho den khi gap toan tu hoac het chuoi
    while (bieu_thuc[ketthuc] != '+' && bieu_thuc[ketthuc] != '-' &&
           bieu_thuc[ketthuc] != '*' && bieu_thuc[ketthuc] != '/' &&
           bieu_thuc[ketthuc] != '(' && bieu_thuc[ketthuc] != ')' && bieu_thuc[ketthuc] != '\0') 
		   {
       ketthuc++;
    }
// Trich xuat so hang hien tai
    if (ketthuc > batdau) 
	{
        char a[MAX];
        strncpy(a, &bieu_thuc[batdau], ketthuc - batdau);
        a[ketthuc - batdau] = '\0';
// Kiem tra neu la so nguyen va in ra
        if (songuyen(a)) 
		{
            printf("%s ", a);
        }
    }
// De quy den phan tiep theo cua bieu thuc
    kt_so_hang (bieu_thuc, ketthuc + 1);
}

int main() 
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

