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
void read(vector<studentai>& S_vect, int* pazymiu_skaicius, studentai S[], string* temp)
{
    int studentu_sk = 0;
    do
    {
        cout << "Jeigu norite, jog studentu pazymiai butu suvedami is failo - SPAUSKITE \"F\"\nJeigu norite suvesti duomenis patys - SPAUSKITE \"P\"\n";
        cin >> *temp;
        if (*temp != "F" && *temp != "f" && *temp != "P" && *temp != "p") { cout << "Klaida! Prasome pakartoti del ivesto netinkamo simbolio\n"; }
    } while (*temp != "F" && *temp != "f" && *temp != "P" && *temp != "p");

    if (*temp == "P" || *temp == "p")
    {
        do
        {
            cout << "Iveskite studentu kieki:\n";
            cin >> studentu_sk;
        } while (int(studentu_sk) < 0 || int(studentu_sk) > 256);

        string automatik;
        do
        {
            cout << "Jeigu norite, jog studentu pazymiai butu suvedami automatiskai - SPAUSKITE \"A\"\nJeigu norite suvesti duomenis mechaniskai - SPAUSKITE \"M\"\n";
            cin >> automatik;
            if (automatik != "A" && automatik != "a" && automatik != "M" && automatik != "m") { cout << "Klaida! Prasome pakartoti del ivesto netinkamo simbolio\n"; }
        } while (automatik != "A" && automatik != "A" && automatik != "M" && automatik != "m");

        if (automatik == "M" || automatik == "m")
        {
            for (int i = 0; i < studentu_sk; i++)
            {
                name_input(S, i);
                input_by_hand(S, i);
            }
        }
        else
        {
            for (int i = 0; i < studentu_sk; i++)
            {
                name_input(S, i);
                automated_marks_input(S, i, 5);
            }
        }
    }
    else if (*temp == "F" || *temp == "f")
    {
        int laik;
        ifstream in;
        string buff;
        in.open("studentai10000.txt");
        if (in.is_open()) {
            getline(in >> ws, buff);
            *pazymiu_skaicius = countWordsInString(buff) - 3;
            while (true) {
                S_vect.resize(S_vect.size() + 1);
                in >> S_vect.at(studentu_sk).Vard;
                if (in.eof()) {
                    S_vect.pop_back();
                    break;
                }
                in >> S_vect.at(studentu_sk).Pav;
                for (int i = 0; i < *pazymiu_skaicius; i++) {
                    in >> laik;
                    S_vect.at(studentu_sk).paz.push_back(laik);
                }
                in >> S_vect.at(studentu_sk).egz;
                S_vect.at(studentu_sk).GP = S_vect.at(studentu_sk).GP * 0.4 + 0.6 * S_vect.at(studentu_sk).egz;
                studentu_sk++;
            }
        }
        else {
            cout << "-\n";
        }
    }
}
