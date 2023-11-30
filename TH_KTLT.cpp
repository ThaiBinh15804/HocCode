#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 100

//   BÀI KIỂM TRA LẦN 1 

void taoMang(float *&a, int &n);
void xuatMang(float *a, int n);
void xuatGtri_DiaChi_Mang(float *a, int n);
float timMax(float *a, int n);
float timMax2(float *a, int n);
void xuatMax2(float *a, int n);

void taoMatran(int a[][MAX], int &n);
void swap(int &a, int &b);
void sapXepChanTangDongX(int a[][MAX], int n, int dong);
void xuatMatran(int a[][MAX], int n);
void sapXepChanTangDong(int a[][MAX], int n);
int ktraGiamDongK(int a[][MAX], int n, int k);
void xuatKtraGiamDongK(int a[][MAX], int n, int k);

void Cau2();
void Cau3();
void Cau4();
void menu();

//4.1. Tạo cấu trúc Sản phẩm
struct Sanpham {
    char maSP[6];
    char tenSP[11];
    float donGia;
    int soLuong;
};
void nhapSP(Sanpham &a);
void nhapDSSP(Sanpham a[], int &n);
void docFile(Sanpham a[], int &n);
void xuatDSSP(Sanpham a[], int n);
void swapSP(Sanpham &a, Sanpham &b);
void sapXepTangDanDonGia(Sanpham a[], int n);
void xuatSP_SoLuongItHon5(Sanpham a[], int n);

int main() {
    menu();
    return 0;
}

//Câu 2: Tạo mảng 1 chiều a dạng con trỏ, chứa số thực
//2.1. Tạo và xuấtchiều a chứa giá trị ngẫu nhiên từ 1 đến 100
//Tạo mảng mảng chứa các số thực ngẫu nhiên từ 1 đến 100
void taoMang(float *&a, int &n) {
    printf("Nhap kich thuoc mang: ");
    scanf("%d", &n);
    a = (float *)malloc(n * sizeof(float));
    srand(time(NULL));
    for (int i = 0; i < n; i ++) {
        *(a + i) = 100*(float)rand()/RAND_MAX + 1;
    }
}

//Xuất mảng
void xuatMang(float *a, int n) {
    for (int i = 0; i < n; i ++) {
        printf("%.2f ", *(a + i));
    }
}

//2.2. Xuất giá trị và địa chỉ các phần tử của mảng a
void xuatGtri_DiaChi_Mang(float *a, int n) {
    for (int i = 0; i < n; i ++) {
        printf("\nPhan tu a[%d] co gia tri va dia chi lan luot la: %.2f - %x", i, *(a + i), (a + i));
    }
}

//2.3. Tìm phần tử lớn nhất thứ 2 trong mảng
float timMax(float *a, int n) {
    float max = *a;
    for (int i = 0; i < n; i ++) {
        if (*(a + i) > max)
            max = *(a + i);
    }

    return max;
}

float timMax2(float *a, int n) {
    float max1 = timMax(a, n);
    float max2 = *a;
    for (int i = 0; i < n; i ++) {
        if (*(a + i) > max2 && *(a + i) < max1)
            max2 = *(a + i);
    }

    return max2;
}

void xuatMax2(float *a, int n) {
    printf("\nPhan tu lon thu 2 trong mang la: %.2f", timMax2(a, n));
}

//Menu câu 2
void Cau2() {
    int exitFlag = 0;
    float *a = NULL;
    int n = 0, lc;
    do{
        printf("\n    ----- CAU 2 ---- ");
        printf("\n11. Tao mang ngau nhien trong doan [1, 100]");
        printf("\n12. Xuat mang");
        printf("\n2.  Xuat gia tri va dia chi cac phan tu mang");
        printf("\n3.  Tim phan tu lon thu 2 trong mang");
        printf("\n0. Tro ve menu chinh");

        printf("\n\nNhap vao lua chon cua ban: ");
        scanf("%d", &lc);
        switch (lc)
        {
        case 11:
            taoMang(a, n);
            printf("\nMang duoc tao: ");
            xuatMang(a, n);
            _getch();
            break;
        case 12:
            printf("\nGia tri mang: ");
            xuatMang(a, n);
            _getch();
            break;
        case 2:
            xuatGtri_DiaChi_Mang(a, n);
            _getch();
            break;
        case 3:
            printf("\nMang hien tai: ");
            xuatMang(a, n);
            xuatMax2(a, n);
            _getch();
            break;
        case 0:
            exitFlag = 1;
            break;
        default:
            printf("\nLua chon khong hop le");
            _getch();
            break;
        
        }
    } while (!exitFlag);
}

