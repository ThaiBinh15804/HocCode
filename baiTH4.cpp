#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//cấu trúc phân số
struct phanso
{
    int tu;
    int mau;
};

typedef phanso value;
//cấu trúc nút là phân số
struct NODE {
    value data;
    NODE* Left;
    NODE* Right;
};

struct TREE {
	NODE* Root;
};

void InitTree(TREE& t) {
	t.Root = NULL;
}

//Tạo nút
NODE* CreateNode(value x) {
    NODE* p = new NODE;
    if (p == NULL)
        return NULL;
    p->data = x;
    p->Left = NULL;
    p->Right = NULL;
    return p;
}


//Rút gọn phân số
int UCLN(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (a != b) {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;
}
value RutGonPhanSo(value& x) 
{
    int ucln = UCLN(x.tu, x.mau);
    x.tu = x.tu / ucln;
    x.mau = x.mau / ucln;

    return x;
}

//So sánh 2 phân số nếu lớn hơn trả về 1, nhỏ hơn trả về -1 bằng trả về 0
int SoSanhPhanSo(value x, value y) {
    float a = (float)x.tu / x.mau;
    float b = (float)y.tu / y.mau;
    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    else
        return 0;
}

//Kiểm tra phân số có đúng quy tắc không
int KiemTraPhanSo(value x) {
    if (x.mau == 0)
        return 0;
    return 1;
}

//Thêm nút vào cây
void InsertNode(TREE& t, NODE* p) 
{
    if (t.Root == NULL)
        t.Root = p;
    else 
    {
        NODE* f = NULL;
        NODE* q = t.Root;
        while (q != NULL) {
            if (SoSanhPhanSo(p->data, q->data) == 0) //Nếu phân số đã tồn tại trong cây thì không thêm vào
                return;
            f = q;
            if (SoSanhPhanSo(p->data, q->data) == -1) //Nếu phân số nhỏ hơn thì duyệt sang trái
                q = q->Left;
            else
                q = q->Right; //Nếu phân số lớn hơn thì duyệt sang phải
        }
        if (SoSanhPhanSo(p->data, f->data) == -1) //Thêm vào bên trái nếu phân số nhỏ hơn
            f->Left = p;
        else
            f->Right = p; //Thêm vào bên phải nếu phân số lớn hơn
    }
}

//Tìm kiếm phần tử dùng đệ quy
NODE* SearchNode(NODE* p, value x) {
    if (p == NULL)
        return NULL;
    if (SoSanhPhanSo(p->data, x) == 0)
        return p;
    else if (SoSanhPhanSo(p->data, x) == -1)
        return SearchNode(p->Right, x);
    else
        return SearchNode(p->Left, x);
}


//Thêm nút vào sau nút T
void Insert_After_T(NODE *p, NODE *T)
{
    if (T == NULL)
    {
        printf("\nNode T khong ton tai, khong the them node p vao sau node T");
        _getch();
        return;
    }
    else
    {
        if (T->Left != NULL && T->Right != NULL)
        {
            printf("\nNode T da co 2 con, khong the them node p vao sau node T");
            _getch();
            return;
        }
        else if (T->Right == NULL && (SoSanhPhanSo(p->data, T->data) == 1))
            T->Right = p;
        else if (T->Left == NULL && (SoSanhPhanSo(p->data, T->data) == -1))
            T->Left = p;
        else
        {
            printf("\nNode p khong the them vao sau node T");
            _getch();
            return;
        }
    }
        
}
//Tìm nút thế mạng của cây
void NodeTheMang(NODE*& x, NODE*& y) {
    if (y->Left != NULL)
        NodeTheMang(x, y->Left);
    else {
        x->data = y->data;
        x = y;
        y = y->Right;
    }
}
//Xoá nút trong cây
void DeleteNode(TREE& t, value x) {
    if (t.Root == NULL)
        return;

    NODE* f = NULL;
    NODE* p = t.Root;

    while (p != NULL) {
        if (SoSanhPhanSo(x, p->data) == 0)
            break;
        f = p;
        if (SoSanhPhanSo(x, p->data) == -1)
            p = p->Left;
        else
            p = p->Right;
    }

    if (p == NULL)
        return;
    if (p->Left == NULL && p->Right == NULL) 
    {
        if (f == NULL)
            t.Root = NULL;
        else {
            if (f->Left == p)
                f->Left = NULL;
            else
                f->Right = NULL;
        }
        delete p;
    }
    else if (p->Left != NULL && p->Right == NULL) 
    {
        if (f == NULL)
            t.Root = p->Left;
        else {
            if (f->Left == p)
                f->Left = p->Left;
            else
                f->Right = p->Left;
        }
        delete p;
    }
    else if (p->Left == NULL && p->Right != NULL) 
    {
        if (f == NULL)
            t.Root = p->Right;
        else {
            if (f->Left == p)
                f->Left = p->Right;
            else
                f->Right = p->Right;
        }
        delete p;
    }
    else if (p->Left != NULL && p->Right != NULL) 
    {
        NODE* q = p->Right;
        f = NULL;
        while (q->Left != NULL) {
            f = q;
            q = q->Left;
        }
        p->data = q->data;
        if (f != NULL)
            f->Left = q->Right;
        else
            p->Right = q->Right;
        delete q;
    }
}

//Duyệt cây bằng 6 cách xuất ra phân số
void Traverse_NLR(NODE* root) {
    if (root == NULL)
        return;
    printf("%d/%d  ", root->data.tu, root->data.mau);
    Traverse_NLR(root->Left);
    Traverse_NLR(root->Right);
}

void Traverse_LNR(NODE* root) {
    if (root == NULL)
        return;
    Traverse_LNR(root->Left);
    printf("%d/%d  ", root->data.tu, root->data.mau);
    Traverse_LNR(root->Right);
}

void Traverse_LRN(NODE* root) {
    if (root == NULL)
        return;
    Traverse_LRN(root->Left);
    Traverse_LRN(root->Right);
    printf("%d/%d  ", root->data.tu, root->data.mau);
}

void Traverse_RNL(NODE* root) {
    if (root == NULL)
        return;
    Traverse_RNL(root->Right);
    printf("%d/%d  ", root->data.tu, root->data.mau);
    Traverse_RNL(root->Left);
}

void Traverse_NRL(NODE* root) {
    if (root == NULL)
        return;
    printf("%d/%d  ", root->data.tu, root->data.mau);
    Traverse_NRL(root->Right);
    Traverse_NRL(root->Left);
}

void Traverse_RLN(NODE* root) {
    if (root == NULL)
        return;
    Traverse_RLN(root->Right);
    Traverse_RLN(root->Left);
    printf("%d/%d  ", root->data.tu, root->data.mau);
}


//Tạo cây nhị phân tìm kiếm nhập liệu từ bàn phím
void CreateTree(TREE& t, int n) 
{
    for (int i = 0; i < n; i++)
    {
        value x;
        printf("Nhap phan so thu %d: ", i + 1);
        
        do
        {
            scanf_s("%d/%d", &x.tu, &x.mau);
            if (KiemTraPhanSo(x) == 0)
                printf("\nPhan so khong hop le. \nVui long nhap lai: ");
        }
        while (KiemTraPhanSo(x) == 0);

        NODE* p = CreateNode(x);
        InsertNode(t, p);
    }
}

//Tạo cây nhị phân tìm kiếm với số lượng yêu cầu và các giá trị là ngẫu nhiên
void CreateTree_Random(TREE& t, int n) 
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        value x;
        do
        {
            x.tu = rand() % 100;
            x.mau = rand() % 100;
        } 
        while (KiemTraPhanSo(x) == 0);
        NODE* p = CreateNode(x);
        InsertNode(t, p);
    }
}

