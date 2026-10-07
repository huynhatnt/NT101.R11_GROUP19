#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Hàm chuẩn hóa chuỗi (Viết hoa, loại khoảng trắng, J -> I)
string formatString(string text) {
    string result = "";
    for (char c : text) {
        if (isalpha((unsigned char)c)) {
            c = toupper((unsigned char)c);
            if (c == 'J') c = 'I';
            result += c;
        }
    }
    return result;
}

// Hàm tạo ma trận 5x5 từ khóa
void generateMatrix(string key, char matrix[5][5]) {
    string formattedKey = formatString(key);
    bool used[26] = { false };
    used['J' - 'A'] = true; // Xem J như I, đánh dấu J đã dùng

    string matrixContent = "";

    // Đưa khóa vào ma trận
    for (char c : formattedKey) {
        if (!used[c - 'A']) {
            matrixContent += c;
            used[c - 'A'] = true;
        }
    }

    // Đưa các chữ cái còn lại vào
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            matrixContent += c;
            used[c - 'A'] = true;
        }
    }

    // Đổ vào mảng 2 chiều 5x5 và in ra màn hình
    cout << "\n--- MA TRAN PLAYFAIR 5x5 ---" << endl;
    int index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = matrixContent[index++];
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "----------------------------\n" << endl;
}

// Hàm tìm tọa độ của một ký tự trong ma trận
void getPosition(char matrix[5][5], char c, int& row, int& col) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

// Hàm xử lý chung cho Mã hóa và Giải mã
string processPlayfair(string text, char matrix[5][5], bool encrypt) {
    text = formatString(text);
    string preparedText = "";

    // Xử lý chèn X nếu 2 ký tự cạnh nhau giống nhau (chỉ dùng khi mã hóa)
    if (encrypt) {
        for (size_t i = 0; i < text.length(); i++) {
            preparedText += text[i];
            if (i + 1 < text.length() && text[i] == text[i + 1]) {
                preparedText += 'X';
            }
        }
        if (preparedText.length() % 2 != 0) {
            preparedText += 'X';
        }
    }
    else {
        preparedText = text; // Giải mã thì giữ nguyên
    }

    string result = "";
    int shift = encrypt ? 1 : -1; // Mã hóa cộng 1, giải mã trừ 1

    for (size_t i = 0; i < preparedText.length(); i += 2) {
        char a = preparedText[i];
        char b = preparedText[i + 1];
        int r1, c1, r2, c2;

        getPosition(matrix, a, r1, c1);
        getPosition(matrix, b, r2, c2);

        if (r1 == r2) { // Cùng hàng
            result += matrix[r1][(c1 + shift + 5) % 5];
            result += matrix[r2][(c2 + shift + 5) % 5];
        }
        else if (c1 == c2) { // Cùng cột
            result += matrix[(r1 + shift + 5) % 5][c1];
            result += matrix[(r2 + shift + 5) % 5][c2];
        }
        else { // Hình chữ nhật
            result += matrix[r1][c2];
            result += matrix[r2][c1];
        }
    }
    return result;
}

int main() {
    int choice;
    string key, text;
    char matrix[5][5];

    cout << "1. Ma hoa (Encrypt)" << endl;
    cout << "2. Giai ma (Decrypt)" << endl;
    cout << "Chon chuc nang (1/2): ";
    cin >> choice;
    cin.ignore(); // Xóa bộ đệm bàn phím

    cout << "Nhap khoa (Key): ";
    getline(cin, key);

    generateMatrix(key, matrix);

    cout << "Nhap van ban: ";
    getline(cin, text);

    if (choice == 1) {
        string cipher = processPlayfair(text, matrix, true);
        cout << "=> Ciphertext: " << cipher << endl;
    }
    else if (choice == 2) {
        string plain = processPlayfair(text, matrix, false);
        cout << "=> Plaintext (Chua loai bo chu X): " << plain << endl;
    }
    else {
        cout << "Lua chon khong hop le!" << endl;
    }

    return 0;
}