//Câu 3: Cho ma trận vuông có kích thước n chứa các số nguyên
//3.1. Tạo ma trận với các giá trị ngẫu nhiên từ 1 đến 100
void taoMatran(int a[][MAX], int &n) {
    printf("Nhap kich thuoc ma tran: ");
    //bắt lỗi ngoại lệ nếu sai nhập lại
    do {
        scanf("%d", &n);
        if (n <= 0 || n > MAX)
            printf("\nNhap sai! \nVui long nhap lai kich thuoc ma tran: ");
    } while (n <= 0 || n > MAX);

    srand(time(NULL));
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            a[i][j] = rand() % 100 + 1;
        }
    }
}

//Xuất ma trận
void xuatMatran(int a[][MAX], int n) {
    printf("\n");
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            printf("%4d ", a[i][j]);
        }
        printf("\n");
    }
}

//3.2. Sắp xếp trên từng dòng sao cho các số chẵn tăng dần
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void sapXepChanTangDongX(int a[][MAX], int n, int dong) {
    for (int i = 0; i < n - 1; i ++) {
        for (int j = i + 1; j < n; j ++) {
            if (a[dong][i] > a[dong][j] && a[dong][i] % 2 == 0 && a[dong][j] % 2 == 0)
                swap(a[dong][i], a[dong][j]);
        }
    }
}

void sapXepChanTangDong(int a[][MAX], int n) {
    for (int i = 0; i < n; i ++) {
        sapXepChanTangDongX(a, n, i);
    }
}

//3.3. Kiểm tra dòng thứ k của ma trận có giảm dần hay không
int ktraGiamDongK(int a[][MAX], int n, int k) {
    for (int i = 0; i < n; i ++) {
        if (a[k][i] < a[k][i + 1])
            return 0;
    }

    return 1;
}

void xuatKtraGiamDongK(int a[][MAX], int n, int k) {
    if (ktraGiamDongK(a, n, k) == 1)
        printf("\nDong %d giam dan", k);
    else
        printf("\nDong %d khong giam dan", k);
}


//Menu câu 3
void Cau3() {
    int exitFlag = 0;
    int a[MAX][MAX], n = 0, lc;
    do{
        printf("\n    ----- CAU 3 ---- ");
        printf("\n11. Tao ma tran voi gia tri ngau nhien trong doan [1, 100]");
        printf("\n12. Xuat ma tran");
        printf("\n2.  Sap xep tren tung dong sao cho cac so chan tang dan");
        printf("\n3.  Kiem tra dong thu k co giam dan hay khong");
        printf("\n4.  Kiem tra tung dong co giam dan hay khong");
        printf("\n0.  Tro ve menu chinh");

        printf("\n\nNhap vao lua chon cua ban: ");
        scanf("%d", &lc);
        switch (lc)
        {
        case 11:
            taoMatran(a, n);
            printf("\nMa tran duoc tao: ");
            xuatMatran(a, n);
            _getch();
            break;
        case 12:
            printf("\nMa tran hien tai: ");
            xuatMatran(a, n);
            _getch();
            break;
        case 2:
            printf("\nMa tran truoc khi sap xep: ");
            xuatMatran(a, n);
            sapXepChanTangDong(a, n);
            printf("\nMa tran sau khi sap xep: ");
            xuatMatran(a, n);
            _getch();
            break;
        case 3:
            printf("\nMa tran hien tai: ");
            xuatMatran(a, n);
            printf("\nNhap dong k: ");
            int k;
            scanf("%d", &k);
            xuatKtraGiamDongK(a, n, k);
            _getch();
            break;
        case 4:
            printf("\nMa tran hien tai: ");
            xuatMatran(a, n);
            for (int i = 0; i < n; i ++) {
                xuatKtraGiamDongK(a, n, i);
            }
            _getch();
            break;
        case 0:
            exitFlag = 1;
            break;
        default:
            printf("\nLua chon khong hop le");
            _getch();
            break;
        
        }
    } while (!exitFlag);
}


//Câu 4: 

//4.2. Nhập/Đọc dữ liệu cho danh sách sản phẩm
void nhapSP(Sanpham &a) {
    //Bắt lỗi ngoại lệ nếu nhập sai nhập lại
    try {
        printf("\nNhap ma san pham: ");
        fflush(stdin);
        gets(a.maSP);
        if (strlen(a.maSP) != 5)
            throw "\nMa san pham phai co 5 ky tu";
        printf("\nNhap ten san pham: ");
        fflush(stdin);
        gets(a.tenSP);
        if (strlen(a.tenSP) == 0)
            throw "\nTen san pham khong duoc de trong";
        printf("\nNhap don gia: ");
        scanf("%f", &a.donGia);
        if (a.donGia <= 0)
            throw "\nDon gia phai lon hon 0";
        printf("\nNhap so luong: ");
        scanf("%d", &a.soLuong);
        if (a.soLuong <= 0)
            throw "\nSo luong phai lon hon 0";
    } catch (const char *msg) {
        printf("%s", msg);
        printf("\nVui long nhap lai thong tin san pham!");
        nhapSP(a);
    }
}

