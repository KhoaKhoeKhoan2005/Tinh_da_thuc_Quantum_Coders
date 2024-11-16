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
        if (a[i] == '+')
            printf("1 ");
        if (a[i] == '-')
            printf("2 ");
        if (a[i] == '*')
            printf("3 ");
        if (a[i] == '/')
            printf("4 ");
    }
}

int songuyen(const char *b)
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

int kt_so_hang(const char *bieu_thuc, int batdau)
{
    if (bieu_thuc[batdau] == '\0')
        return 0;
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
        // Kiem tra no la so nguyen va in ra
        if (songuyen(b))
        {
            printf("%s ", b);
        }
    }   
    kt_so_hang(bieu_thuc, ketthuc + 1);
}

int Vitri_ngoac(char *a, int m)
{
    int dem = 1; // Dong do dem so luong ngoac mo
    for (int i = m + 1; i < strlen(a); i++)
    {
        if (a[i] == '(')
        {
            dem++;
        }
        else if (a[i] == ')')
        {
            dem--;
            if (dem == 0)
            {
                return i;
            }
        }
    }
    return -1; // Khi khong tim thay ngoac dong
}

// Ham loai bo cac khoang trang trong bieu thuc
void khongKhoangTrang(char *a)
{
    int i = 0, j = 0;
    while (a[i])
    {
        if (!isspace(a[i]))
        { // Neu khong phai khoang trang thi sao chep
            a[j++] = a[i];
        }
        i++;
    }
    a[j] = '\0'; // Ket thuc chuoi
}

// Ham kiem tra tinh hop le cua bieu thuc (kiem tra ngoac tron)
int kiemTraHople(char *a)
{
    int canbang = 0; // so luong ngoac mo va dong
    for (int i = 0; a[i] != '\0'; i++)
    {
        if (a[i] == '(')
        {
            canbang++;
        }
        else if (a[i] == ')')
        {
            canbang--;
            if (canbang < 0)
                return 0; // Co ngoac dong ma khong co ngoac mo
        }
    }
    return canbang == 0; // Neu canbang cuoi cung la 0 thi ngoac hop le
}

// Ham tinh gia tri cua bieu thuc (chi cac phep cong va tru)

int Tinh(char *a)
{
    int so[100], so_dem = 0;
    char pheptinh[100];
    int pheptinh_dem = 0;
    char now[100] = "";
    int now_oday = 0;

    for (int i = 0; i < strlen(a); ++i)
    {
        if (isdigit(a[i]))
        {
            now[now_oday++] = a[i];
        }
        else
        {
            now[now_oday] = '\0';
            so[so_dem++] = atoi(now);
            pheptinh[pheptinh_dem++] = a[i];
            now_oday = 0;
        }
    }

    if (now_oday > 0)
    {
        now[now_oday] = '\0';
        so[so_dem++] = atoi(now);
    }

    for (int i = 0; i < pheptinh_dem; ++i)
    {
        if (pheptinh[i] == '*' || pheptinh[i] == '/')
        {
            int trai = so[i];
            int phai = so[i + 1];
            int ketqua = (pheptinh[i] == '*') ? (trai * phai) : (trai / phai);
            so[i] = ketqua;

            for (int j = i + 1; j < so_dem - 1; ++j)
            {
                so[j] = so[j + 1];
            }
            so_dem--;

            for (int j = i; j < pheptinh_dem - 1; ++j)
            {
                pheptinh[j] = pheptinh[j + 1];
            }
            pheptinh_dem--;
            --i;
        }
    }

    int ketqua = so[0];
    for (int i = 0; i < pheptinh_dem; ++i)
    {
        if (pheptinh[i] == '+')
        {
            ketqua += so[i + 1];
        }
        else if (pheptinh[i] == '-')
        {
            ketqua -= so[i + 1];
        }
    }

    return ketqua;
}

void Thay_The(char *a)
{
    int bat_dau, het;
    char bu_nhin[100];

    while ((bat_dau = strrchr(a, '(') - a) >= 0)
    {
        char *het_ptr = strchr(a + bat_dau, ')');
        if (!het_ptr)
            break;

        het = het_ptr - a;
        char bt_con[100];
        strncpy(bt_con, a + bat_dau + 1, het - bat_dau - 1);
        bt_con[het - bat_dau - 1] = '\0';

        int value = Tinh(bt_con);
        sprintf(bu_nhin, "%d", value);

        memmove(a + bat_dau + strlen(bu_nhin), a + het + 1, strlen(a) - het);
        memcpy(a + bat_dau, bu_nhin, strlen(bu_nhin));
    }
}

// Ham xu li bieu thuc trong ham main
int main()
{
    char a[100];
    printf("Nhap bieu thuc: ");
    fgets(a, sizeof(a), stdin);
    a[strcspn(a, "\n")] = 0;

    // Loai bo cac khoang trang trong bieu thuc
    khongKhoangTrang(a);

    // Kiem tra tinh hop le cua bieu thuc
    if (!kiemTraHople(a))
    {
        printf("Bieu thuc khong hop le!\n");
        return 1;
    }

    // Kiem tra dau toan hoc trong bieu thuc
    printf("Thu tu cac phep toan: ");
    kt_dau(a);

    // Kiem tra cac so hang trong bieu thuc
    printf("\nCac so hang co trong bieu thuc la: ");
    kt_so_hang(a, 0);
    Thay_The(a);
    int ketqua = Tinh(a);
    printf("\nGia tri cua bieu thuc la: %d\n", ketqua);

    return 0;
}
