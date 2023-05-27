#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<time.h>


struct Phanso
{
    int tu;
    int mau;
};


struct BinaryNode
{
    Phanso data;
    BinaryNode *left;
    BinaryNode *right;
};

struct BinaryTree
{
    BinaryNode *root;
};


void init_BinaryTree(BinaryTree &t)
{
    t.root = NULL;
}

BinaryNode *createBinaryNode(Phanso x)
{
    BinaryNode *p = new BinaryNode;
    if (p == NULL)
    {
        printf("\nKhong du bo nho cap phat!!");
        return NULL;
    }

    p->data = x;
    p->left = NULL;
    p->right = NULL;

    return p;
}

int isEmpty(BinaryTree t)
{
    if (t.root == NULL)
        return 0;
    return 1;
}

int CompareFraction(Phanso x1, Phanso x2)
{
    if (x1.tu * x2.mau > x2.tu * x1.mau)
        return 1;
    else if (x1.tu * x2.mau < x2.tu * x1.mau)
        return -1;
    else
        return 0;
}

//Add Binary Node
void add_BinaryNode(BinaryNode *&root, BinaryNode *p)
{
    if (root == NULL)
    {
        root = p;
        return;
    }

    if (CompareFraction(root->data, p->data) == 1)
        add_BinaryNode(root->left, p);
    else if (CompareFraction(root->data, p->data) == -1)
        add_BinaryNode(root->right, p);
}

int Check_Fraction(Phanso x)
{
    if (x.mau == 0)
        return 0;
    return 1;
}

void Enter_Fraction(Phanso &x)
{
    printf("\nNhap vao gia tri cua phan so: ");
    do 
    {
        scanf("%d/%d", &x.tu, &x.mau);
        if (Check_Fraction(x) == 0)
            printf("\nNhap lai gia tri cua phan so: ");
    } while (Check_Fraction(x) == 0);
}

//Create Binary Tree from data in Keyboard
void Create_BinaryTree_DataFromKeyBoard(BinaryTree &t)
{
    int n;
    printf("\nNhap vao so luong node muon tao: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        Phanso x;
        printf("\nPhan so thu %d: ", i + 1);
        Enter_Fraction(x);

        BinaryNode *p = createBinaryNode(x);
        add_BinaryNode(t.root, p);
    }
}

//Create Binary Tree from data in Array
void Create_BinaryTree_DataFromArray(BinaryTree &t)
{
    int n;
    printf("\nNhap vao so luong node muon tao: ");
    scanf("%d", &n);

    Phanso a[100];
    printf("\nNhap vao mang phan so: ");
    for (int i = 0; i < n; i++)
    {
        printf("\nPhan so thu %d: ", i + 1);
        Enter_Fraction(a[i]);
    }

    for (int i = 0; i < n; i++)
    {
        BinaryNode *p = createBinaryNode(a[i]);
        add_BinaryNode(t.root, p);
    }
}

//Create Binary Tree random
void Create_BinaryTree_Random(BinaryTree &t)
{
    int n;
    printf("\nNhap va so luong node muon tao: ");
    scanf("%d", &n);
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        Phanso x;
        do
        {
            x.tu = rand() % 100;
            x.mau = rand() % 100;
        } while (Check_Fraction(x) == 0);
        
        BinaryNode *p = createBinaryNode(x);
        add_BinaryNode(t.root, p);
    }
}

//Traverse Binary Tree by 6 ways

void Traverse_NLR(BinaryNode *root)
{
    if (root == NULL)
        return;

    printf("%d/%d ", root->data.tu, root->data.mau);
    Traverse_NLR(root->left);
    Traverse_NLR(root->right);
}

void Traverse_LNR(BinaryNode *root)
{
    if (root == NULL)
        return;

    Traverse_LNR(root->left);
    printf("%d/%d ", root->data.tu, root->data.mau);
    Traverse_LNR(root->right);
}

void Traverse_LRN(BinaryNode *root)
{
    if (root == NULL)
        return;

    Traverse_LRN(root->left);
    Traverse_LRN(root->right);
    printf("%d/%d ", root->data.tu, root->data.mau);
}

void Traverse_NRL(BinaryNode *root)
{
    if (root == NULL)
        return;

    printf("%d/%d ", root->data.tu, root->data.mau);
    Traverse_LRN(root->right);
    Traverse_LRN(root->left);
}

void Traverse_RNL(BinaryNode *root)
{
    if (root == NULL)
        return;

    Traverse_LRN(root->right);
    printf("%d/%d ", root->data.tu, root->data.mau);
    Traverse_LRN(root->left);
}

