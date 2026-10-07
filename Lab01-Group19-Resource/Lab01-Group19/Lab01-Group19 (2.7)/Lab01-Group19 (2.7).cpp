#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int ucln(int a, int b)
{
    while (b != 0)
    {
        int du = a % b;
        a = b;
        b = du;
    }

    return a;
}

int nghichDaoModulo(int a)
{
    for (int i = 1; i < 26; i++)
    {
        if ((a * i) % 26 == 1)
            return i;
    }

    return -1;
}

string maHoaAffine(string vanBan, int a, int b)
{
    string ketQua = "";

    for (char c : vanBan)
    {
        if (isalpha(c))
        {
            if (isupper(c))
            {
                int p = c - 'A';
                int maHoa = (a * p + b) % 26;

                ketQua += maHoa + 'A';
            }
            else
            {
                int p = c - 'a';
                int maHoa = (a * p + b) % 26;

                ketQua += maHoa + 'a';
            }
        }
        else
        {
            ketQua += c;
        }
    }

    return ketQua;
}

string giaiMaAffine(string vanBan, int a, int b)
{
    string ketQua = "";
    int nghichDao = nghichDaoModulo(a);

    for (char c : vanBan)
    {
        if (isalpha(c))
        {
            if (isupper(c))
            {
                int cSo = c - 'A';
                int giaiMa = (nghichDao * (cSo - b + 26)) % 26;

                ketQua += giaiMa + 'A';
            }
            else
            {
                int cSo = c - 'a';
                int giaiMa = (nghichDao * (cSo - b + 26)) % 26;

                ketQua += giaiMa + 'a';
            }
        }
        else
        {
            ketQua += c;
        }
    }

    return ketQua;
}

int main()
{
    int luaChon;
    int a, b;
    string vanBan;

    cout << "1. Ma hoa" << endl;
    cout << "2. Giai ma" << endl;
    cout << "Chon: ";
    cin >> luaChon;

    cout << "Nhap a: ";
    cin >> a;

    cout << "Nhap b: ";
    cin >> b;

    cin.ignore();

    if (ucln(a, 26) != 1)
    {
        cout << "Khoa a khong hop le." << endl;
        return 0;
    }

    if (luaChon == 1)
    {
        cout << "Nhap ban ro: ";
        getline(cin, vanBan);

        cout << "Ban ma: "
            << maHoaAffine(vanBan, a, b) << endl;
    }
    else if (luaChon == 2)
    {
        cout << "Nhap ban ma: ";
        getline(cin, vanBan);

        cout << "Ban ro: "
            << giaiMaAffine(vanBan, a, b) << endl;
    }
    else
    {
        cout << "Lua chon khong hop le." << endl;
    }

    return 0;
}