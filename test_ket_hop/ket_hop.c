#include <stdio.h>
#include <string.h>
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

int main() 
{
    char a[100];
    printf("Nhap bieu thuc ");
	gets(a);
    printf("\nbieu thuc sau khi nhap: ");
    puts(a);
    printf("\nthu tu cac phep toan: ");
    kt_dau(a);
}
