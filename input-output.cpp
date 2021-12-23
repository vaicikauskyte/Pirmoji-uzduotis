#include "input-output.h"
#include "logic.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
using namespace std;

void read_from_file(std::vector<studentas>& S, int* pazymiu_sk)
{
	int student_sk = 0;
	int temp;
	try {
		std::ifstream fileRead("kursiokai.txt");
		std::string buff;
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
	}
	catch (std::exception& e) {
		std::cout << "Negalima nuskaityti failo" << std::endl;
	}
	
	
}

void print_student(std::vector<studentas> S, int pazymiu_sk) //atspausdina rezultatus
{
	std::ofstream output;
	output.open("rezultatai.txt");
	output << std::setw(20) << std::left << "Vardas"
		<< std::setw(20) << std::left << "Pavarde"
		<< std::setw(18) << std::left << "Galutinis (Vid.)/"
		<< std::left << "Galutinis (Med.)\n"
		<< "--------------------------------------------------------------------------\n";
	int n = S.size();
	sort(S.begin(), S.end());
	for (int i = 0; i < n; i++)
	{
		output << std::fixed << std::showpoint;
		output << std::setprecision(2);
		output << std::setw(20) << std::left << S[i].Vard
			<< std::setw(20) << std::left << S[i].Pav
			<< std::setw(18) << std::left << S[i].GP
			<< count_median(S[i].paz, S[i].egz) << std::endl;
	}
	output << "\n\n";
}

unsigned int countWordsInString(std::string const& str)
{
	std::stringstream stream(str);
	return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}

void rezultatai(vector<studentas> S, int studentu_sk, char p) //atspausdina rezultatus
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

void automated_marks_input(vector<studentas>& S, int i, int pazymiu_k) //funckija, kuri automatiskai suveda pazymius, egzamino rezultata
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

void input_by_hand(vector<studentas>& S, int i) //funkcija duoda vartotojui suvest pazymius ir egzamino pazymi
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
void name_input(vector<studentas>& S, int i) //duoda suvest vardus ir pavardes
{
	cout << "Iveskite studento nr. " << i + 1 << " duomenis:\n";
	studentas stud;
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