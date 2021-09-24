// v0.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <iterator>


struct duomenys {
	std::string Vard, Pav;
	std::vector<int> paz = { 0 };
	int egz;
	float GP = 0;
};


float count_median(std::vector<int> pazymiai) //funkcija suskaiciuoja mediana
{
	int sk = 0;
	for (int i = 0; i < 10; i++)
	{
		if (pazymiai[i] != 0)
		{
			sk++;
		}
		if (pazymiai[i] == -1)
		{
			pazymiai[i] = 0;
			sk--;
			break;
		}
	}
	if (sk % 2 == 0)
	{
		return float(((pazymiai[sk / 2 - 1]) + (pazymiai[(sk / 2)])) / 2.0);
	}
	else
	{
		return float(pazymiai[(sk / 2)]);
	}
}


void print_student(std::vector<duomenys> S, int pazymiu_sk) //atspausdina rezultatus
{
	std::ofstream output;
	output.open("rezultatai.txt");
	output << std::setw(20) << std::left << "Vardas"
		<< std::setw(20) << std::left << "Pavarde"
		<< std::setw(18) << std::left << "Galutinis(vid.)/"
		<< std::left << "Galutinis(med.)\n"
		<< "--------------------------------------------------------------------------\n";
	for (int i = 0; i < S.size(); i++)
	{
		output << std::setw(20) << std::left << S[i].Vard
			<< std::setw(20) << std::left << S[i].Pav
			<< std::setw(18) << std::left << S[i].GP
			<< count_median(S[i].paz) << std::endl;
	}
	output << "\n\n";
}


unsigned int countWordsInString(std::string const& str)
{
	std::stringstream stream(str);
	return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}


void read_from_file(std::vector<duomenys>& S, int* pazymiu_sk)
{
	int student_sk = 0;
	int temp;
	std::ifstream fileRead;
	std::string buff;
	fileRead.open("studentai100000.txt.txt");
	if (fileRead.is_open())
	{
		getline(fileRead >> std::ws, buff);
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
			//std::cout << S.at(student_counter).Vard;
			S.at(student_sk).GP = S.at(student_sk).GP / *pazymiu_sk;
			S.at(student_sk).GP = S.at(student_sk).GP * 0.4 + 0.6 * S.at(student_sk).egz;
			student_sk++;
		}
	}
	else { std::cout << "-\n"; }
}


int main()
{
	int pazymiu_sk;
	char temp;
	std::vector<duomenys> S;
	read_from_file(S, &pazymiu_sk);
	print_student(S, pazymiu_sk);
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
