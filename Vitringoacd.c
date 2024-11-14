#include<stdio.h>
#include<string.h>
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

int main() {
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
// Tao cung nghi ra duoc phuong an nay hom qua, nhung ma nghi ra ham tinh voi ham final rat la kho
// Cu the la t du dinh tao ra 3 mang b,c,d trong do mang b va c nhu da ban hom thu 4, con mang d la de chua level cua cac so hang trong mang b
//so hang cang nam trong nhieu dau ngoac thi level cang cao
// vd bieu thuc ((3+8)+12-14) thi mang b la 3 8 12 14 va mang d la 2 2 1 1
