#include <stdio.h>
#include <string.h>
int main() {
    char a[100];
    printf("Nhap bieu thuc: ");
    fgets(a, sizeof(a), stdin);

    xoa_cach(a);
    kt_so_hang(a);
    kt_dau(a);
    tinh(a);
    
    printf("Kết quả: %d\n", result);

    return 0;
}
// (((2+10)+1+2))+3