//Tạo cây tìm kiếm từ một  mảng
void CreateTree_Array(TREE& t, value a[], int n) 
{
    for (int i = 0; i < n; i++)
    {
        NODE* p = CreateNode(a[i]);
        InsertNode(t, p);
    }
}

int coutNode(NODE* root) {
	
	if (root == NULL)
		return 0;

	return coutNode(root->Left)+coutNode(root->Right)+1;
}
//Đếm số nút có giá trị lớn hơn 1
int DemNodeLonHon1(NODE* root) {
    if (root == NULL)
        return 0;
    if (root->data.tu > root->data.mau)
        return DemNodeLonHon1(root->Left) + DemNodeLonHon1(root->Right) + 1;
    else
        return DemNodeLonHon1(root->Left) + DemNodeLonHon1(root->Right);
}

//Tối giản tất cả các nút trong cây
void ToiGian(NODE *root) {
    if (root == NULL)
        return;
    ToiGian(root->Left);
    ToiGian(root->Right);
    root->data = RutGonPhanSo(root->data);
}

//Tìm kiếm trong cây có nút nào bằng x không
NODE* SearchNode(TREE t, value x) 
{
    NODE* p = t.Root;

    while (p != NULL) {
        if (SoSanhPhanSo(x, p->data) == 0)
            return p;
        else if (SoSanhPhanSo(x, p->data) == -1)
            p = p->Left;
        else
            p = p->Right;
    }
    return NULL;
}

