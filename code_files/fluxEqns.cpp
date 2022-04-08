#define _USE_MATH_DEFINES

#include "fluxEqns.h"

double fluxEqns::flowRate(double hydraulicConductance, double reflectionCoeffecient, double waterPressureDiff, double osmoticPressureDiff)
{
	double localFlowRate = hydraulicConductance * (waterPressureDiff + (reflectionCoeffecient * osmoticPressureDiff));
	return localFlowRate;
}

double fluxEqns::waterFlux(double radialConductivity, 
	double pressurePotentialSurface, 
	double pressurePotentialXylem, 
	double effectiveReflectionCoefficient,
	double osmoticPotentialSurface, 
	double osmoticPotentialXylem)
{
	double waterFluxCal = radialConductivity * (pressurePotentialSurface - pressurePotentialXylem +
		effectiveReflectionCoefficient * (osmoticPotentialSurface - osmoticPotentialXylem));
	return waterFluxCal;
}

static void system_cyto_pi(double t, double* y, double* ydot, void* data)
{
    (void)t;
    auto* temp = reinterpret_cast<vector<double>*>(data);
    (void)data;

    double Vol_cell                 = (*temp)[0];
    double epiExternalSurfaceArea   = (*temp)[1];
    double V_max                    = (*temp)[2];
    double phosphateExternal        = (*temp)[3];
    double k_m                      = (*temp)[4];
    double surfacePerm              = (*temp)[5];
    double phosphatePerm            = (*temp)[6];
    double adjSurfaceArea           = (*temp)[7];
    double U                        = (*temp)[8];
    double cytoPi1                  = (*temp)[9];
    double cytoPi2                  = (*temp)[10];
    double isEpiCell                = (*temp)[11];
    
    ydot[0] = ((isEpiCell) * (1 / Vol_cell) * epiExternalSurfaceArea * (((V_max * phosphateExternal) / (k_m + phosphateExternal)) + (surfacePerm * phosphateExternal)))
                + ((1 - isEpiCell) * (1 / Vol_cell) * adjSurfaceArea * phosphatePerm * (cytoPi1 - y[0]))
                - ((1 / Vol_cell) * adjSurfaceArea * phosphatePerm * (cytoPi2 - y[0])) - (U * y[0]);
}

int fluxEqns::cyto_pi( globals phosVals, vector<CellData> allCells, double epiExternalSurfaceArea, map<double, vector<double>> &result)
{
    cout << "Phosphorous Concentration calc" << endl;
    int totalCells = allCells.size();
    vector<double> y(totalCells, phosVals.initialConcentration[0]);
    if (phosVals.initialConcentration.size() == totalCells) {
        vector<double> y = phosVals.initialConcentration;
    }
    for (int cellID = 0; cellID < y.size(); cellID++) {
        allCells[cellID].Conc = y[cellID];
    }

    LSODA lsoda;

    /// declare int;
    int i;
    
    vector<double> concentrations;

    double t = phosVals.simTimes[0];
    double tmax = phosVals.simTimes[1];
    double tstep = 1;
    if (phosVals.simTimes.size() == 3)
        tstep = phosVals.simTimes[2];

    result.insert(pair<double, vector<double>>(t, y));

    while (t < tmax) {
        double tout = t + tstep;
        vector<CellData>::iterator curCell;
        for (curCell = allCells.begin(), i=0; curCell < allCells.end(); curCell++, i++) {
            vector<double> yout;
            vector<double> data;
            int istate = 1;
            (*curCell).Conc = y[i];
            double Vol_cell = M_PI * pow((*curCell).radius, 2) * (*curCell).height;
            double cytoPi1 = (*curCell).Conc,
                   cytoPi2 = (*curCell).Conc,
                   adjSurfaceArea = 0.0;
            for (int nbrCnt = 0; nbrCnt < (*curCell).neighbours.size(); nbrCnt++) {
                int nbrID = (*curCell).neighbours[nbrCnt];
                adjSurfaceArea = M_PI * pow(phosVals.plasmodesmaRadius, 2);
                if (allCells[nbrID].ID == nbrID) {
                    if ((*curCell).Conc > allCells[nbrID].Conc) {
                        cytoPi2 = allCells[nbrID].Conc;
                    }
                    else {
                        cytoPi1 = allCells[nbrID].Conc;
                    }
                }
            }
            data.push_back(Vol_cell);
            data.push_back(epiExternalSurfaceArea);
            data.push_back(phosVals.V_max);
            data.push_back(phosVals.surfaceConcentration);
            data.push_back(phosVals.k_m);
            data.push_back(phosVals.surface_epi_permeability);
            data.push_back(phosVals.permeability);
            data.push_back(adjSurfaceArea);
            data.push_back(phosVals.utilisation);
            data.push_back(cytoPi1);
            data.push_back(cytoPi2);
            if ((*curCell).type == type_epi)
                data.push_back(1.0);
            else
                data.push_back(0.0);

            vector<double> tempY = { y[i] };
            lsoda.lsoda_update(system_cyto_pi, 1, tempY, yout, &t, tout, &istate, &data);
            if (istate <= 0) {
                cerr << "error istate = " << istate << endl;
                exit(0);
            }
            y[i] = yout[1];
            t = result.rbegin()->first;
        }
        result.insert(pair<double, vector<double> >(tout, y));
        t = tout;
    }
    return 0;
}
