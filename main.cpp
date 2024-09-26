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
        cout << "5. generuoti simboliu eiluciu poras"<< endl;
        cout << "6. collision resistance test"<< endl;
        cout << "7. baigti programa" << endl;  
        
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

            case 5:{

                srand(time(0)); 

                const int poruIsVis = 100000;
                const int grupesDydis = 25000;

            vector<pair<string, string> > stringPoros;

           
            ofstream outputFile("poros.txt");
             if (!outputFile) {
                    cerr << "klaida. nepavyko atidaryti failo." << endl;
                 return 1;
                }

            // 10 ilgio
                for (int i = 0; i < grupesDydis; i++) {
                string str1 = poros_random(10);
                string str2 = poros_random(10);
                stringPoros.push_back(make_pair(str1, str2));
                 }

            // 100 ilgio
                for (int i = 0; i < grupesDydis; i++) {
                string str1 = poros_random(100);
                string str2 = poros_random(100);
                stringPoros.push_back(make_pair(str1, str2));
                }

             //500 ilgio
                for (int i = 0; i < grupesDydis; i++) {
                string str1 = poros_random(500);
                string str2 = poros_random(500);
                stringPoros.push_back(make_pair(str1, str2));
                 }

            // 1000 ilgio
                 for (int i = 0; i < grupesDydis; i++) {
                string str1 = poros_random(1000);
                string str2 = poros_random(1000);
                stringPoros.push_back(make_pair(str1, str2));
                 }

            // irasom i faila
                for (int i = 0; i < stringPoros.size(); i++) {
                    outputFile << stringPoros[i].first << ", " << stringPoros[i].second  << endl;
                 }

            
                outputFile.close();

                cout << "sekmingai irasyta faile poros.txt" << endl;

    break;
}

case 6:{
 
   
    string filename = "poros.txt";
    vector<pair<string, string> > stringPairs = loadStringPairsFromFile(filename);

    
    if (stringPairs.empty()) {
        cerr << "Nepavyko nuskaityti failo." << endl;
        return 1;
    }

    
    ofstream outputFile("kolizijuHashai.txt");
    if (!outputFile.is_open()) {
        cerr << "Nepavyko atidaryti failo isvesties saugojimui." << endl;
        return 1;
    }

    for (size_t i = 0; i < stringPairs.size(); ++i) {
        const pair<string, string>& pair = stringPairs[i];
        apdoroja(pair.first, outputFile);  
        apdoroja(pair.second, outputFile);
    }

    outputFile.close();
    

    kolizijos(stringPairs);


   break;
}

            case 7:
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

    } while (choice != 7);  

    return 0;
}
