#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cmath>
#include <cctype>
#include <random>
using namespace std;

class FitnessScorer {
private:
    unordered_map< string, double > ngrams;
    double floor_score;

public:
    FitnessScorer(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Loi: Khong the mo file " << filename << endl;
            exit(1);
        }

        string key;
        long long count;
        long long total_N = 0;

        unordered_map< string, long long > temp_counts;
        while (file >> key >> count) {
            temp_counts[key] = count;
            total_N += count;
        }
        file.close();

        for (const auto& pair : temp_counts) {
            ngrams[pair.first] = log10((double)pair.second / total_N);
        }

        floor_score = log10(0.01 / total_N);
    }

    double score(const string& text) {
        double current_score = 0;
        string clean_text = "";

        for (char c : text) {
            if (isalpha((unsigned char)c)) {
                clean_text += toupper((unsigned char)c);
            }
        }

        if (clean_text.length() < 4) return current_score;

        for (size_t i = 0; i <= clean_text.length() - 4; ++i) {
            string quadgram = clean_text.substr(i, 4);
            auto it = ngrams.find(quadgram);
            if (it != ngrams.end()) {
                current_score += it->second;
            }
            else {
                current_score += floor_score;
            }
        }

        return current_score;
    }
};
string decrypt(const string& ciphertext, const string& key) {
    string plaintext = "";
    for (char c : ciphertext) {
        if (isalpha((unsigned char)c)) {
            bool is_lower = islower((unsigned char)c);
            int index = toupper((unsigned char)c) - 'A';
            char decrypted_char = key[index];
            plaintext += is_lower ? tolower((unsigned char)decrypted_char) : decrypted_char;
        }
        else {
            plaintext += c;
        }
    }
    return plaintext;
}

string hillClimbing(const string& ciphertext, FitnessScorer& scorer, double& out_best_score) {
    string best_key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    random_device rd;
    mt19937 g(rd());
    shuffle(best_key.begin(), best_key.end(), g);

    string best_plaintext = decrypt(ciphertext, best_key);
    double best_score = scorer.score(best_plaintext);

    int count_no_improvement = 0;

    while (count_no_improvement < 1000) {
        string child_key = best_key;

        int a = rand() % 26;
        int b = rand() % 26;
        swap(child_key[a], child_key[b]);

        string child_plaintext = decrypt(ciphertext, child_key);
        double child_score = scorer.score(child_plaintext);

        if (child_score > best_score) {
            best_score = child_score;
            best_key = child_key;
            count_no_improvement = 0;
        }
        else {
            count_no_improvement++;
        }
    }

    out_best_score = best_score;
    return best_key;
}

int main() {
    srand((unsigned)time(0));

    FitnessScorer scorer("english_quadgrams.txt");

    ifstream inFile("ciphertext.txt");
    if (!inFile.is_open()) {
        cout << "Loi: Khong the mo file ciphertext.txt!\n";
        cout << "Vui long tao file ciphertext.txt chua doan ma va dat cung thu muc voi file chay.\n";
        return 1;
    }

    string ciphertext;
    string line;
    while (getline(inFile, line)) {
        ciphertext += line + "\n";
    }
    inFile.close();

    int num_restarts = 15;
    double global_best_score = -99999999.0;
    string global_best_key = "";
    string global_best_plaintext = "";

    cout << "Dang giai ma vui long doi...\n";

    for (int i = 0; i < num_restarts; i++) {
        double local_best_score;
        string local_best_key = hillClimbing(ciphertext, scorer, local_best_score);

        if (local_best_score > global_best_score) {
            global_best_score = local_best_score;
            global_best_key = local_best_key;
            global_best_plaintext = decrypt(ciphertext, global_best_key);
        }
    }

    cout << "Ban ro (Plaintext):\n" << global_best_plaintext << "\n";

    return 0;
}