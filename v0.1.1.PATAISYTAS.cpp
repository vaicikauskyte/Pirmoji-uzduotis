// 1 uzd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>

using namespace std; 

struct studentai {
    string Vard, Pav;
    int paz[10] = { 0 };
    int egz;
    float GP = 0;
};

void count_median(int pazymiai[], studentai S[], int k);
int generate_random_mark();
void automated_marks_input(studentai S[], int i, int pazymiu_k);
void input_by_hand(studentai S[], int i);
void input_by_hand(studentai S[], int i);
bool has_digit(string s);
void name_input(studentai S[], int i);
void rezultatai(studentai S[], int studentu_sk, char p);

int main()
{
    int studentu_sk;
    char temp, p;
    do
    {
         cout << "Iveskite studentu kieki:\n";
         cin >> studentu_sk;
    } while (int(studentu_sk) < 0 || int(studentu_sk) > 255);
    studentai S[255];

    do
    {
         cout << "Pasirinkite - noresite suzinoti studentu galutini pazymi, apskaiciuota pasitelkiant vidurki ar mediana.\nKad pasirintumete vidurki: SPAUSKITE \"V\"\nKad pasirinktumete mediana: SPAUSKITE \"M\"\n";
         cin >> p;
        if (p != 'V' && p != 'v' && p != 'M' && p != 'm') {  cout << "Klaida! Prasome pakartoti del ivesto netinkamo simbolio\n"; }
    } while (p != 'V' && p != 'v' && p != 'M' && p != 'm');

    do
    {
         cout << "Jeigu norite, jog studentu pazymiai butu suvedami automatiskai - SPAUSKITE \"A\"\nJeigu norite suvesti duomenis patys - SPAUSKITE \"P\"\n";
         cin >> temp;
        if (temp != 'A' && temp != 'a' && temp != 'P' && temp != 'p') {  cout << "Klaida! Prasome pakartoti del ivesto netinkamo simbolio\n"; }
    } while (temp != 'A' && temp != 'a' && temp != 'P' && temp != 'p');

    for (int i = 0; i < studentu_sk; i++)
    {
        name_input(S, i);
        if (temp == 'p' || temp == 'P') { input_by_hand(S, i); }
        else { automated_marks_input(S, i, 5); }
    }

    rezultatai(S, studentu_sk, p);
    system("pause");
    return 0;
}
void rezultatai(studentai S[], int studentu_sk, char p) //atspausdina rezultatus
{
    if (p == 'V' || p == 'v') {
        cout << "\n\n";
        cout << setw(20) << left << "Vardas"
            << setw(20) << left << "Pavarde"
            << left << "Galutinis(vid.)\n"
            << "---------------------------------------------------------------------------\n";
        for (int i = 0; i < studentu_sk; i++)
        {
            cout << setw(20) << left << S[i].Vard
                << setw(20) << left << S[i].Pav
                << left << S[i].GP;
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
            cout << setw(20) << left << S[i].Vard
                << setw(20) << left << S[i].Pav;
            count_median(S[i].paz, S, i);
            cout << left << S[i].GP;
            cout << "\n\n";
        }
    }

}

void count_median(int pazymiai[], studentai S[], int k) //funkcija, skaiciuojanti mediana
{
    int sk = 0;
    float mediana = 0;
    for (int i = 0; i < 10; i++)
    {
        if (pazymiai[i] > 0)
        {
            sk++;
        }
        if (pazymiai[i] == -1)
        {
            pazymiai[i] = 0;
            break;
        }
    }
    if (sk % 2 == 0)
    {
         mediana = (((pazymiai[sk / 2 - 1]) + (pazymiai[(sk / 2)])) / 2.0);
    }
    else
    {
        mediana = pazymiai[(sk / 2)];
    }
    S[k].GP = mediana * 0.4 + 0.6 * S[k].egz;

}

int generate_random_mark() //sugeneruoja atsitiktini pazymi nuo 1 iki 10
{
    srand(time(NULL));
    return rand() % 10 + 1;
}

void automated_marks_input(studentai S[], int i, int pazymiu_k) //funckija automatiskai suveda pazymius ir egz. pazymi
{
    S[i].egz = generate_random_mark();
    for (int x = 0; x < pazymiu_k; x++)
    {
        S[i].paz[x] = generate_random_mark();
        S[i].GP += S[i].paz[x];
    }
    if (pazymiu_k != 0) {
        S[i].GP = S[i].GP / pazymiu_k;
    }
    else {
        S[i].GP = 0;
    }
    S[i].GP = S[i].GP * 0.4 + 0.6 * S[i].egz;
}


void input_by_hand(studentai S[], int i) //funkcija duoda vartotojui suvest pazymius ir egzamino pazymi
{
    do {
         cout << "Iveskite studento egzamino pazymi:\n";
         cin >> S[i].egz;
    } while (S[i].egz < 0 || S[i].egz > 10);

     cout << "Iveskite studento pazymius (kai baigsite, iveskite -1 (minus vienas)):";
    int sk = 0;
    do {
         cin >> S[i].paz[sk];
        if (S[i].paz[sk] != -1) { S[i].GP = S[i].GP + (float)S[i].paz[sk]; }
        sk++;
    } while (S[i].paz[sk - 1] != -1);
    sk--;
    if (sk != 0) {
        S[i].GP = S[i].GP / sk;
    }
    else {
        S[i].GP = 0;
    }
    S[i].GP = S[i].GP * 0.4 + 0.6 * S[i].egz;
}
bool has_digit( string s)
{
    return (s.find_first_of("0123456789") !=  string::npos);
}

void name_input(studentai S[], int i) //duoda suvest vardus ir pavardes
{
     cout << "Iveskite studento nr. " << i + 1 << " duomenis\n";
    do {
         cout << "Iveskite studento nr. " << i + 1 << " VARDA:\n";
         cin >> S[i].Vard;
    } while (S[i].Vard.length() < 0 || S[i].Vard.length() > 25 || has_digit(S[i].Vard));
    do {
         cout << "Iveskite studento nr. " << i + 1 << " PAVARDE:\n";
         cin >> S[i].Pav;
    } while (S[i].Pav.length() < 0 && S[i].Pav.length() > 25 || has_digit(S[i].Pav));
     cout <<  endl;
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
