#include "hash.h"
#include <bitset>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>

using namespace std;

string keiciaIvesti(string& input) {
    for (size_t i = 0; i < input.size(); ++i) {
        if (isalpha(input[i])) {
            if (isupper(input[i]) || input[i] == '?') {
                input[i] ^= (i % 8);
                input[i] += 3;
            } else {
                input[i] ^= (i + 5);
                input[i] -= 4;
            }
        } else {
            input[i] ^= (i % 6);
            input[i] += 1;
        }
    }

    reverse(input.begin(), input.end());
    return input;
}

string ivestis_i_bitus(string& input) {
    string bits;

    while (input.length() < 32) {
        input += 'k';
    }

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        bits += bitset<8>(static_cast<unsigned char>(c)).to_string();
    }
    return bits;
}

char hexas(char hexChar) {
    if (isdigit(hexChar)) {
        return (hexChar == '9') ? '0' : hexChar + 1;
    } else if (hexChar >= 'A' && hexChar <= 'F') {
        return (hexChar == 'F') ? 'A' : hexChar + 1;
    } else if (hexChar >= 'a' && hexChar <= 'f') {
        return (hexChar == 'f') ? 'a' : hexChar + 1;
    }
    return hexChar;
}

string sesiolika_bitu(string& bits, const string& originalInput) {
    while (bits.size() % 4 != 0) {
        bits = '0' + bits;
    }

    stringstream hexiukai;
    bool containsUpper = any_of(originalInput.begin(), originalInput.end(), ::isupper);
    bool containsExclamation = originalInput.find('!') != string::npos;

    int daugiklis = 1;
    if (containsUpper) {
        daugiklis = originalInput.length();
    } else if (containsExclamation) {
        daugiklis = originalInput.length() / 2;
    }

    srand(time(0));
    int pakaitine_reiksme = 1;

    for (size_t i = 0; i < bits.size(); i += 4) {
        string gabalas = bits.substr(i, 4);
        int value = stoi(gabalas, nullptr, 2);

        int kiek_originalus = originalInput[i / 4] % 16;
        pakaitine_reiksme += (kiek_originalus + 1);

        int randomShift = rand() % daugiklis;
        value *= (pakaitine_reiksme + randomShift);
        value = abs(value % 16);

        hexiukai << std::hex << value;
    }

    string hexo_rezas = hexiukai.str();

    for (size_t i = 0; i < hexo_rezas.length(); ++i) {
        hexo_rezas[i] = hexas(hexo_rezas[i]);
    }

    if (hexo_rezas.length() > 64) {
        hexo_rezas = hexo_rezas.substr(0, 64);
    } else {
        while (hexo_rezas.length() < 64) {
            hexo_rezas += '0';
        }
    }

    return hexo_rezas;
}

int suma(const string& input) {
    int sum = 0;
    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        if (std::isalpha(c)) {
            sum += std::tolower(c) - 'a' + 1;
        }
    }
    return sum;
}

string dauginti_bitus_is_sumos(string bits, int wordSum) {
    for (size_t i = 0; i < bits.size(); ++i) {
        if (bits[i] == '1') {
            bits[i] = (wordSum % 2) ? '1' : '0';
        } else {
            bits[i] = (wordSum % 2) ? '0' : '1';
        }
        wordSum /= 2;
        if (wordSum == 0) break;
    }
    return bits;
}

void apdoroja(const string& input, ofstream& outputFile) {
    string pakeista_ivestis = input + to_string(input.length());

    keiciaIvesti(pakeista_ivestis);
    string binaryResult = ivestis_i_bitus(pakeista_ivestis);
    int wordSum = suma(pakeista_ivestis);
    string pakeisti_bitai = dauginti_bitus_is_sumos(binaryResult, wordSum);
    string hashResult = sesiolika_bitu(pakeisti_bitai, pakeista_ivestis);

    outputFile << "hashas: " << hashResult << endl;
}
