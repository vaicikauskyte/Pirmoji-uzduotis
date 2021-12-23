#include <string>
#include <vector>

struct studentas {
	std::string Vard, Pav;
	std::vector<int> paz = { 0 };
	int egz;
	float GP = 0;

	bool operator < (const studentas& duom) const
	{
		if (Vard == duom.Vard) {
			return (Pav < duom.Pav);
		}
		return (Vard < duom.Vard);
	}
};