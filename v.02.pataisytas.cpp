// uzduotis-0.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

struct duomenys {
    string Vard, Pav;
    vector<int> paz = { 0 };
    int egz;
    float GP = 0;

    bool operator < (const duomenys& duom) const
    {
        if (Vard == duom.Vard) {
            return (Pav < duom.Pav);
        }
        return (Vard < duom.Vard);
    }
};

int generate_random_mark();
void automated_marks_input(vector<duomenys>& S, int i, int pazymiu_k);
void rezultatai(vector<duomenys> S, int studentu_sk, char p);
void input_by_hand(vector<duomenys>& S, int i);
bool has_digit(string s);
void name_input(vector<duomenys>& S, int i);
void read_from_file(vector<duomenys>& S, int* pazymiu_sk);
unsigned int countWordsInString(string const& str);
float count_median(vector<int> pazymiai, int egzas);
void print_student(vector<duomenys> S, int pazymiu_sk);

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
        vector<duomenys> S;
        vector<duomenys> S_vect;

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
        std::vector<duomenys> S;
        read_from_file(S, &pazymiu_sk);
        print_student(S, pazymiu_sk);
        cout << "Rezultatai issaugoti faile rezultatai.txt" << endl;
    }

}

void rezultatai(vector<duomenys> S, int studentu_sk, char p) //atspausdina rezultatus
{
    if (p == 'V' || p == 'v') {
        cout << "\n\n";
        cout << setw(20) << left << "Vardas"
            << setw(20) << left << "Pavarde"
            << left << "Galutinis(vid.)\n"
            << "---------------------------------------------------------------------------\n";
        for (int i = 0; i < studentu_sk; i++)
        {
            cout << fixed << showpoint;
            cout << setprecision(2);
            cout << setw(20) << left << S[i].Vard
                << setw(20) << left << S[i].Pav
                << left << S[i].GP << endl;
        }
        cout << "\n\n";
    }

    else {
        cout << "\n\n";
        cout << setw(20) << left << "Vardas"
            << setw(20) << left << "Pavarde"
            << left << "Galutinis(med.)\n"
            << "----------------------------------------------------------------\n";
        for (int i = 0; i < studentu_sk; i++)
        {
            cout << fixed << showpoint;
            cout << setprecision(2);
            cout << setw(20) << left << S[i].Vard
                << setw(20) << left << S[i].Pav
                << left << count_median(S[i].paz, S[i].egz) << endl;
        }
        cout << "\n\n";
    }

}

int generate_random_mark() //sugeneruoja atsitiktini pazymi nuo 1 iki 10
{
    return rand() % 10 + 1;
}

void automated_marks_input(vector<duomenys>& S, int i, int pazymiu_k) //funckija, kuri automatiskai suveda pazymius, egzamino rezultata
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

void input_by_hand(vector<duomenys>& S, int i) //funkcija duoda vartotojui suvest pazymius ir egzamino pazymi
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

bool has_digit(string s)
{
    return (s.find_first_of("0123456789") != string::npos);
}
void name_input(vector<duomenys>& S, int i) //duoda suvest vardus ir pavardes
{
    cout << "Iveskite studento nr. " << i + 1 << " duomenis:\n";
    duomenys stud;
    do {
        cout << "Iveskite studento nr. " << i + 1 << " VARDA:\n";
        cin >> stud.Vard;
    } while (stud.Vard.length() < 0 || stud.Vard.length() > 25 || has_digit(stud.Vard));
    do {
        cout << "Iveskite studento nr. " << i + 1 << " PAV:\n";
        cin >> stud.Pav;
    } while (stud.Pav.length() < 0 && stud.Pav.length() > 25 || has_digit(stud.Pav));
    cout << endl;
    S.push_back(stud);
}

float count_median(vector<int> pazymiai, int egzas) //funkcija suskaiciuoja mediana
{
    pazymiai.push_back(egzas);
    int size = pazymiai.size() - 1;

    if (size == 0)
    {
        return 0;
    }
    else
    {
        sort(pazymiai.begin(), pazymiai.end());
        if (size % 2 == 0)
        {
            return (pazymiai[size / 2] + pazymiai[size / 2 + 1]) / 2.0;
        }
        else
        {
            return pazymiai[size / 2 + 1];
        }
    }
}

void print_student(vector<duomenys> S, int pazymiu_sk) //atspausdina rezultatus
{
    ofstream output;
    output.open("rezultatai.txt");
    output << setw(20) << left << "Vardas"
        << setw(20) << left << "Pavarde"
        << setw(18) << left << "Galutinis (Vid.)/"
        << left << "Galutinis (Med.)\n"
        << "--------------------------------------------------------------------------\n";
    int n = S.size();
    sort(S.begin(), S.end());
    for (int i = 0; i < n; i++)
    {
        output << fixed << showpoint;
        output << setprecision(2);
        output << setw(20) << left << S[i].Vard
            << setw(20) << left << S[i].Pav
            << setw(18) << left << S[i].GP
            << count_median(S[i].paz, S[i].egz) << endl;
    }
    output << "\n\n";
}


void read_from_file(vector<duomenys>& S, int* pazymiu_sk)
{
    int student_sk = 0;
    int temp;
    ifstream fileRead("kursiokai.txt");
    string buff;
    if (fileRead.is_open())
    {
        while (getline(fileRead, buff)) {
            *pazymiu_sk = countWordsInString(buff) - 3;
            while (true)
            {
                S.resize(S.size() + 1);
                fileRead >> S.at(student_sk).Vard;
                if (fileRead.eof()) { S.pop_back(); break; }
                fileRead >> S.at(student_sk).Pav;
                for (int i = 0; i < *pazymiu_sk; i++)
                {
                    fileRead >> temp;
                    S.at(student_sk).paz.push_back(temp);
                }
                fileRead >> S.at(student_sk).egz;
                S.at(student_sk).GP = S.at(student_sk).GP / *pazymiu_sk;
                S.at(student_sk).GP = S.at(student_sk).GP * 0.4 + 0.6 * S.at(student_sk).egz;
                student_sk++;
            }
        }
        fileRead.close();
    }
    cout << "-\n";
}

unsigned int countWordsInString(string const& str)
{
    stringstream stream(str);
    return distance(istream_iterator<string>(stream), istream_iterator<string>());
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
