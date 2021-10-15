#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <iterator>
#include <fstream>
#include "studentai.h"
#include "spausdinimas.h"
#include "skaitymas.h"

using namespace std;

int main() {
    int pazymiu_skaicius;
    studentai S[256];
    string temp;
    vector<studentai> S_vect;
    read(S_vect, &pazymiu_skaicius, S, &temp);
    print_student(S_vect, pazymiu_skaicius, S, temp);
    system("pause");
    return 0;
}