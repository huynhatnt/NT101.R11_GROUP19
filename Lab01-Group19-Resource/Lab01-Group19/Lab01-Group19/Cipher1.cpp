#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string maHoa(string vanBan, int khoa)
{
    string ketQua = "";

    for (char c : vanBan)
    {
        if (isupper(c))
        {
            ketQua += (c - 'A' + khoa) % 26 + 'A';
        }
        else if (islower(c))
        {
            ketQua += (c - 'a' + khoa) % 26 + 'a';
        }
        else
        {
            ketQua += c;
        }
    }
    return ketQua;
}

string giaiMa(string vanBan, int khoa)
{
    string ketQua = "";

    for (char c : vanBan)
    {
        if (isupper(c))
        {
            ketQua += (c - 'A' - khoa + 26) % 26 + 'A';
        }
        else if (islower(c))
        {
            ketQua += (c - 'a' - khoa + 26) % 26 + 'a';
        }
        else
        {
            ketQua += c;
        }
    }
    return ketQua;
}
double tinhDiem(string vanBan)
{
    double tanSuat[26] = {
        8.17, 1.49, 2.78, 4.25, 12.70, 2.23,
        2.02, 6.09, 6.97, 0.15, 0.77, 4.03,
        2.41, 6.75, 7.51, 1.93, 0.10, 5.99,
        6.33, 9.06, 2.76, 0.98, 2.36, 0.15,
        1.97, 0.07
    };

    int dem[26] = { 0 };
    int tong = 0;

    for (char c : vanBan)
    {
        if (isupper(c))
        {
            dem[c - 'A']++;
            tong++;
        }
        else if (islower(c))
        {
            dem[c - 'a']++;
            tong++;
        }
    }

    double diem = 0;

    for (int i = 0; i < 26; i++)
    {
        double mongDoi = tanSuat[i] * tong / 100;
        double saiLech = dem[i] - mongDoi;

        if (mongDoi > 0)
        {
            diem += saiLech * saiLech / mongDoi;
        }
    }

    return diem;
}

void bruteF(string banMa)
{
    int khoaDung = 0;
    string banRoDung = "";
    double diemDung = 1000000;

    for (int khoa = 1; khoa <= 25; khoa++)
    {
        string banRo = giaiMa(banMa, khoa);
        double diem = tinhDiem(banRo);

        if (diem < diemDung)
        {
            diemDung = diem;
            khoaDung = khoa;
            banRoDung = banRo;
        }
    }

    cout << "Khoa: " << khoaDung << endl;
    cout << "Ban ro: " << banRoDung << endl;
}


int main()
{
    int chon;
    string vanBan;
    int khoa;

    cout << "1. Ma hoa" << endl;
    cout << "2. Giai ma" << endl;
    cout << "3. Brute-force" << endl;
    cout << "Chon: ";
    cin >> chon;
    cin.ignore();

    cout << "Nhap van ban: ";
    getline(cin, vanBan);

    if (chon == 1)
    {
        cout << "Nhap khoa: ";
        cin >> khoa;

        cout << "Ban ma: " << maHoa(vanBan, khoa) << endl;
    }
    else if (chon == 2)
    {
        cout << "Nhap khoa: ";
        cin >> khoa;

        cout << "Ban ro: " << giaiMa(vanBan, khoa) << endl;
    }
    else if (chon == 3)
    {
        bruteF(vanBan);
    }

    return 0;
}



