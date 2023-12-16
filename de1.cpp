#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


//Nhập mảng
void nhapMang(int a[], int &n) {
    printf("\nNhap vao so luong phan tu mang: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) {
        printf("\nNhap phan tu thu %d: ", i + 1);
        scanf("%d", &a[i]);
    }
}

//Xuất mảng
void xuatMang(int a[], int n) {
    for (int i = 0; i < n; i ++) {
        printf(" %d", a[i]);
    }
}


//1.1. Hãy cho biết tất cả phần tử chẵn của B có nằm trong A hay không
int ktraChanB_inA(int a[], int na, int b[], int nb) {
    int check = 0; //Kiểm tra xem trong B có phần tử chẵn không và kiểm tra chẵn B trong A
    for (int i = 0; i < nb; i ++) {
        if (b[i] % 2 == 0) {
            check = 0;
            for (int j = 0; j < na; j ++) {
                if (b[i] == a[j]) {
                    check = 1;
                    break;
                }
            }
            if (check == 0) {
                return 0;
            }
        }
    }

    if (check == 0) 
        return 0;
    return 1;
}

//1.2. Đếm số phần tử cùng xuất hiện trong cả 2 mảng
int searchInArray(int a[], int n, int x) {
    for (int i = 0; i < n; i ++) {
        if (a[i] == x)
            return i;
    }
    return -1;
}

void xoaPhanTu(int a[], int &n, int x) {
    int indexXoa = searchInArray(a, n, x);
    if (indexXoa != -1) {
        for (int i = indexXoa; i < n; i ++) {
            a[i] = a[i + 1];
        }
        n --;
    }
}

int demPtu_CungXH_2Mang(int a[], int na, int b[], int nb) {
    int soPhanTu[100];
    int nPhantu = 0;
    for (int i = 0; i < na; i ++) {
        if (searchInArray(soPhanTu, nPhantu, a[i]) == -1) {
            soPhanTu[nPhantu] = a[i];
            nPhantu ++;
        }
    }

    int cout = 0;
    for (int i = 0; i < nb; i ++) {
        if (searchInArray(soPhanTu, nPhantu, b[i]) != -1) {
            cout ++;
            xoaPhanTu(soPhanTu, nPhantu, b[i]);
        }
    }

    return cout;
}

//Nhập chuỗi


//2.1. Biến tất cả các từ của chuỗi B trong chuoi A thành I LOVE 
void xoaN_KiTu(char s[], int n, int k) {
    int l = strlen(s);
    for (int i = k; i < l; i ++) {
        s[i] = s[i + n];
    }
    s[l - n] = '\0';
}

void chenChuoi(char s[], char a[], int x) {
    int ls = strlen(s);
    int la = strlen(a);

    for (int i = la; i >= x; i --) {
        a[i + ls] = a[i];
    }

    int chen = 0;
    for (int i = x; i < x + ls; i ++) {
        a[i] = s[chen];
        chen ++;
    }
}

int timChuoiB_InA(char a[], char b[], int x) {
    int la = strlen(a);
    int lb = strlen(b);

    for (int i = x; i <= la - lb; i ++) {
        if (a[i] == b[0]) {
            int cout = 0;
            for (int j = 0; j < lb; j ++) {
                if (a[i + j] == b[j])
                    cout ++;
                else
                    break;
            }

            if (cout == lb)
                return i;
        }
    }
    return -1;
}

void doiChuoiB_InA(char a[], char b[]) {
    int la = strlen(a);
    int lb = strlen(b);
    char s[] = "I LOVE";
    int ls = strlen(s);

    for (int i = 0; i < la; i ++) {
        int indexChen = timChuoiB_InA(a, b, 0);
        if (indexChen != -1) {
            chenChuoi(s, a, indexChen);
            xoaN_KiTu(a, lb, indexChen + ls);
        }
    }
}

//2.2. Xoá tất cả các số ra khỏi chuỗi
void xoaSo(char s[]) {
    int n = strlen(s);
    for (int i = 0; i < n; i ++) {
        if (s[i] >= '0' && s[i] <= '9') {
            xoaN_KiTu(s, 1, i);
            i --;
        }
    }
}

// 3.1. Đếm số lần xuất hiện x trong mảng số nguyên
//Dùng đệ quy
int demX_DQ(int a[], int n, int i, int x) {
    if (i == n) return 0;
    if (a[i] == x)
        return demX_DQ(a, n, i + 1, x) + 1;
    else
        return demX_DQ(a, n, i + 1, x);
}

//Dùng khử đệ quy
int demX_khuDQ(int a[], int n, int x) {
    int dem = 0;
    for (int i = 0; i < n; i ++) {
        if (a[i] == x)
            dem ++;
    }
    return dem;
}

//3.2. Tính tổ hợp chập k của n
//Dùng đệ quy
int toHopChapK_DQ(int n, int k) {
    if (k == 0 || k == n) return 1;
    return toHopChapK_DQ(n - 1, k - 1) + toHopChapK_DQ(n - 1, k);
}

int toHopChapK_khuDQ(int n, int k) {
    int result = 1;
    
    for (int i = 1; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    
    return result;
}

int main() {
    // int a[100];
    // int b[100];
    // int na, nb;
    // printf("\nNhap mang a: ");
    // nhapMang(a, na);
    // printf("\nMang a: ");
    // xuatMang(a, na);
    // printf("\nNhap mang b: ");
    // nhapMang(b, nb);
    // printf("\nMang b: ");
    // xuatMang(b, nb);
    // // if (ktraChanB_inA(a, na, b, nb) == 1) {
    // //     printf("\nDung");
    // // } else {
    // //     printf("\nSai");
    // // }

    // printf("\nSo phan tu cung xuat hien trong 2 mang: %d", demPtu_CungXH_2Mang(a, na, b, nb));

    // char a[100];
    // printf("\nNhap chuoi a: ");
    // fflush(stdin);
    // gets(a);
    // printf("\nChuoi a: %s", a);
    // // char b[100];
    // // printf("\nNhap chuoi b: ");
    // // fflush(stdin);
    // // gets(b);
    // // printf("\nChuoi b: %s", b);

    // // printf("\n%d", timChuoiB_InA(a, b, 8));
    // // doiChuoiB_InA(a, b);
    // xoaSo(a);
    // printf("\nChuoi a: %s", a);
    
    // int a[100];
    // int n;
    // nhapMang(a, n);
    // printf("\nMang: ");
    // xuatMang(a, n);
    // int x;
    // printf("\nNhap phan tu muon dem: ");
    // scanf("%d",&x);
    // printf("\nSo lan %d xuat hien: %d", x, demX_khuDQ(a, n, x));

    // int n, k;
    // printf("\nNhap k: ");
    // scanf("%d", &k);
    // printf("\nNhap n: ");
    // scanf("%d", &n);

    // printf("\nKq: %d", toHopChapK_khuDQ(n,k));

    _getch();
    return 1;

}
