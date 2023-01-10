#ifndef RESOURCES_H_INCLUDED
#define RESOURCES_H_INCLUDED

#include <string>
#include <vector>
#include <stdlib.h>
#include "tinyxml.h"

#include "viStringTokenizer.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include "globals.h"
#include <rsSourceCorticalDB.h>
#include <rsSourceDermisDB.h>
#include <numeric>
#include <cstdarg>
#include <unordered_map>

using namespace std;

class rsBaseFunctions : public globals
{
private:
public:
	vector<CellData> allCells;
	void CombineAllDBs(rsSourceCorticalDB* RsSourceCorticalDB, int numDermis, ...);
};
#endif // GLOBALS_H_INCLUDED