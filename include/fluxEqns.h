#ifndef FLUXEQNS_H_INCLUDED
#define FLUXEQNS_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <chrono>
#include <cmath>
#include <stdexcept>
#include "globals.h"
#include <map>
#include <rsSourceDermisDB.h>
#include <rsSourceCorticalDB.h>

#include "LSODA.h"
#include "helper.h"

using namespace std;

class fluxEqns : public globals
{
public:

	double flowRate(
		double hydraulicConductance,
		double reflectionCoeffecient,
		double waterPressureDiff,
		double osmoticPressureDiff);

	double waterFlux(
		double radialConductivity,
		double pressurePotentialSurface,
		double pressurePotentialXylem,
		double reflectionCoefficient,
		double osmoticPotentialSurface,
		double osmoticPotentialXylem
	);
	int cyto_pi( globals phosVals, vector<CellData> allCells, double epiExternalSurfaceArea, map<double, vector<double>> &result);
};

#endif