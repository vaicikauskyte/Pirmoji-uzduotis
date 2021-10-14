#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct studentai {
    string Vard, Pav;
    vector<int> paz;
    int egz;
    float GP = 0;
};

void rezultatai(studentai S[], int studentu_sk, char p);
void count_median(vector<int> pazymiai, studentai S[], int i);
int generate_random_mark();
void automated_marks_input(studentai S[], int i, int pazymiu_k);
void input_by_hand(studentai S[], int i);
bool has_digit(string s);
void name_input(studentai S[], int i);

int main()
{
    int studentu_sk;
    string temp;
    char p;
    do
    {
        cout << "Iveskite studentu kieki:\n";
        cin >> studentu_sk;
    } while (int(studentu_sk) < 0 || int(studentu_sk) > 256);
    studentai S[255];
    vector<studentai> S_vect;

    do
    {
        cout << "Pasirinkite - noresite suzinoti studentu galutini pazymi, apskaiciuota pasitelkiant vidurki ar mediana.\nKad pasirintumete vidurki: SPAUSKITE \"V\"\nKad pasirinktumete mediana: SPAUSKITE \"M\"\n";
        cin >> p;
        if (p != 'V' && p != 'v' && p != 'M' && p != 'm') { cout << "Klaida! Prasome pakartoti del ivesto netinkamo simbolio\n"; }
    } while (p != 'V' && p != 'v' && p != 'M' && p != 'm');

    do
    {
        cout << "Jeigu norite, jog studentu pazymiai butu suvedami automatiskai - SPAUSKITE \"A\"\nJeigu norite suvesti duomenis patys - SPAUSKITE \"P\"\n";
        cin >> temp;
        if (temp != "A" && temp != "a" && temp != "P" && temp != "p") { cout << "Klaida! Prasome pakartoti del ivesto netinkamo simbolio\n"; }
    } while (temp != "A" && temp != "a" && temp != "P" && temp != "p");

    for (int i = 0; i < studentu_sk; i++)
    {
        name_input(S, i);
        if (temp == "P" || temp == "p") { input_by_hand(S, i); }
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
        cout << "\n\n";
    }

}

void count_median(vector<int> pazymiai, studentai S[], int i) //funkcija, skaiciuojanti mediana
{
     int sk = 0;
     double mediana = 0;
     for (int i = 0; i < pazymiai.size(); i++)
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
     S[i].GP = mediana * 0.4 + 0.6 * S[i].egz;
}

int generate_random_mark() //sugeneruoja atsitiktini pazymi nuo 1 iki 10
{
    srand(time(NULL));
    return rand() % 10 + 1;
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

bool has_digit(string s)
{
    return (s.find_first_of("0123456789") !=  string::npos);
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
     cout <<  endl;
}




