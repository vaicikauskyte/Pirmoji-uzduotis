// uzduotis-0.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "input-output.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
    char x;
    do
    {
        cout << "Jeigu norite duomenis nuskaityti is failo SPAUSKITE \"F\",\n jei norite duomenis ivesti patys SPAUSKITE \"P\" \n";
        cin >> x;
        if (x != 'F' && x != 'f' && x != 'P' && x != 'p') { cout << "Klaida! Prasome pakartoti del ivesto netinkamo simbolio\n"; }
    } while (x != 'F' && x != 'f' && x != 'P' && x != 'p');

    if (x == 'P' || x == 'p') {
        int studentu_sk;

        do
        {
            cout << "Iveskite studentu kieki:\n";
            cin >> studentu_sk;
        } while (int(studentu_sk) < 0 || int(studentu_sk) > 256);
        vector<studentas> S;

        char p;
        do
        {
            cout << "Pasirinkite - noresite suzinoti studentu galutini pazymi, apskaiciuota pasitelkiant vidurki ar mediana.\nKad pasirintumete vidurki: SPAUSKITE \"V\"\nKad pasirinktumete mediana: SPAUSKITE \"M\"\n";
            cin >> p;
            if (p != 'V' && p != 'v' && p != 'M' && p != 'm') { cout << "Klaida! Prasome pakartoti del ivesto netinkamo simbolio\n"; }
        } while (p != 'V' && p != 'v' && p != 'M' && p != 'm');

        char temp;
        do
        {
            cout << "Jeigu norite, jog studentu pazymiai butu suvedami automatiskai - SPAUSKITE \"A\"\nJeigu norite suvesti duomenis patys - SPAUSKITE \"P\"\n";
            cin >> temp;
            if (temp != 'A' && temp != 'a' && temp != 'P' && temp != 'p') { cout << "Klaida!Prasome pakartoti del ivesto netinkamo simbolio\n"; }
        } while (temp != 'A' && temp != 'a' && temp != 'P' && temp != 'p');

        for (int i = 0; i < studentu_sk; i++)
        {
            name_input(S, i);
            if (temp == 'P' || temp == 'p') { input_by_hand(S, i); }
            else { automated_marks_input(S, i, 5); }
        }
        rezultatai(S, studentu_sk, p);
        system("pause");
        return 0;
    }
    else {
        int pazymiu_sk;
        vector<studentas> S;
        read_from_file(S, &pazymiu_sk);
        print_student(S, pazymiu_sk);
        cout << "Rezultatai issaugoti faile rezultatai.txt" << endl;
    }
}

