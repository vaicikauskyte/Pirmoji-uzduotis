#include "logic.h"
#include <algorithm>

float count_median(std::vector<int> pazymiai, int egzas) //funkcija suskaiciuoja mediana
{
	pazymiai.push_back(egzas);
	int size = pazymiai.size() - 1;

	try {
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
	catch (std::exception& e) {
		return 0;
	}
}