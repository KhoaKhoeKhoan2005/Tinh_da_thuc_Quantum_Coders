#include<stdio.h>
#include<string.h>
//Phan khai bao bien, bo vo main thi vut phan nay di
float b[50], c[50],d[50];
float tinh();
int length(float a[]);
float tinhngoac(int i, int j);
float congtru(int i, int j);
float nhanchia(int i, int j);
int main(){
    // nhap 3 mang b, c, d va tinh, bo vo main thi vut phan nhap 3 mang di
    int n,m;
    printf("nhap so phan tu mang b: ");
    scanf("%d",&n);
    printf("\nnhap mang b: ");
    for(m=0;m<n;m++){
        printf("b[%d]= ",m);
        scanf("%f",&b[m]);
    }
    printf("\nnhap mang c (1,2,3,4): ");
    for(m=0;m<n-1;m++){
        printf("c[%d]= ",m);
        scanf("%f",&c[m]);
    }
    printf("\nnhap mang d: ");
    for(m=0;m<n;m++){
        printf("d[%d]= ",m);
        scanf("%f",&d[m]);
    }
    tinh();
    printf("ket qua: %f",b[0]);
}

float tinh(){
    int max=d[0];
    for (int i=0; i<length(d);i++){
            if(d[i]>max) max=d[i];
    }
    for(;max>=0;max--){
        for(int i=0;i<length(b);i++){
            if(d[i]==max){
                for(int j=i;j<length(b);j++){
                    if(d[j]!=max){
                        tinhngoac(i,j);
                        break;
                    }
                    else if(j=length(b)){
                        tinhngoac(i,j);
                        break;
                    }
                }
            }
        }
    }
}
//tinh do dai cua mot mang
int length(float a[]){
    int length=0;
    while (a[length] != 0 && length < 100) {
        length++;
    }
    return (length-1);
}

float tinhngoac(int i, int j){
int k=i+1;
float kqua = congtru(i,j);
b[i]=kqua;
d[i]=d[i]-1;
for(;k<=length(b)-(j-i);k++){
    b[k]=b[k+j-i];
}
if(j>length(b)-(j-i)){
    for(k=length(b)-(j-i);k<=j;k++) b[k]=0;
}
for(;k<=length(c)-(j-i);k++){
    c[k]=c[k+j-i];
}
if(j>length(c)-(j-i)){
    for(k=length(c)-(j-i);k<=j;k++) c[k]=0;
}
for(;k<=length(d)-(j-i);k++){
    d[k]=d[k+j-i];
}
if(j>length(d)-(j-i)){
    for(k=length(d)-(j-i);k<=j;k++) d[k]=0;
}
}
float congtru(int i, int j){
    float kq=nhanchia(i,j);
    int k=i;
    while(k<=j-1){
       float temp = nhanchia(i,j);
        if(c[i]==1){
            kq+=temp; k++;       
        }
        else if(c[i]==2){
            kq-=temp; k++;
        }
    }
    return kq;
}
float nhanchia(int i, int j){
    float kq;
    int k=i;
    while(k<=j-1){
        if(c[k]==1||c[k]==2){
            kq=b[k]; i=i+1; break;
        }
        else if(c[k]==3){
            kq=b[k];
            while((k<=j-1)||c[k]==3){
                kq*=b[k+1];
                i=i+1;
            }
            break;
        }
        else if(c[k]==4){
            kq=b[k];
            while((k<=j-1)||c[k]==4){
                kq/=b[k+1];
                i=i+1;
            }
            break;
        }   
    }
    return kq;
}