#include <iostream>
#include <fstream>
#include <string>
#include "hash.h"

using namespace std;

int main() {
    int choice;
    do {
        cout << "ivesties metodas: " << endl;
        cout << "1. ivesti ranka" << endl;
        cout << "2. nuskaityti is failo" << endl;
        cout << "3. testavimo failu generavimas" << endl;
        cout << "4. eiluciu hashavimo laiko testavimas" << endl;
        cout << "5. baigti programa" << endl;  
        
        cin >> choice;

        ofstream outputFile;

        if (choice == 1 || choice == 2) {
            outputFile.open("hashas.txt");
        } else if (choice == 4) {
            outputFile.open("hash_performance.txt");
        }

        if (!outputFile.is_open() && (choice == 1 || choice == 2 || choice == 4)) {
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
                ifstream inputFile("testas_su_A.txt");  // Replace with the file you need to read and hash

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
            case 3: {
                failiukas("testas_su_A.txt", 'A', 1500);
                failiukas("testas_su_B.txt", 'B', 1500);

                kratinukas("testas_random1.txt", 1500);
                kratinukas("testas_random2.txt", 1500);

                nevienodi("panasus1.txt", "panasus2.txt", 1500);

                tuscias("tuscias.txt");

                cout << "Testiniai failai sugeneruoti sekmingai!" << endl;

                break;
            }
            case 4: {
                int lineCounts[] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
                int size = sizeof(lineCounts) / sizeof(lineCounts[0]);

                for (int i = 0; i < size; ++i) {
                    int count = lineCounts[i];
                    testukas1("konstitucija.txt", count);  
                }

                break;
            }
            case 5:
                cout << "Programa baigta." << endl;
                break;

            default:
                cout << "netinkamas pasirinkimas! prasome ivesti skaiciu" << endl;
                break;
        }

        if (outputFile.is_open()) {
            outputFile.close();
        }

        
        if (choice == 1 || choice == 2) {
            cout << "ivesties hashas issaugotas faile hashas.txt" << endl;
        } else if (choice == 4) {
            cout << "ivesties hashas issaugotas faile hash_performance.txt" << endl;
        }

    } while (choice != 5);  

    return 0;
}
