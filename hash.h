#ifndef HASH_UTIL_H
#define HASH_UTIL_H

#include <string>
#include <fstream>

using namespace std;

string keiciaIvesti(string& input);
string ivestis_i_bitus(string& input);
char hexas(char hexChar);
string sesiolika_bitu(string& bits, const string& originalInput);
int suma(const string& input);
string dauginti_bitus_is_sumos(string bits, int wordSum);
void apdoroja(const string& input, ofstream& outputFile);

#endif
