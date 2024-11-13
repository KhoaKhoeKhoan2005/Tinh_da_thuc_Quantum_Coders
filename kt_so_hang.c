#include <stdio.h>
#include <string.h>
#define MAX 100
// Ham kiem tra và in ra cac so hang hop le va cac ky tu khong hop le trong bieu thuc
int Kiemtrasohang(char *a)
{
    int i = 0;
    while (a[i] != '\0')
	{
        // Kiem tra neu ky ty la mot so hoac mot dau '-' truoc so
        if ((a[i] >= '0' && a[i] <= '9') || (a[i] == '-' && a[i + 1] >= '0' && a[i + 1] <= '9'))
		{
            // Bat dau mot so hang hop le
            int batdau = i; // Vi tri bat dau cua so hang
            if (a[i] == '-') 
			{
                i++;
            }
            // Duyet qua cac ky tu so lien tiep de tim het so hang
            while (a[i] >= '0' && a[i] <= '9') 
			{
                i++;
            }
            // Trich xuat va in ra so hang hop le
            printf("So hang hop le tai vi tri %d: ", batdau);
            for (int j = batdau; j < i; j++) 
			{
                printf("%c", a[j]);
            }
            printf("\n");
        }
        // Neu ky tu khong hop le
        else
		{
            printf("So hang khong hop le tai vi tri %d: %c\n", i, a[i]);
        }
        i++;
    }
}

int main() 
{
    char a[100];
    // Nhap bieu thuc
    printf("Nhap mot bieu thuc co dau ngoac don bat ky: ");
    fgets(a, sizeof(a), stdin);
    // Kiem tra so hang trong bieu thuc
    Kiemtrasohang(a);
    return 0;
}

