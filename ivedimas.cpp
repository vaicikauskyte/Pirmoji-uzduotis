#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <iterator>
#include <fstream>
#include "ivedimas.h"
#include "spausdinimas.h"
#include "skaitymas.h"
#include "studentai.h"
#include "skaciavimas.h"
void input_by_hand(studentai S[], int i) //funkcija duoda vartotojui suvest pazymius ir egzamino pazymi
{
    int temp;
    do {
        cout << "Iveskite studento egzamino pazymi:\n";
        cin >> S[i].egz;
    } while (S[i].egz < 0 || S[i].egz > 10);
    cout << "Iveskite studento pazymius (kai baigsite, iveskite -1 (minus vienas)):";
    int sk = 0;
    do {
        cin >> temp;
        S[i].paz.push_back(temp);
        if (S[i].paz.at(sk) != -1) { S[i].GP = S[i].GP + (float)S[i].paz.at(sk); }
        sk++;
    } while (S[i].paz.back() != -1);
    sk--;
    if (sk != 0) {
        S[i].GP = S[i].GP / sk;
    }
    else {
        S[i].GP = 0;
    }
    S[i].GP = S[i].GP * 0.4 + 0.6 * S[i].egz;
}
void name_input(studentai S[], int i) //duoda suvest vardus ir pavardes
{
    cout << "Iveskite studento nr. " << i + 1 << " duomenis:\n";
    do {
        cout << "Iveskite studento nr. " << i + 1 << " VARDA:\n";
        cin >> S[i].Vard;
    } while (S[i].Vard.length() < 0 || S[i].Vard.length() > 25 || has_digit(S[i].Vard));
    do {
        cout << "Iveskite studento nr. " << i + 1 << " PAV:\n";
        cin >> S[i].Pav;
    } while (S[i].Pav.length() < 0 && S[i].Pav.length() > 25 || has_digit(S[i].Pav));
    cout << endl;
}
void automated_marks_input(studentai S[], int i, int pazymiu_k) //funckija, kuri automatiskai suveda pazymius, egzamino rezultata
{
    S[i].egz = generate_random_mark();
    for (int x = 0; x < pazymiu_k; x++)
    {
        S[i].paz.push_back(generate_random_mark());
    }
    if (pazymiu_k != 0) {
        S[i].GP = S[i].GP / pazymiu_k;
    }
    else {
        S[i].GP = 0;
    }
    S[i].GP = S[i].GP * 0.4 + 0.6 * S[i].egz;
}
bool has_digit(string s)
{
    return (s.find_first_of("0123456789") != string::npos);
}