//hàm nhập gồm 3 lựa chọn
void nhap(TREE &t)
{
    printf("\n\n\t\t =========== NHAP DU LIEU ===========");
    printf("\n1. Nhap du lieu tu ban phim");
    printf("\n2. Nhap du lieu ngau nhien");
    printf("\n3. Nhap du lieu tu mang");
    printf("\n\n\t\t =========== END ===========");

    int luachon;
    printf("\nNhap lua chon: ");
    scanf_s("%d", &luachon);

    switch (luachon)
    {
    case 1:
    {
        int n;
        printf("\nNhap so luong phan so: ");
        scanf_s("%d", &n);
        CreateTree(t, n);
    }
    break;
    case 2:
    {
        int n;
        printf("\nNhap so luong phan so: ");
        scanf_s("%d", &n);
        CreateTree_Random(t, n);
    }
    break;
    case 3:
    {
        int n;
        printf("\nNhap so luong phan so: ");
        do 
        {
            scanf_s("%d", &n);
            if (n <= 0)
                printf("\nSo luong phan so khong hop le.\nVui long nhap lai: ");
        } 
        while (n <= 0);

        value* a = new value[n];
        for (int i = 0; i < n; i++)
        {
            printf("\nNhap phan so thu %d: ", i + 1);
            scanf_s("%d/%d", &a[i].tu, &a[i].mau);
        }
        CreateTree_Array(t, a, n);
    }
    default:
        printf("\nLua chon khong hop le");
        break;
    }
}

//hàm xuất
void xuat(TREE t)
{
    printf("\n\n\t\t =========== XUAT DU LIEU ===========");
    printf("\n1. Xuat du lieu theo thu tu NLR");
    printf("\n2. Xuat du lieu theo thu tu LNR");
    printf("\n3. Xuat du lieu theo thu tu LRN");
    printf("\n4. Xuat du lieu theo thu tu NRL");
    printf("\n5. Xuat du lieu theo thu tu RNL");
    printf("\n6. Xuat du lieu theo thu tu RLN");
    printf("\n\n\t\t =========== END ===========");

    int luachon;
    printf("\nNhap lua chon: ");
    scanf_s("%d", &luachon);

    switch (luachon)
    {
    case 1:
    {
        printf("\n\n\t=========== XUAT DU LIEU THEO THU TU NLR ===========\n");
        printf("\t");
        Traverse_NLR(t.Root);
        _getch();
        break;
    }
    case 2:
    {
        printf("\n\n\t=========== XUAT DU LIEU THEO THU TU LNR ===========\n");
        printf("\t");
        Traverse_LNR(t.Root);
        _getch();
        break;
    }
    case 3:
    {
        printf("\n\n\t=========== XUAT DU LIEU THEO THU TU LRN ===========\n");
        printf("\t");
        Traverse_LRN(t.Root);
        _getch();
        break;
    }
    case 4:
    {
        printf("\n\n\t=========== XUAT DU LIEU THEO THU TU NRL ===========\n");
        printf("\t");
        Traverse_NRL(t.Root);
        _getch();
        break;
    }
    case 5:
    {
        printf("\n\n\t=========== XUAT DU LIEU THEO THU TU RNL ===========\n");
        printf("\t");
        Traverse_RNL(t.Root);
        _getch();
        break;
    }
    case 6:
    {
        printf("\n\n\t=========== XUAT DU LIEU THEO THU TU RLN ===========\n");
        printf("\t");
        Traverse_RLN(t.Root);
        _getch();
        break;
    }
    default:
        printf("\nLua chon khong hop le");
        break;
    }
}
//Cộng 2 phân số
value CongPhanSo(value a, value b)
{
    value sum;
    sum.tu = a.tu * b.mau + b.tu * a.mau;
    sum.mau = a.mau * b.mau;
    return sum;
}

//Tính tổng các node trong cây dùng đệ quy
value Tong(NODE *root)
{
    if (root == NULL)
        return { 0, 1 };
    
    return CongPhanSo(root->data, CongPhanSo(Tong(root->Left), Tong(root->Right)));
}
//Tìm phân số lớn nhất trong cây
value TimMax(TREE t)
{
    value max = t.Root->data;
    NODE* p = t.Root;
    while (p != NULL)
    {
        if (SoSanhPhanSo(p->data, max) == 1)
            max = p->data;
        p = p->Right;
    }
    return max;
}

