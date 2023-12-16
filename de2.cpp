#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

//Nhập mảng
void nhapMang(int a[], int &n) {
    printf("\nNhap so luong: ");
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

//1.1. Đếm số lượng phần tử phân biệt trong mảng
int timKiemX(int a[], int n, int x) {
    for (int i = 0; i < n; i ++) {
        if (a[i] == x)
            return i;
    }
    return -1;
}

int demPtuPhanBiet(int a[], int n) {
    int dem[MAX];
    int ndem = 0;
    for (int i = 0; i < n; i ++) {
        if (timKiemX(dem, n, a[i]) == -1) {
            dem[ndem] = a[i];
            ndem ++;
        }
    }

    return ndem;
}

struct map {
    int value;
    int num;
};

int timKiemMap(map a[], int n, int x) {
    for (int i = 0; i < n; i ++) {
        if (a[i].value == x)
            return i;
    }
    return -1;
}

int timNumMax_inMap(map a[], int n) {
    int max = 0;
    for (int i = 0; i < n; i ++) {
        if (a[i].num > a[max].num) {
            max = i;
        }
    }
    return a[max].value;
}

void Cau1_1(int a[], int n) {
    map phanTu[MAX] = {0};
    int m = 0;
    for (int i = 0; i < n; i ++) {
        int index = timKiemMap(phanTu, n, a[i]);
        if (index == -1) {
            phanTu[m].value = a[i];
            phanTu[m].num ++;
            m ++;
        } else {
            phanTu[index].num ++;
        }

    }

    printf("\nSo luong phan tu cua mang: %d", m);
    printf("\nPhan tu xuat hien nhieu nhat: %d", timNumMax_inMap(phanTu, m));
}


//2.1. Biến các từ sau dấu '.' thành từ có chữ cái in hoa ký tự đầu tiên
void Cau2_1(char s[]) {
    int n = strlen(s);
    for (int i = 0; i < n; i ++) {
        if (s[i] == '.') {
            int anchor = 1;
            while (s[i + anchor] <= 'a' || s[i + anchor] >= 'z') {
                anchor ++;
            }
            s[i + anchor] -= 32;
        }
    }
}

void chenKiTu(char s[], char x, int k) {
    int n = strlen(s);
    for (int i = n; i >= k; i --) {
        s[i + 1] = s[i];
    }
    s[k] = x;
    s[n + 1] = '\0';
}

void Cau2_2(char s[]) {
    int n = strlen(s);
    char x = '.';
    for (int i = 1; i < n - 1; i ++) {
        if (s[i] == ' ' && (s[i + 1] >= 'A' && s[i + 1] <= 'Z')) {
                chenKiTu(s, x, i);
                i ++;
        }
    }
}


//3.1. Tìm phần tử lớn nhất
//Đệ quy
int timMax_DQ(int a[], int n, int i, int max) {
    if (i == n) return a[max];
    if (a[i] > a[max])
        return timMax_DQ(a, n, i + 1, i);
    else
        return timMax_DQ(a, n, i + 1, max);
}

//Khử đệ quy
int timMax_khuDQ(int a[], int n) {
    int max = 0;
    for (int i = 1; i < n; i ++) {
        if (a[max] < a[i])
            max = i;
    }
    return a[max];
}

//3.2. Tìm Fibonacci lẻ trong đoạn [m, n]

//Tính Fibonacci
//Đệ quy
int Fibonacci_DQ(int n) {
    if (n == 0) return 0;
    if (n <= 2) return 1;
    return Fibonacci_DQ(n - 1) + Fibonacci_DQ(n - 2);
}

//Khử đệ quy
int Fibonacci_khuDQ(int n) {
    if (n == 0) return 0;
    if (n <= 2) return 1;
    int p1 = 1, p2 = 1, cr = 0;
    for (int i = 3; i <= n; i ++) {
        cr = p1 + p2;
        p2 = p1;
        p1 = cr;
    }

    return cr;
}

int ktraFibonacci(int x) {
    if (x == 0) return 0;
    if (x <= 2) return 1;
    long long p1 = 1, p2 = 1, cr = 0;
    for (int i = 3; i <= x; i ++) {
        cr = p1 + p2;
        if (cr == x)
            return 1;
        p2 = p1;
        p1 = cr;
    }

    return 0;
}

void Cau3_2(int m, int n) {
    printf("\nCac gia tri: ");
    for (int i = m; i <= n; i ++) {
        if (i % 2 != 0 && ktraFibonacci(i) == 1)
            printf(" %d", i);
    }
}

int main() {
    // int a[MAX];
    // int n;
    // nhapMang(a, n);
    // printf("\nMang a: ");
    // xuatMang(a, n);
    // printf("\nKq: %d", demPtuPhanBiet(a, n));
    // Cau1_1(a, n);

    // char a[100];
    // printf("\nNhap chuoi a: ");
    // fflush(stdin);
    // gets(a);
    // printf("\nChuoi: %s", a);
    // Cau2_1(a);
    // // Cau2_2(a);
    // printf("\nChuoi: %s", a);

    // int a[MAX];
    // int n;
    // nhapMang(a, n);
    // printf("\nMang a: ");
    // xuatMang(a, n);
    // printf("\nMax: %d", timMax_khuDQ(a, n));

    int m, n;
    printf("\nNhap vao m, n: ");
    scanf("%d%d", &m, &n);
    Cau3_2(m, n);

    _getch();
    return 1;
}
