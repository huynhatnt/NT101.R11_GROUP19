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
                ketQua += (c - 'A' + doDich) % 26 + 'A';
            else
                ketQua += (c - 'a' + doDich) % 26 + 'a';

            viTriKhoa++;
        }
        else
            ketQua += c;
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
                ketQua += (c - 'A' - doDich + 26) % 26 + 'A';
            else
                ketQua += (c - 'a' - doDich + 26) % 26 + 'a';

            viTriKhoa++;
        }
        else
            ketQua += c;
    }

    return ketQua;
}

string chuanHoa(string vanBan)
{
    string ketQua = "";

    for (char c : vanBan)
    {
        if (isalpha(c))
            ketQua += toupper(c);
    }

    return ketQua;
}

double tinhIC(string vanBan)
{
    int dem[26] = { 0 };
    int tongKyTu = vanBan.length();

    if (tongKyTu <= 1)
        return 0;

    for (char c : vanBan)
        dem[c - 'A']++;

    double tong = 0;

    for (int i = 0; i < 26; i++)
        tong += dem[i] * (dem[i] - 1);

    return tong / (tongKyTu * (tongKyTu - 1.0));
}

double tinhICTB(string vanBan, int doDaiKhoa)
{
    double tongIC = 0;

    for (int i = 0; i < doDaiKhoa; i++)
    {
        string nhom = "";

        for (int j = i; j < vanBan.length(); j += doDaiKhoa)
            nhom += vanBan[j];

        tongIC += tinhIC(nhom);
    }

    return tongIC / doDaiKhoa;
}

int timDoDaiKhoa(string vanBan)
{
    int doDaiTotNhat = 1;
    double icCaoNhat = 0;

    for (int doDai = 1; doDai <= 15; doDai++)
    {
        double ic = tinhICTB(vanBan, doDai);

        if (ic > icCaoNhat)
        {
            icCaoNhat = ic;
            doDaiTotNhat = doDai;
        }
    }

    return doDaiTotNhat;
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
    int tong = vanBan.length();

    for (char c : vanBan)
    {
        c = toupper(c);
        dem[c - 'A']++;
    }

    double diem = 0;

    for (int i = 0; i < 26; i++)
    {
        double mongDoi = tanSuat[i] * tong / 100;
        double saiLech = dem[i] - mongDoi;

        if (mongDoi > 0)
            diem += saiLech * saiLech / mongDoi;
    }

    return diem;
}

char timKyTuKhoa(string nhom)
{
    double diemTotNhat = 1000000;
    int khoaTotNhat = 0;

    for (int khoa = 0; khoa < 26; khoa++)
    {
        string banRo = "";

        for (char c : nhom)
            banRo += (c - 'A' - khoa + 26) % 26 + 'A';

        double diem = tinhDiem(banRo);

        if (diem < diemTotNhat)
        {
            diemTotNhat = diem;
            khoaTotNhat = khoa;
        }
    }

    return 'A' + khoaTotNhat;
}

string timKhoa(string vanBan, int doDaiKhoa)
{
    string khoa = "";

    for (int i = 0; i < doDaiKhoa; i++)
    {
        string nhom = "";

        for (int j = i; j < vanBan.length(); j += doDaiKhoa)
            nhom += vanBan[j];

        char kyTuKhoa = timKyTuKhoa(nhom);
        khoa += kyTuKhoa;
    }

    return khoa;
}

int main()
{
    int luaChon;
    string vanBan;
    string khoa;

    cout << "1. Ma hoa" << endl;
    cout << "2. Giai ma" << endl;
    cout << "3. Khong biet khoa" << endl;
    cout << "Chon: ";
    cin >> luaChon;
    cin.ignore();

    if (luaChon == 1)
    {
        cout << "Nhap ban ro: ";
        getline(cin, vanBan);

        cout << "Nhap khoa: ";
        getline(cin, khoa);

        cout << "Ban ma: "
            << maHoaVigenere(vanBan, khoa) << endl;
    }
    else if (luaChon == 2)
    {
        cout << "Nhap ban ma: ";
        getline(cin, vanBan);

        cout << "Nhap khoa: ";
        getline(cin, khoa);

        cout << "Ban ro: "
            << giaiMaVigenere(vanBan, khoa) << endl;
    }
    else if (luaChon == 3)
    {
        cout << "Nhap ban ma: ";
        getline(cin, vanBan);

        string banMaChuan = chuanHoa(vanBan);

        int doDaiKhoa = timDoDaiKhoa(banMaChuan);

        string khoaDuDoan = timKhoa(banMaChuan, doDaiKhoa);

        string banRo = giaiMaVigenere(vanBan, khoaDuDoan);

        cout << endl;
        cout << "Do dai khoa du doan: "
            << doDaiKhoa << endl;

        cout << "Khoa du doan: "
            << khoaDuDoan << endl;

        cout << "Ban ro du doan: "
            << banRo << endl;
    }
    else
    {
        cout << "Lua chon khong hop le." << endl;
    }

    return 0;
}