//Tìm phân số nhỏ nhất trong cây
value TimMin(TREE t)
{
    value min = t.Root->data;
    NODE* p = t.Root;
    while (p != NULL)
    {
        if (SoSanhPhanSo(p->data, min) == -1)
            min = p->data;
        p = p->Left;
    }
    return min;
}
//Liệt kê tử số lớn hơn mẫu số dùng đệ quy
void LietKeTuSoLonHonMauSo(NODE *Root)
{
    if (Root != NULL)
    {
        if (Root->data.tu > Root->data.mau)
            printf("%d/%d\t", Root->data.tu, Root->data.mau);
        LietKeTuSoLonHonMauSo(Root->Left);
        LietKeTuSoLonHonMauSo(Root->Right);
    }
}

//Liệt kê tử số nhỏ hơn mẫu số dùng đệ quy
void LietKeTuSoNhoHonMauSo(NODE* Root)
{
    if (Root != NULL)
    {
        if (Root->data.tu < Root->data.mau)
            printf("%d/%d\t", Root->data.tu, Root->data.mau);
        LietKeTuSoNhoHonMauSo(Root->Left);
        LietKeTuSoNhoHonMauSo(Root->Right);
    }
}
//Kiểm tra phân số có phải là số nguyên tố
int KiemTraNguyenTo(int n)
{
    if (n < 2)
        return 0;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return 0;
    return 1;
}

//Liệt kê các phân số có tủ và mẫu đồng thời là số nguyên tố
void LietKePhanSoNguyenTo(NODE* Root)
{
    if (Root != NULL)
    {
        if (KiemTraNguyenTo(Root->data.tu) == 1 && KiemTraNguyenTo(Root->data.mau) == 1)
            printf("%d/%d\t", Root->data.tu, Root->data.mau);
        LietKePhanSoNguyenTo(Root->Left);
        LietKePhanSoNguyenTo(Root->Right);
    }
}

//Liệt các phân số ở mức thứ k (k là chiều cao của cây - 1)
void LietKePhanSoMucK(NODE* Root, int k, int i)
{
    if (Root != NULL)
    {
        if (i == k)
            printf("%d/%d\t", Root->data.tu, Root->data.mau);
        LietKePhanSoMucK(Root->Left, k, i + 1);
        LietKePhanSoMucK(Root->Right, k, i + 1);
    }
}

//Đếm số lượng phần tử ở mức thứ k
int DemPhanTuMucK(NODE* Root, int k, int i)
{
    if (Root == NULL)
        return 0;
    if (i == k)
        return 1;
    return DemPhanTuMucK(Root->Left, k, i + 1) + DemPhanTuMucK(Root->Right, k, i + 1);
}

//Tính chiều cao của cây
int ChieuCaoCay(NODE* Root)
{
    if (Root == NULL)
        return 0;
    int a = ChieuCaoCay(Root->Left);
    int b = ChieuCaoCay(Root->Right);
    return a > b ? a + 1 : b + 1;
}


//Tính tổng các phân số ở mức thứ k
value TongPhanSoMucK(NODE* Root, int k, int i)
{
    value sum;
    sum.tu = 0;
    sum.mau = 1;
    if (Root != NULL)
    {
        if (i == k)
            sum = Root->data;
        sum = CongPhanSo(sum, TongPhanSoMucK(Root->Left, k, i + 1));
        sum = CongPhanSo(sum, TongPhanSoMucK(Root->Right, k, i + 1));
    }
    return sum;
}

void LietKe(TREE t)
{
    printf("\n\n\t\t =========== LIET KE ===========");
    printf("\n1. Liet ke phan so co tu so lon hon mau so");
    printf("\n2. Liet ke phan so co tu so nho hon mau so");
    printf("\n3. Liet ke phan so co tu so va mau so la so nguyen to");
    printf("\n4. Liet ke phan so o muc k");
    printf("\n\n\t\t =========== END ===========");

    int luachon;
    printf("\nNhap lua chon: ");
    scanf_s("%d", &luachon);

    switch (luachon)
    {
    case 1:
    {
        printf("\n\n\t=========== LIET KE PHAN SO CO TU SO LON HON MAU SO ===========\n");
        printf("\t");
        LietKeTuSoLonHonMauSo(t.Root);
        _getch();
        break;
    }
    case 2:
    {
        printf("\n\n\t=========== LIET KE PHAN SO CO TU SO NHO HON MAU SO ===========\n");
        printf("\t");
        LietKeTuSoNhoHonMauSo(t.Root);
        _getch();
        break;
    }
    case 3: 
    {
        printf("\n\n\t=========== LIET KE PHAN SO CO TU SO VA MAU SO LA SO NGUYEN TO ===========\n");
        printf("\t");
        LietKePhanSoNguyenTo(t.Root);
        _getch();
        break;
    }
    case 4:
    {
        int k;
        printf("\nNhap muc k: ");
        scanf_s("%d", &k);
        printf("\n\n\t=========== LIET KE PHAN SO O MUC %d ===========\n", k);
        printf("\t");
        LietKePhanSoMucK(t.Root, k, 0);
        _getch();
        break;
    }
    default:
        printf("\nLua chon khong hop le");
        break;
    }
}

