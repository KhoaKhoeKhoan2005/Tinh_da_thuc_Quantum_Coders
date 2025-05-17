#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define max 20
int a[max],b[max],tong[max],hieu[max],tich[max*2],so_mu_a,so_mu_b,max_a_b;
float fa[max], fb[max], thuong[max], sodu[max];
void nhapmang(char *dt1, char *dt2) {
    printf("Nhap da thuc thu 1:\n");
    fgets(dt1, 100, stdin);
    dt1[strcspn(dt1, "\n")] = 0;
    printf("Nhap da thuc thu 2:\n");
    fgets(dt2, 100, stdin);
    dt2[strcspn(dt2, "\n")] = 0;
}

void nhapvarutgondt(char* dt, int c[]) {
    for (int i = 0; i < max; i++) {
        c[i] = 0;
    }

    int len = strlen(dt);
    int i = 0, sign = 1, stack[100], top = -1;
    stack[++top] = 1;

    while (i < len) {
        if (dt[i] == ' ') {
            i++; 
            continue;
        }
        if (dt[i] == '+') {
            sign = stack[top];
            i++;
        }
		 else if (dt[i] == '-') {
            sign = -stack[top];
            i++;
        }
		 else if (dt[i] == '(') {
            stack[++top] = sign;
            i++;
        }
		 else if (dt[i] == ')') {
            top--;
            i++;
        } else {
            int heso = 0, bac = 0;
            char temp[20] = {0};
            int j = 0;
            while (i < len && dt[i] != '+' && dt[i] != '-' && dt[i] != '(' && dt[i] != ')') {
                temp[j++] = dt[i++];
            }
            temp[j] = '\0';
            char* vitrix = strchr(temp, 'x');
            if (vitrix) {
                if (vitrix == temp) {
                    heso = 1;
                } else {
                    temp[vitrix - temp] = '\0';
                    heso = atoi(temp);
                }
                if (*(vitrix + 1) == '^') {
                    bac = atoi(vitrix + 2);
                } else {
                    bac = 1;
                }
            } else {
                heso = atoi(temp);
            }
            if (bac < max) {
                c[bac] += heso * sign;
            }
        }
    }
}

int leng(int mang[]) {
    for (int i = max - 1; i >= 0; i--) {
        if (mang[i] != 0) return i;
    }
    return 0;
}

int fleng(float mang[]) {
    for (int i = max - 1; i >= 0; i--) {
        if (mang[i] != 0) return i;
    }
    return 0;
}

void congmang(int a[], int b[]){
    for(int i=0;i<=max_a_b;i++){
        tong[i]=a[i]+b[i];
    }
}

void trumang(int a[], int b[]){
    for(int i=0;i<=max_a_b;i++){
        hieu[i]=a[i]-b[i];
    }
}

void nhanmang(int a[], int b[]){
    for(int i=0;i<=so_mu_a;i++){
        for(int j=0;j<=so_mu_b;j++){
            tich[i+j]+=a[i]*b[j];
        }
    }
}

void chiamang(int a[], int b[]){
    for (int i=0;i<=so_mu_a;i++) fa[i]=a[i]*1.0;
    for (int i=0;i<=so_mu_b;i++) fb[i]=b[i]*1.0;
    float temp[20];
    for(int i=0;i<=so_mu_a;i++) sodu[i]=fa[i];
    while(fleng(sodu)>=so_mu_b){
        thuong[fleng(sodu)-so_mu_b]=sodu[fleng(sodu)]/fb[so_mu_b];
        for(int i=0;i<=20;i++) temp[i]=0;
        for(int i=0;i<=fleng(thuong);i++){
            for(int j=0;j<=so_mu_b;j++){
                temp[i+j]+=thuong[i]*fb[j];
            }
        }
        for(int i=0;i<=so_mu_a;i++){
        sodu[i]=fa[i]-temp[i];
        }
	if(so_mu_b==0) break;
    }
}
void xuatdathuc(int a[]) {
    int first = 1;
    for (int i = max - 1; i >= 0; i--) {
        if (a[i] != 0) {
            if (!first && a[i] > 0) printf(" + ");
            if (a[i] < 0) printf(" - ");
            if (abs(a[i]) != 1 || i == 0) printf("%d", abs(a[i]));
            if (i > 0) printf("x");
            if (i > 1) printf("^%d", i);
            first = 0;
        }
    }
    if (first) printf("0");
    printf("\n");
}

void xuatdathuc_float(float a[]) {
    int first = 1;
    for (int i = max - 1; i >= 0; i--) {
        if (a[i] != 0) {
            if (!first && a[i] > 0) printf(" + ");
            if (a[i] < 0) printf(" - ");
            if (fabs(a[i]) != 1 || i == 0) printf("%.2f", fabs(a[i]));
            if (i > 0) printf("x");
            if (i > 1) printf("^%d", i);
            first = 0;
        }
    }
    if (first) printf("0");
    printf("\n");
}

int main(){
    char dt1[100];
    char dt2[100];
    nhapmang(dt1, dt2);
    nhapvarutgondt(dt1, a);
    nhapvarutgondt(dt2, b);
    so_mu_a=leng(a); so_mu_b=leng(b);
      so_mu_a = leng(a);
    so_mu_b = leng(b);
    max_a_b = (so_mu_a >= so_mu_b) ? so_mu_a : so_mu_b;
    congmang(a, b);
    printf("\nTong da thuc: ");
    xuatdathuc(tong);
    trumang(a, b);
    printf("\nHieu da thuc: ");
    xuatdathuc(hieu);
    nhanmang(a, b);
    printf("\nTich da thuc: ");
    xuatdathuc(tich);
    if(so_mu_b==0 && b[0]==0){
		printf("\nKhong the chia da thuc");
		}
    else{
    chiamang(a,b);
    printf("\nThuong da thuc: ");
    xuatdathuc_float(thuong);
     printf("\nSo du da thuc: ");
    xuatdathuc_float(sodu);
    }
    return 0;
}