void Traverse_RLN(BinaryNode *root)
{
    if (root == NULL)
        return;

    Traverse_LRN(root->right);
    Traverse_LRN(root->left);
    printf("%d/%d ", root->data.tu, root->data.mau);
}

//Find node in Binary Tree
BinaryNode *find_BinaryNode(BinaryNode *root, Phanso x)
{
    if (root == NULL)
        return NULL;
    
    if (CompareFraction(root->data, x) == 0)
        return root;
    else if (CompareFraction(root->data, x) == 1)
        find_BinaryNode(root->left, x);
    else
        find_BinaryNode(root->right, x);

}

//Add node p to right/left of node T
void add_p_to_T(BinaryNode *p, BinaryNode *T)
{
    if (T == NULL || p == NULL)
    {
        printf("\nKhong the them node p vao node T");
        _getch();
        return;
    }

    if (T->left != NULL && T->right != NULL)
    {
        printf("\nNode T da co 2 con");
        _getch();
        return;
    }
    else if (T->left == NULL && CompareFraction(p->data, T->data) == -1)
        T->left = p;
    else if (T->right == NULL && CompareFraction(p->data, T->data) == 1)
        T->right = p;
    else
    {
        printf("\nKhong the them node p vao node T");
        _getch();
        return;
    }
}

//Cout node data bigger than 1
int Count_BiggerThan1(BinaryNode *root)
{
    if (root == NULL)
        return 0;

    Phanso x;
    x.tu = 1;
    x.mau = 1;
    if (CompareFraction(root->data, x) == 1)
        return 1 + Count_BiggerThan1(root->left) + Count_BiggerThan1(root->right);
    else
        return Count_BiggerThan1(root->left) + Count_BiggerThan1(root->right);
}

//Greatest common divisor
int UCLN(int a, int b)
{
    a = abs(a);
    b = abs(b);
    if (a == 0 || b == 0)
        return a + b;

    while (a != b)
    {
        if (a > b)
            a -= b;
        else
            b -= a;
    }

    return a;
}

Phanso Simplify_Fraction(Phanso x)
{
    int ucln = UCLN(x.tu, x.mau);
    x.tu /= ucln;
    x.mau /= ucln;
    return x;
}

//Simplify all node in Binary Tree
void Simplify_BinaryTree(BinaryNode *root)
{
    if (root == NULL)
        return;

    root->data = Simplify_Fraction(root->data);
    Simplify_BinaryTree(root->left);
    Simplify_BinaryTree(root->right);
}

void Enter_Data(BinaryTree &t)
{
    printf("\n\t================ ENTER DATA ================");
    printf("\n1. Nhap du lieu tu ban phim");
    printf("\n2. Nhap du lieu ngau nhien");
    printf("\n3. Nhap du lieu tu mang");

    int luachon;
    printf("\nNhap lua chon: ");
    scanf("%d", &luachon);

    switch (luachon)
    {
        case 1:
        {
            Create_BinaryTree_DataFromKeyBoard(t);
            break;
        }
        case 2:
        {
            Create_BinaryTree_Random(t);
            break;
        }
        case 3:
        {
            Create_BinaryTree_DataFromArray(t);
            break;
        }
        default:
        {
            printf("\nLua chon khong hop le");
            _getch();
            break;
        }
    }

}

void Traverse_BinaryTree(BinaryTree t)
{
    printf("\n\t================ TRAVERSE BINARY TREE ================");
    printf("\n1. NLR");
    printf("\n2. LNR");
    printf("\n3. LRN");
    printf("\n4. NRL");
    printf("\n5. RNL");
    printf("\n6. RLN");

    int luachon;
    printf("\nNhap lua chon: ");
    scanf("%d", &luachon);

    switch (luachon)
    {
        case 1:
        {
            Traverse_NLR(t.root);
            break;
        }
        case 2:
        {
            Traverse_LNR(t.root);
            break;
        }
        case 3:
        {
            Traverse_LRN(t.root);
            break;
        }
        case 4:
        {
            Traverse_NRL(t.root);
            break;
        }
        case 5:
        {
            Traverse_RNL(t.root);
            break;
        }
        case 6:
        {
            Traverse_RLN(t.root);
            break;
        }
        default:
        {
            printf("\nLua chon khong hop le");
            _getch();
            break;
        }
    }
}

//Add Fraction
Phanso AddFraction(Phanso a, Phanso b)
{
    Phanso x;
    x.tu = a.tu * b.mau + a.mau * b.tu;
    x.mau = a.mau * b.mau;
    return x;
}