//hàm menu chức năng
void MENU(TREE &t)
{
    while (1!=0)
    {
        printf("\n\n\t\t =========== MENU ===========");
        printf("\n1. Nhap du lieu");
        printf("\n2. Xuat du lieu");
        printf("\n3. Them mot nut p la con trai/con phai cua nut T");
        printf("\n4. Dem nhung nut la phan so lon hon 1");
        printf("\n5. Toi gian tat ca cac nut trong cay");
        printf("\n6. Tim kiem nut co gia tri bang x");
        printf("\n7. Tinh tong cac nut trong cay");
        printf("\n8. Tim phan so lon nhat trong cay");
        printf("\n9. Tim phan so nho nhat trong cay");
        printf("\n10. Liet ke");
        printf("\n11. Dem so phan tu o muc thu k");
        printf("\n12. Tinh tong cac phan tu o muc thu k");
        printf("\n0. Thoat chuong trinh");
        printf("\n\n\t\t =========== END ===========");

        printf("\nNOTE: Nhap phan so voi dinh dang a/b\n");
        int luachon;
        printf("\nNhap lua chon: ");
        scanf_s("%d", &luachon);

        switch (luachon)
        {
        case 1:
        {
            nhap(t);
            break;
        }
        case 2:
        {
            xuat(t);
            break;
        }
        case 3:
        {
            value x;
            printf("\nNhap phan so can them: ");
            scanf_s("%d/%d", &x.tu, &x.mau);

            value y;
            printf("\nNhap gia tri nut T ban muon them sau: ");
            scanf_s("%d/%d", &y.tu, &y.mau);

            NODE* T = SearchNode(t, y);
            NODE* p = CreateNode(x);
            Insert_After_T(p, T);
            break;
        }
        case 4:
        {
            printf("\nSo luong nut la phan so lon hon 1 la: %d", DemNodeLonHon1(t.Root));
            _getch();
            break;
        }
        case 5:
        {
            ToiGian(t.Root);
            
            printf("\nDa thuc hien");
            _getch();
            break;
        }
        case 6:
        {
            value x;
            printf("\nNhap phan so can tim: ");
            scanf_s("%d/%d", &x.tu, &x.mau);

            if (SearchNode(t, x) != NULL)
                printf("\nTim thay");
            else
                printf("\nKhong tim thay");
            _getch();
            break;
        }
        case 7:
        {
            value sum = Tong(t.Root);
            printf("\nTong cac nut trong cay la: %d/%d", sum.tu, sum.mau);
            RutGonPhanSo(sum);
            printf("\nRut gon: %d/%d", sum.tu, sum.mau);
            _getch();
            break;
        }
        case 8:
        {
            value max = TimMax(t);
            printf("\nPhan so lon nhat trong cay la: %d/%d", max.tu, max.mau);
            _getch();
            break;
        }
        case 9:
        {
            value min = TimMin(t);
            printf("\nPhan so nho nhat trong cay la: %d/%d", min.tu, min.mau);
            _getch();
            break;
        }
        case 10:
        {
            LietKe(t);
            break;
        }
        case 11:
        {
            int k;
            printf("\nNhap muc k: ");
            scanf_s("%d", &k);
            printf("\nSo phan tu o muc %d la: %d", k, DemPhanTuMucK(t.Root, k, 0));
            _getch();
            break;
        }
        case 12:
        {
            int k;
            printf("\nNhap muc k: ");
            scanf_s("%d", &k);

            if (k > ChieuCaoCay(t.Root))
            {
                printf("\nMuc k khong hop le");
                _getch();
                break;
            }
            
            value sum = TongPhanSoMucK(t.Root, k, 0);
            printf("\nTong cac phan tu o muc %d la: %d/%d", k, sum.tu, sum.mau);

            RutGonPhanSo(sum);
            printf("\nRut gon: %d/%d", sum.tu, sum.mau);
            _getch();
            break;
        }
        case 0:
        {
            return;
            break;
        }
        }
    }   
}

int main() 
{
	TREE t;
	InitTree(t);
	MENU(t);
    return 0;
}
