// 1 uzd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::string;

struct studentai {
    std::string Vard, Pav;
    int paz[10] = { 0 };
    int egz;
    float GP = 0;
};

void count_median(int pazymiai[]) //funkcija, skaiciuojanti mediana
{
    int sk = 0;
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
        std::cout << float(((pazymiai[sk / 2 - 1]) + (pazymiai[(sk / 2)])) / 2.0);
    }
    else
    {
        std::cout << pazymiai[(sk / 2)];
    }
    std::cout << std::endl;
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
        std::cout << "Iveskite studento egzamino pazymi:\n";
        std::cin >> S[i].egz;
    } while (S[i].egz < 0 || S[i].egz > 10);
    std::cout << "Iveskite studento pazymius (kai baigsite, iveskite -1 (minus vienas)):";
    int sk = 0;
    do {
        std::cin >> S[i].paz[sk];
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
bool has_digit(std::string s)
{
    return (s.find_first_of("0123456789") != std::string::npos);
}

void name_input(studentai S[], int i) //duoda suvest vardus ir pavardes
{
    std::cout << "Iveskite studento nr. " << i + 1 << " duomenis\n";
    do {
        std::cout << "Iveskite studento nr. " << i + 1 << " VARDA:\n";
        std::cin >> S[i].Vard;
    } while (S[i].Vard.length() < 0 || S[i].Vard.length() > 25 || has_digit(S[i].Vard));
    do {
        std::cout << "Iveskite studento nr. " << i + 1 << " PAVARDE:\n";
        std::cin >> S[i].Pav;
    } while (S[i].Pav.length() < 0 && S[i].Pav.length() > 25 || has_digit(S[i].Pav));
    std::cout << std::endl;
}

void rezultatai(studentai S[], int studentu_sk, char p) //atspausdina rezultatus
{
    if (p == 'V' || p == 'v') {
        std::cout << "\n\n";
        std::cout << std::setw(20) << std::left << "Vardas"
            << std::setw(20) << std::left << "Pavarde"
            << std::left << "Galutinis(vid.)\n"
            << "---------------------------------------------------------------------------\n";
        for (int i = 0; i < studentu_sk; i++)
        {
            std::cout << std::setw(20) << std::left << S[i].Vard
                << std::setw(20) << std::left << S[i].Pav
                << std::left << S[i].GP;
        }
        std::cout << "\n\n";
    }

    else {
        std::cout << "\n\n";
        std::cout << std::setw(20) << std::left << "Vardas"
            << std::setw(20) << std::left << "Pavarde"
            << std::left << "Galutinis(med.)\n"
            << "----------------------------------------------------------------\n";
        for (int i = 0; i < studentu_sk; i++)
        {
            std::cout << std::setw(20) << std::left << S[i].Vard
                << std::setw(20) << std::left << S[i].Pav;
                count_median(S[i].paz);
        }
        std::cout << "\n\n";
    }
    
}

int main()
{
    int studentu_sk;
    char temp, p;
    do
    {
        std::cout << "Iveskite studentu kieki:\n";
        std::cin >> studentu_sk;
    } while (int(studentu_sk) < 0 || int(studentu_sk) > 255);
    studentai S[255];

    do
    { 
        std::cout << "Pasirinkite - noresite suzinoti studentu galutini pazymi, apskaiciuota pasitelkiant vidurki ar mediana.\nKad pasirintumete vidurki: SPAUSKITE \"V\"\nKad pasirinktumete mediana: SPAUSKITE \"M\"\n";
        std::cin >> p;
        if (p != 'V' && p != 'v' && p != 'M' && p != 'm') { std::cout << "Klaida! Prasome pakartoti del ivesto netinkamo simbolio\n"; }
    } while (p != 'V' && p != 'v' && p != 'M' && p != 'm');

    do
    {
        std::cout << "Jeigu norite, jog studentu pazymiai butu suvedami automatiskai - SPAUSKITE \"A\"\nJeigu norite suvesti duomenis patys - SPAUSKITE \"P\"\n";
        std::cin >> temp;
        if (temp != 'A' && temp != 'a' && temp != 'P' && temp != 'p') { std::cout << "Klaida! Prasome pakartoti del ivesto netinkamo simbolio\n"; }
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

































// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
