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
    cout << "3. testavimas" << endl;
   // cout << "4. collision resistance test" << endl;
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
        case 3:
        {
            create_single_char_file("test_single_A.txt", 'A', 1000);
            create_single_char_file("test_single_B.txt", 'B', 1000);

            create_random_char_file("test_random1.txt", 1000);
            create_random_char_file("test_random2.txt", 1000);

            create_similar_files("test_similar1.txt", "test_similar2.txt", 1000);

            create_empty_file("test_empty.txt");

            std::cout << "Test files generated!" << std::endl;

            int lineCounts[] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
            int size = sizeof(lineCounts) / sizeof(lineCounts[0]);

            for (int i = 0; i < size; ++i) {
            int count = lineCounts[i];
            performance_test("konstitucija.txt", count);
            }
    return 0;

        
    }
        default:
            cout << "netinkamas pasirinkimas! prasome ivesti skaiciu" << endl;
            break;
    }

    outputFile.close();
    cout << "hashas issaugotas faile ,,hashas.txt'' " << endl;

    return 0;

}
