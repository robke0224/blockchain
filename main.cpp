#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;


string keiciaIvesti(string& input) {
   for (size_t i = 0; i < input.size(); ++i) {
    if (isalpha(input[i])) {  // tikrina ar raide
        if (isupper(input[i]) || input[i] == '?') {  
            input[i] ^= (i % 8);  // XOR mod 8
            input[i] += 3;        // ascii reiksme pakelia per 3 
        } else {                    
            input[i] ^= (i + 5);  // XOR su + 5
            input[i] -= 4;        // ascii pamazina per 4
        }
    } else {
        input[i] ^= (i % 6);      // XOR mod 6 ne abeceles raidem
        input[i] += 1;            // ascii per viena pakelia
    }
}

    // stringa perverciam
    reverse(input.begin(), input.end());

    return input;
}

// ivesti i bitu grandine 256
string ivestis_i_bitus(string& input) {
    string bits;

    while (input.length() < 32) {
        input += 'k'; // druskos jeigu inputas trumpas
    }

    // vercia kiekviena raide i 8 bitus
    for (size_t i = 0; i < input.length(); ++i) {
    char c = input[i];
    bits += bitset<8>(static_cast<unsigned char>(c)).to_string();
}
    return bits;
}

// hex didinimo funkcija
char hexas(char hexChar) {
    if (isdigit(hexChar)) {  // tikrina ar skaicius
        return (hexChar == '9') ? '0' : hexChar + 1;  // didina vienu, po 9 i 0 grizta
    } else if (hexChar >= 'A' && hexChar <= 'F') {  // didziosios raid
        return (hexChar == 'F') ? 'A' : hexChar + 1;
    } else if (hexChar >= 'a' && hexChar <= 'f') {  // mazosios raid
        return (hexChar == 'f') ? 'a' : hexChar + 1;
    }
    return hexChar;  // nehexa grazina nekeista
}

// bitus i sesioliktaini hasha
string sesiolika_bitu(string& bits, const string& originalInput) {
    
    while (bits.size() % 4 != 0) {
        bits = '0' + bits;
    }

    stringstream hexStream;
    bool containsUpper = any_of(originalInput.begin(), originalInput.end(), ::isupper);
    bool containsExclamation = originalInput.find('!') != string::npos;

    // Determine multiplier base
    int multiplierBase = 1;
    if (containsUpper) {
        multiplierBase = originalInput.length(); //Random logic to radically change the output for UpperCase
    } else if (containsExclamation) {
        multiplierBase = originalInput.length() / 2; //Random logic to radically change the output for !
    }

    int rollingValue = 1;

    // Convert 4-bit chunks to hexadecimal
    for (size_t i = 0; i < bits.size(); i += 4) {
        string chunk = bits.substr(i, 4);
        int value = stoi(chunk, nullptr, 2);

        // Apply transformations
        int charInfluence = originalInput[i / 4] % 16; // i/4 selects every character, % 16 is ensuring that the influence is constrained between 0 and 15
        rollingValue += (charInfluence + 1);

        // Make the value less predictable and more complex
        value *= rollingValue;
        value *= multiplierBase + (i / 4); //ensuring that longer inputs and higher indices lead to greater modifications
        value *= abs(sin(originalInput.length() + i / 4)) * 100; //Adding non-linearity to the transformation

        hexStream << hex << value;
    }

    string hexResult = hexStream.str();

    // Modify each hexadecimal character
    for (size_t i = 0; i < hexResult.length(); ++i) {
    hexResult[i] = hexas(hexResult[i]);
}

    // Ensure the result is exactly 64 characters
    if (hexResult.length() > 64) {
        hexResult = hexResult.substr(0, 64);
    } else {
        while (hexResult.length() < 64) {
            hexResult += '0';
        }
    }

    return hexResult;
}

// Function to compute word sum
int computeWordSum(const string& input) {
    int sum = 0;

    // Calculate the sum of alphabetical positions for each character (ignoring non-alphabetical characters)
   for (size_t i = 0; i < input.length(); ++i) {
    char c = input[i];
    if (std::isalpha(c)) {
        // Convert to lowercase for consistent calculation
        sum += std::tolower(c) - 'a' + 1;
    }
}

    return sum;
}

// Function to multiply bits by word sum
string multiplyBitsByWordSum(string bits, int wordSum) {
    // Iterate over each bit and multiply its numeric value by wordSum
    for (size_t i = 0; i < bits.size(); ++i) {
        if (bits[i] == '1') {
            bits[i] = (wordSum % 2) ? '1' : '0';
        } else {
            bits[i] = (wordSum % 2) ? '0' : '1';
        }
        wordSum /= 2; // Update wordSum for the next bit, scaling down
        if (wordSum == 0) break; // If wordSum is exhausted, stop modifying the bits
    }

    return bits;
}

// Function to process input and generate the hash
void processInput(const string& input, ofstream& outputFile) {
    string modifiedInput = input + to_string(input.length()); // Salt the input by appending its length

    keiciaIvesti(modifiedInput);
    string binaryResult = ivestis_i_bitus(modifiedInput);
    int wordSum = computeWordSum(modifiedInput);
    string modifiedBits = multiplyBitsByWordSum(binaryResult, wordSum);
    string hashResult = sesiolika_bitu(modifiedBits, modifiedInput);

    // Output the hash
    outputFile << "Hash: " << hashResult << endl;
}

int main() {
    int choice;
    cout << "Select input method: " << endl;
    cout << "1. Input by hand" << endl;
    cout << "2. Input from file (konstitucija.txt)" << endl;
    cin >> choice;

    ofstream outputFile("results.txt");

    if (!outputFile.is_open()) {
        cout << "Error opening output file!" << endl;
        return 1;
    }

    if (choice == 1) {
        string input;
        cout << "Enter input: ";
        cin.ignore(); // To ignore the newline character left in the input buffer
        getline(cin, input);

        processInput(input, outputFile); // Process the input and write to file

    } else if (choice == 2) {
        ifstream inputFile("konstitucija.txt");

        if (!inputFile.is_open()) {
            cout << "Error opening input file!" << endl;
            return 1;
        }

        string line;
        while (getline(inputFile, line)) {
            processInput(line, outputFile); // Process each line and write to file
        }

        inputFile.close();
    } else {
        cout << "Invalid choice!" << endl;
    }

    outputFile.close();
    cout << "Hash results saved to results.txt" << endl;

    return 0;
}
