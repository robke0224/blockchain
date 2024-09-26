#ifndef HASH_UTIL_H
#define HASH_UTIL_H

#include <string>
#include <fstream>
#include <random>

using namespace std;

string keiciaIvesti(string& input);
string ivestis_i_bitus(string& input);
char hexas(char hexChar);
string sesiolika_bitu(string& bits, const string& originalInput);
int suma(const string& input);
string dauginti_bitus_is_sumos(string bits, int wordSum);
void apdoroja(const string& input, ofstream& outputFile);
void failiukas(const std::string& filename, char c, size_t size);
void kratinukas(const std::string& filename, size_t size);
void nevienodi(const std::string& filename1, const std::string& filename2, size_t size);
void tuscias(const std::string& filename);
void testukas1(const std::string& filename, int lineCount);
string poros_random(int length);
void kolizijos(const vector<pair<string, string> >& stringPairs);
vector<pair<string, string> > loadStringPairsFromFile(const string& filename);

#endif