void nhapDSSP(Sanpham a[], int &n) {
    printf("\nNhap so luong san pham: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) {
        printf("\nNhap thong tin san pham thu %d", i + 1);
        nhapSP(a[i]);
    }
}

void docFile(Sanpham a[], int &n) {
    FILE *f = fopen("DSSP.txt", "r");
    if (f == NULL) {
        printf("\nKhong mo duoc file");
        return;
    }
    n = 0;
    while (fscanf(f, "%[^|]|%[^|]|%f|%d\n", a[n].maSP, a[n].tenSP, &a[n].donGia, &a[n].soLuong) == 4) {
        n ++;
    }
    fclose(f);
}

//4.3. Xuất danh sách sản phẩm
void xuatDSSP(Sanpham a[], int n) {
    printf("\n%-10s%-15s%-15s%-15s", "Ma SP", "Ten SP", "Don gia", "So luong");
    for (int i = 0; i < n; i ++) {
        printf("\n%-10s%-15s%-15.2f%-15d", a[i].maSP, a[i].tenSP, a[i].donGia, a[i].soLuong);
    }
}

//4.4 Sắp xếp danh sách tăng dần theo đơn giá
void swapSP(Sanpham &a, Sanpham &b) {
    Sanpham temp = a;
    a = b;
    b = temp;
}

void sapXepTangDanDonGia(Sanpham a[], int n) {
    for (int i = 0; i < n - 1; i ++) {
        for (int j = i + 1; j < n; j ++) {
            if (a[i].donGia > a[j].donGia)
                swapSP(a[i], a[j]);
        }
    }
}

// 4.5. Xuất thông tin các sản phẩm có số lượng trong kho ít hơn 5
void xuatSP_SoLuongItHon5(Sanpham a[], int n) {
    printf("\n%-10s%-15s%-15s%-15s", "Ma SP", "Ten SP", "Don gia", "So luong");
    for (int i = 0; i < n; i ++) {
        if (a[i].soLuong < 5)
            printf("\n%-10s%-15s%-15.2f%-15d", a[i].maSP, a[i].tenSP, a[i].donGia, a[i].soLuong);
    }
}


//Menu câu 4
void Cau4() {
    int exitFlag = 0;
    Sanpham a[MAX];
    int n = 0, lc;
    do{
        printf("\n    ----- CAU 4 ---- ");
        printf("\n11. Nhap danh sach san pham");
        printf("\n12. Doc danh sach san pham tu file");
        printf("\n2.  Xuat danh sach san pham");
        printf("\n3.  Sap xep danh sach tang dan theo don gia");
        printf("\n4.  Xuat thong tin cac san pham co so luong trong kho it hon 5");
        printf("\n0.  Tro ve menu chinh");

        printf("\n\nNhap vao lua chon cua ban: ");
        scanf("%d", &lc);
        switch (lc)
        {
        case 11:
            nhapDSSP(a, n);
            printf("\nDanh sach san pham vua nhap: ");
            xuatDSSP(a, n);
            break;
        case 12:
            docFile(a, n);
            printf("\nDanh sach san pham doc tu file: ");
            xuatDSSP(a, n);
            _getch();
            break;
        case 2:
            xuatDSSP(a, n);
            _getch();
            break;
        case 3:
            printf("\nDanh sach san pham truoc khi sap xep: ");
            xuatDSSP(a, n);
            sapXepTangDanDonGia(a, n);
            printf("\nDanh sach san pham sau khi sap xep: ");
            xuatDSSP(a, n);
            _getch();
            break;
        case 4:
            printf("\nDanh sach san pham hien tai: ");
            xuatDSSP(a, n);
            printf("\nDanh sach san pham co so luong trong kho it hon 5: ");
            xuatSP_SoLuongItHon5(a, n);
            _getch();
            break;
        case 0:
            exitFlag = 1;
            break;
        default:
            printf("\nLua chon khong hop le");
            _getch();
            break;
        
        }
    } while (!exitFlag);
}

// MENU tổng
void menu() {
    while (1)
    {
        system("cls");
        printf("\n\n==== MENU ====");
        printf("\n2. Cau 2");
        printf("\n3. Cau 3");
        printf("\n4. Cau 4");
        printf("\n0. Thoat");
        printf("\n\n====================");

        printf("\n\nNhap vao lua chon cua ban: ");
        int lc;
        scanf("%d", &lc);
        switch (lc)
        {
        case 2:
            Cau2();
            break;
        case 3:
            Cau3();
            break;
        case 4:
            Cau4();
            break;
        case 0:
            exit(0);
        default:
            printf("\nLua chon khong hop le");
            _getch();
            break;
        }
    }
}
