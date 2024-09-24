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
void create_single_char_file(const std::string& filename, char c, size_t size);
void create_random_char_file(const std::string& filename, size_t size);
void create_similar_files(const std::string& filename1, const std::string& filename2, size_t size);
void create_empty_file(const std::string& filename);
void performance_test(const std::string& filename, int lineCount);

#endif
