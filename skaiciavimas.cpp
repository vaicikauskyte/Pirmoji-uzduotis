#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <iterator>
#include <fstream>
#include "skaiciavimas.h"
#include "spausdinimas.h"
#include "skaitymas.h"
#include "ivedimas.h"
#include "studentai.h"
int generate_random_mark() //sugeneruoja atsitiktini pazymi nuo 1 iki 10
{
    srand(time(NULL));
    return rand() % 10 + 1;
}
float count_median(vector<int> paz)
{
    int sk = 0;
    for (int i = 0; i < 10; i++)
    {
        if (paz[i] != 0) {
            sk++;
        }
        if (paz[i] == -1) {
            paz[i] = 0;
            sk--;
            break;
        }
    }
    if (sk % 2 == 0)
    {
        return float(((paz[sk / 2 - 1]) + (paz[sk / 2])) / 2.);
    }
    else
    {
        return float(paz[sk / 2]);
    }
}
unsigned int countWordsInString(string const& str) {
    stringstream stream(str);
    return distance(istream_iterator<string>(stream), istream_iterator<string>());
}