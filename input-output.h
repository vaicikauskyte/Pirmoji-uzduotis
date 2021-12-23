#pragma once
#include "entities.h"
#include<vector>
using namespace std;

void read_from_file(vector<studentas>& S, int* pazymiu_sk);
void print_student(vector<studentas> S, int pazymiu_sk);
unsigned int countWordsInString(string const& str);
void rezultatai(vector<studentas> S, int studentu_sk, char p);
int generate_random_mark();
void automated_marks_input(vector<studentas>& S, int i, int pazymiu_k);
void input_by_hand(vector<studentas>& S, int i);
bool has_digit(string s);
void name_input(vector<studentas>& S, int i);