//Sum all node in Binary Tree
Phanso Sum_AllNode(BinaryNode *root)
{
    if (root == NULL)
    {
        Phanso x;
        x.tu = 0;
        x.mau = 1;
        return x;
    }

    return AddFraction(root->data, AddFraction(Sum_AllNode(root->left), Sum_AllNode(root->right)));
}

//Find Fraction max
Phanso findFraction_max(BinaryTree t)
{
    if (t.root == NULL)
    {
        Phanso x;
        x.tu = 0;
        x.mau = 1;
        return x;
    }

    Phanso x = t.root->data;
    BinaryNode *p = t.root;

    while (p != NULL)
    {
        if (CompareFraction(p->data, x) == 1)
            x = p->data;
        p = p->right;
    }

    return x;
}

//Find Fraction min
Phanso findFraction_min(BinaryTree t)
{
    if (t.root == NULL)
    {
        Phanso x;
        x.tu = 0;
        x.mau = 1;
        return x;
    }

    Phanso x = t.root->data;
    BinaryNode *p = t.root;

    while (p != NULL)
    {
        if (CompareFraction(p->data, x) == -1)
            x = p->data;
        p = p->left;
    }

    return x;
}


//Check fraction have numeratoe is greater than denominator
int Check_Fraction_Numerator_Demoninator(Phanso x)
{
    if (x.tu > x.mau)
        return 1;
    return 0;
}

//List node data whose numerator is greater than denominator
void List_NodeData_GreaterThan(BinaryNode *root)
{
    if (root == NULL)
        return;

    if (Check_Fraction_Numerator_Demoninator(root->data) == 1)
        printf("%d/%d\t", root->data.tu, root->data.mau);

    List_NodeData_GreaterThan(root->left);
    List_NodeData_GreaterThan(root->right);
}

//Check prime number
int Check_PrimeNumber(int n)
{
    if (n < 2)
        return 0;

    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return 0;

    return 1;
}

//Check fraction whose numerator and denominator are prime number
int Check_PrimeFraction(Phanso x)
{
    if (Check_PrimeNumber(x.tu) == 1 && Check_PrimeNumber(x.mau) == 1)
        return 1;
    return 0;
}

//List node data whose numerator and denominator are prime number
void List_NodeData_PrimeFraction(BinaryNode *root)
{
    if (root == NULL)
        return;

    if (Check_PrimeFraction(root->data) == 1)
        printf("%d/%d\t", root->data.tu, root->data.mau);

    List_NodeData_PrimeFraction(root->left);
    List_NodeData_PrimeFraction(root->right);
}

void List_NodeData_High_k(BinaryNode *root, int k, int i)
{
    if (root == NULL)
        return;

    if (i == k)
        printf("%d/%d\t", root->data.tu, root->data.mau);

    List_NodeData_High_k(root->left, k, i + 1);
    List_NodeData_High_k(root->right, k, i + 1);
}

int Height_BinaryTree(BinaryNode *root)
{
    if (root == NULL)
        return 0;

    int left_height = Height_BinaryTree(root->left);
    int right_height = Height_BinaryTree(root->right);

    if (left_height > right_height)
        return left_height + 1;
    return right_height + 1;
}

void List(BinaryTree t)
{
    printf("\n\t================ LIST ================");
    printf("\n1. Liet ke cac phan so co tu so lon hon mau so");
    printf("\n2. Liet ke cac phan so co tu so va mau so la so nguyen to");
    printf("\n3. Liet ke cac phan so o muc k");

    int luachon;
    printf("\nNhap lua chon: ");
    scanf("%d", &luachon);

    switch (luachon)
    {
        case 1:
        {
            printf("\nCac phan so co tu so lon hon mau so la: ");
            List_NodeData_GreaterThan(t.root);
            break;
        }
        case 2:
        {
            printf("\nCac phan so co tu so va mau so la so nguyen to la: ");
            List_NodeData_PrimeFraction(t.root);
            break;
        }
        case 3:
        {
            int k;
            printf("\nNhap k: ");
            scanf("%d", &k);

            if (k < 0 || k > Height_BinaryTree(t.root))
            {
                printf("\nMuc k khong hop le");
                _getch();
                break;
            }
            printf("\nCac phan so o muc %d la: ", k);
            List_NodeData_High_k(t.root, k, 0);
            break;
        }
        default:
        {
            printf("\nLua chon khong hop le");
            break;
        }
    }
}

//Cout node in height k
int Count_NodeInHeight_k(BinaryNode *root, int k, int i)
{
    if (root == NULL)
        return 0;

    if (i == k)
        return 1;

    return Count_NodeInHeight_k(root->left, k, i + 1) + Count_NodeInHeight_k(root->right, k, i + 1);
}

