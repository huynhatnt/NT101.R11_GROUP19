#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string maHoaVigenere(string vanBan, string khoa)
{
    string ketQua = "";
    int viTriKhoa = 0;

    for (char c : vanBan)
    {
        if (isalpha(c))
        {
            char kyTuKhoa = toupper(khoa[viTriKhoa % khoa.length()]);
            int doDich = kyTuKhoa - 'A';

            if (isupper(c))
            {
                ketQua += (c - 'A' + doDich) % 26 + 'A';
            }
            else
            {
                ketQua += (c - 'a' + doDich) % 26 + 'a';
            }

            viTriKhoa++;
        }
        else
        {
            ketQua += c;
        }
    }

    return ketQua;
}

string giaiMaVigenere(string vanBan, string khoa)
{
    string ketQua = "";
    int viTriKhoa = 0;

    for (char c : vanBan)
    {
        if (isalpha(c))
        {
            char kyTuKhoa = toupper(khoa[viTriKhoa % khoa.length()]);
            int doDich = kyTuKhoa - 'A';

            if (isupper(c))
            {
                ketQua += (c - 'A' - doDich + 26) % 26 + 'A';
            }
            else
            {
                ketQua += (c - 'a' - doDich + 26) % 26 + 'a';
            }

            viTriKhoa++;
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
    int chon;
    string vanBan;
    string khoa;

    cout << "1. Ma hoa Vigenere" << endl;
    cout << "2. Giai ma Vigenere" << endl;
    cout << "Chon: ";
    cin >> chon;
    cin.ignore();

    cout << "Nhap van ban: ";
    getline(cin, vanBan);

    cout << "Nhap khoa: ";
    cin >> khoa;

    if (chon == 1)
    {
        cout << "Ban ma: " << maHoaVigenere(vanBan, khoa) << endl;
    }
    else if (chon == 2)
    {
        cout << "Ban ro: " << giaiMaVigenere(vanBan, khoa) << endl;
    }

    return 0;
}