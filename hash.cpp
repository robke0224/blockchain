#include "hash.h"
#include <bitset>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <random>

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

///////////////////////////////////////////////////////////////////////////////////////////
// Generates a file with a single repeated character
void create_single_char_file(const std::string& filename, char c, size_t size) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (size_t i = 0; i < size; ++i) {
            file << c;
        }
        file.close();
    }
}

// Generates a file with random characters of specified length
void create_random_char_file(const std::string& filename, size_t size) {
    std::ofstream file(filename);
    if (file.is_open()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(32, 126);  // Printable ASCII chars

        for (size_t i = 0; i < size; ++i) {
            file << static_cast<char>(dis(gen));  // Cast integer to char
        }
        file.close();
    }
}

// Generates two files with almost identical content except for one character
void create_similar_files(const std::string& filename1, const std::string& filename2, size_t size) {
    std::ofstream file1(filename1);
    std::ofstream file2(filename2);

    if (file1.is_open() && file2.is_open()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(32, 126);  // Printable ASCII chars

        std::string content(size, ' ');
        for (size_t i = 0; i < size; ++i) {
            content[i] = static_cast<char>(dis(gen));  // Cast integer to char
        }

        // Write identical content to both files, but change one character in the second file
        file1 << content;
        content[size / 2] = static_cast<char>(dis(gen));  // Change a middle character
        file2 << content;

        file1.close();
        file2.close();
    }
}

// Generates an empty file
void create_empty_file(const std::string& filename) {
    std::ofstream file(filename);
    file.close();
}
//////////////////////////////////////////////////////////////////////////
void performance_test(const std::string& filename, int lineCount) {
    std::ifstream inputFile(filename);
    ofstream outputFile("hashas_performance.txt");
    std::string line;

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "Failed to open input or output file!" << std::endl;
        return;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

    int processedLines = 0;
    while (getline(inputFile, line) && processedLines < lineCount) {
        apdoroja(line, outputFile);
        processedLines++;
    }

   std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Processed " << lineCount << " lines in " << elapsed.count() << " seconds." << std::endl;

    inputFile.close();
    outputFile.close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


