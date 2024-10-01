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
        cout << "7. procentinio skirtingumo skaiciavimas" << endl;  
        cout << "8. baigti programa" << endl; 
        
        cin >> choice;

        ofstream outputFile;

        if (choice == 1 || choice == 2) {
            outputFile.open("hashas.txt");
        } else if (choice == 4) {
            outputFile.open("eilutes4.txt");
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
                ifstream inputFile("konstitucija.txt");  // Replace with the file you need to read and hash

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

    case 7:{
         const int num_pairs = 100000;  
         const int max_length = 500;   

    vector<double> bit_differences, hex_differences;

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> length_dist(1, max_length);

    
    ofstream pair_file("7testas.txt");
    if (!pair_file.is_open()) {
        cerr << "nepavyko atidaryti failo!" << endl;
        return -1;
    }

    
    ofstream hash_file("palyginimo_rezultatai.txt");
    if (!hash_file.is_open()) {
        cerr << "nepavyko atidaryti failo!" << endl;
        return -1;
    }

    for (int i = 0; i < num_pairs; ++i) {
       
        int length = length_dist(generator);
        string str1 = generate_random_string(length);

        
        string str2 = str1;
        uniform_int_distribution<> char_pos_dist(0, length - 1);
        int pos = char_pos_dist(generator);

        // cia kad tik vienu simboliu skirtusi
        char original_char = str2[pos];
        char new_char;
        do {
            new_char = generate_random_string(1)[0];
        } while (new_char == original_char);
        str2[pos] = new_char;

        //irasyti i faila
        pair_file << str1 << " " << str2 << endl;

        // hashina
        
        string modified_str1 = keiciaIvesti(str1, 'k', 2, true, false);
        string modified_str2 = keiciaIvesti(str2, 'k', 2, true, false);


        string binary_hash1 = ivestis_i_bitus(modified_str1);
        string binary_hash2 = ivestis_i_bitus(modified_str2);

        string hex_hash1 = sesiolika_bitu(binary_hash1, modified_str1);
        string hex_hash2 = sesiolika_bitu(binary_hash2, modified_str2);

        // skirtumai
        double bit_diff = compute_bit_difference(binary_hash1, binary_hash2);
        double hex_diff = compute_hex_difference(hex_hash1, hex_hash2);

        bit_differences.push_back(bit_diff);
        hex_differences.push_back(hex_diff);

        // iraso i faila skirtumus
        hash_file << "String pora: " << str1 << " " << str2 << endl;
        hash_file << "pirmo hashas hex: " << hex_hash1 << endl;
        hash_file << "antro hashas hex: " << hex_hash2 << endl;
        hash_file << "bitu skirtumas: " << bit_diff << "%" << endl;
        hash_file << "hexo skirtumas: " << hex_diff << "%" << endl;
        hash_file << "-------------------------------------------" << endl;
    }

 
    pair_file.close();
    hash_file.close();

    // skaiciavimai
    double bit_min = *min_element(bit_differences.begin(), bit_differences.end());
    double bit_max = *max_element(bit_differences.begin(), bit_differences.end());
    double bit_avg = accumulate(bit_differences.begin(), bit_differences.end(), 0.0) / bit_differences.size();

    double hex_min = *min_element(hex_differences.begin(), hex_differences.end());
    double hex_max = *max_element(hex_differences.begin(), hex_differences.end());
    double hex_avg = accumulate(hex_differences.begin(), hex_differences.end(), 0.0) / hex_differences.size();

    // isvestis terminale
    cout << "bitu skirtumas: " << endl;
    cout << "min: " << bit_min << "%" << endl;
    cout << "max: " << bit_max << "%" << endl;
    cout << "vidutinis: " << bit_avg << "%" << endl;

    cout << "hexu sirtumas: " << endl;
    cout << "min: " << hex_min << "%" << endl;
    cout << "max: " << hex_max << "%" << endl;
    cout << "vidutinis: " << hex_avg << "%" << endl;

    break;

    }


            case 8:
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

    } while (choice != 8);  

    return 0;
}
