/*
Mẹ mày béo
Dòng comment này được viết trên Github
nhằm test chức năng chỉnh sửa trên
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//dem ki true
int demkitu(char *a, int n)
{
    int dem1=0;
    for (int i=0; a[i]!='\0'; i++){
        dem1++;
    }
    return dem1;
}

//dem so lan xuat hien ki tu a
int demlan(char *a, int n)
{
    int dem2=0;
    for (int i=0; a[i]!='\0';i++)
    {
        if(a[i]=='a')
        {
            dem2++;
        }
    }
    return dem2;
}

//dem khoang trang
int demkhoang(char *a, int n)
{
    int dem3=0;
    for(int i=0; a[i]!='\0';i++)
    {
        if(a[i]==' ')
        {
            dem3++;
        }
    }
    return dem3;
}

//xoa khoang trang
void xoa(char *a, int n)
{
    int i,j=0;
    for(i=0;a[i]='\0';i++)
    {
        if(a[i]!=' ')
        {
            a[j++]=a[i];
        }
    }
    a[j]='\0';
}

//xuat ra ket qua
void xuat(char *a, int n)
{
    printf("\nSo ki tu la: %d",demkitu(a,n));
    printf("\nSo lan xuat hien: %d",demlan(a,n));
    printf("\nSo khoang trang: %d", demkhoang(a,n));
}

int main()
{
    char *a;
    int n;
    printf("\nNhap so phan tu ki tu:");
    scanf("%d",&n);
    int temp=getchar();
    a=(char*) malloc (n*sizeof(char));
    if(a==NULL) exit(1);
    printf("\nNhap chuoi a:");
    fgets(a,n,stdin)
    [strlen(a)-1]='\0';
    xuat(a,n);
    xoa(a,n);
    printf("%s",a); free(a);
    return 0;
}
