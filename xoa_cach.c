#include <stdio.h>
#include <string.h>
#include <ctype.h>
int ktra(char *a)
{
	int dem=0;
	for(int i=0;a[i]!='\0';i++)
	{
		if(a[i]==' ') {dem++;}
	}
	return dem;
}
void xoakhoangtrang(char *a) {
    int i = 0, j = 0;
    for (int i = 0; a[i] != '\0'; i++) 
	{
        if (a[i] != ' ') {a[j++] = a[i];}
    }
    a[j] = '\0';
}
void vitripheptoan(char *a) 
{
	for (int i = 0; a[i] != '\0'; i++) 
	{
        if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/') {printf("%d ", i);}
    }
}
void vitringoacdong(const char *a) 
{
    for (int i = 0; a[i] != '\0'; i++)
	{
        if (a[i] == ')') {printf("%d ", i);}
    }
}
int main() {
    char a[100];
    printf("Nhap bieu thuc ");
	gets(a);
	printf("\nco %d khoang trang trong bieu thuc",ktra(a));
    xoakhoangtrang(a);
    printf("\nbieu thuc sau khi xoa khoang trang: ");
    puts(a);
    printf("\nVi tri cac phep toan: ");
    vitripheptoan(a);
    printf("\nVi tri ngoac dong: ");
    vitringoacdong(a);
}