//Sum node in height k
Phanso Sum_NodeInHeight_k(BinaryNode *root, int k, int i)
{
    if (root == NULL)
    {
        Phanso x;
        x.tu = 0;
        x.mau = 1;
        return x;
    }

    if (i == k)
        return root->data;

    return AddFraction(Sum_NodeInHeight_k(root->left, k, i + 1), Sum_NodeInHeight_k(root->right, k, i + 1));
}

void MENU(BinaryTree &t)
{
    while (1 != 0)
    {
        system("cls");
        printf("\n\t================ MENU ================");
        printf("\n1. Nhap du lieu cho cay");
        printf("\n2. Duyet cay");
        printf("\n3. Them node moi (p) vao sau node T");
        printf("\n4. Dem so luong node co gia tri lon hon 1");
        printf("\n5. Toi gian toan bo cay");
        printf("\n6. Tim node co gia tri x");
        printf("\n7. Tong toan bo cay");
        printf("\n8. Tim phan so lon nhat");
        printf("\n9. TIm phan so nho nhat");
        printf("\n10. Liet ke cac phan so");
        printf("\n11. Dem so luong node o muc k");
        printf("\n12. Tinh tong cac node o muc k");
        printf("\n0. Thoat");
        printf("\n\t================ END ================");

        int luachon;
        printf("\nNhap lua chon: ");
        scanf("%d", &luachon);

        switch (luachon)
        {
            case 1:
            {
                Enter_Data(t);
                break;
            }
            case 2:
            {
                Traverse_BinaryTree(t);
                _getch();
                break;
            }
            case 3:
            {
                Phanso x;
                printf("\nNhap gia tri node p: ");
                Enter_Fraction(x);
                BinaryNode *p = createBinaryNode(x);

                Phanso y;
                printf("\nNhap gia tri node T: ");
                Enter_Fraction(y);
                BinaryNode *T = find_BinaryNode(t.root, y);

                add_p_to_T(p, T);
                break;
            }
            case 4:
            {
                printf("\nSo luong node co gia tri lon hon 1: %d", Count_BiggerThan1(t.root));
                _getch();
                break;
            }
            case 5:
            {
                Simplify_BinaryTree(t.root);
                printf("\nDa toi gian toan bo cay");
                _getch();
                break;
            }
            case 6:
            {
                Phanso x;
                printf("\nNhap phan so x: ");
                Enter_Fraction(x);
                BinaryNode *p = find_BinaryNode(t.root, x);

                if (p == NULL)
                    printf("\nKhong tim thay node co gia tri x");
                else
                    printf("\nTim thay node co gia tri x");
                _getch();
                break;
            }
            case 7:
            {
                Phanso sum = Sum_AllNode(t.root);
                printf("\nTong toan bo cay: %d/%d", sum.tu, sum.mau);
                sum = Simplify_Fraction(sum);
                printf("\nRut gon: %d/%d", sum.tu, sum.mau);
                _getch();
                break;
            }
            case 8:
            {
                Phanso x = findFraction_max(t);
                printf("\nPhan so lon nhat: %d/%d", x.tu, x.mau);
                _getch();
                break;
            }
            case 9:
            {
                Phanso x = findFraction_min(t);
                printf("\nPhan so nho nhat: %d/%d", x.tu, x.mau);
                _getch();
                break;
            }
            case 10:
            {
                List(t);
                _getch();
                break;
            }
            case 11:
            {
                int k;
                printf("\nNhap k: ");
                scanf("%d", &k);

                if (k < 0 || k > Height_BinaryTree(t.root))
                {
                    printf("\nMuc k khong hop le");
                    _getch();
                    break;
                }
                printf("\nSo luong node o muc %d la: %d", k, Count_NodeInHeight_k(t.root, k, 0));
                _getch();
                break;
            }
            case 12:
            {
                int k;
                printf("\nNhap k: ");
                scanf("%d", &k);

                if (k < 0 || k > Height_BinaryTree(t.root))
                {
                    printf("\nMuc k khong hop le");
                    _getch();
                    break;
                }
                Phanso sum = Sum_NodeInHeight_k(t.root, k, 0);
                printf("\nTong cac node o muc %d: %d/%d", k, sum.tu, sum.mau);
                sum = Simplify_Fraction(sum);
                printf("\nRut gon: %d/%d", sum.tu, sum.mau);
                _getch();
                break;
            }
            case 0: return;
                break;
            
            default:
            {
                printf("\nLua chon khong hop le");
                break;
            }
        }
    }
}

int main()
{
    BinaryTree t;
    init_BinaryTree(t);

    MENU(t);

    return 0;
}