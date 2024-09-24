#include <iostream>
#include <fstream>
#include <string>
#include "hash.h"

using namespace std;

int main() {
    int choice;
    cout << "ivesties metodas: " << endl;
    cout << "1. ivesti ranka" << endl;
    cout << "2. nuskaityti is failo" << endl;
    cin >> choice;

    ofstream outputFile("hashas.txt");

    if (!outputFile.is_open()) {
        cout << "nepavyko atidaryti failo:(" << endl;
        return 1;
    }

    switch (choice) {
        case 1: {
            string input;
            cout << "iveskite: ";
            cin.ignore();
            getline(cin, input);

            apdoroja(input, outputFile);
            break;
        }
        case 2: {
            ifstream inputFile("konstitucija.txt");

            if (!inputFile.is_open()) {
                cout << "nepavyko atidaryti failo:(" << endl;
                return 1;
            }

            string line;
            while (getline(inputFile, line)) {
                apdoroja(line, outputFile);
            }

            inputFile.close();
            break;
        }
        default:
            cout << "netinkamas pasirinkimas! prasome ivesti skaiciu" << endl;
            break;
    }

    outputFile.close();
    cout << "hashas issaugotas faile ,,hashas.txt'' " << endl;

    return 0;
}
