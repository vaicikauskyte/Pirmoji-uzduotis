#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <iterator>
#include <fstream>
#include "spausdinimas.h"
#include "skaitymas.h"
#include "ivedimas.h"
#include "studentai.h"
#include "skaciavimas.h"
void print_student(vector<studentai> S_vect, int pazymiu_skaicius, studentai S[], string temp)
{
    ofstream out;
    out.open("rezultatai.txt");
    if (temp == "P" || temp == "p")
    {
        out << setw(25) << left << "Studento vardas" << setw(25) << left << "Pavarde" << setw(20) << left << "Galutinis(vidurkis)/ Galutinis(mediana)" << "\n"
            << "-------------------------------------------------------------------------------------------------------------------\n";
        for (int i = 0; i < S[i].paz.size(); i++)
        {
            out << setw(25) << left << S[i].Vard
                << setw(25) << left << S[i].Pav
                << setw(20) << left << S[i].GP
                << count_median(S[i].paz);
        }
        out << "\n\n\n";
    }
    else if (temp == "F" || temp == "f")
    {
        out << setw(25) << left << "Studento vardas" << setw(25) << left << "Pavarde" << setw(20) << left << "Galutinis(vidurkis)/ Galutinis(mediana)"
            << "--------------------------\n";
        for (int i = 0; i < S_vect.size(); i++) {
            out << setw(25) << left << S_vect[i].Vard << setw(25) << left << S_vect[i].Pav << setw(20) << left << S_vect[i].GP
                << count_median(S_vect[i].paz) << endl;
        }
        out << "\n\n\n";
    }
}