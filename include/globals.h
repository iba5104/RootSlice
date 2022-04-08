#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include <string>
#include <vector>
#include <stdlib.h>
#include "tinyxml.h"

using namespace std;

class globals
{
private:
	static vector<string> allFileNames;
	static string outputFolderPrefix;
public:
	static void addToFileNamesVector(string filename);
	static void resetFileNameList();
	static void setFolderName(string folderName);
	static string getFolderName();
	static void writePVDFile(string pvdFileName);
	static int setUResolution;
	static int setVResolution;
	static int setWResolution;
	static double baseRadius;
	static double thickness;
	static double initZPosition;
	static double totalHeight;
	static double rcaRatio;
	static double vectorNum;
	static double corticalCellMultiplyRatio;
	static double cortexRadiusInput;
	static int corticalAddRadiusDBSelectInput;
	static int corticalCellNumSelectInput;

	const char* type_scleren	= "sclerenchyma";
	const char* type_epi		= "epidermis";
	const char* type_endo		= "endodermis";
	const char* type_peri		= "pericycle";
	const char* type_exo		= "exodermis";
	const char* type_cortical	= "cortical";

	double cellWallWidth;
	double plasmaMembraneThickness;
	double gapCytoTono;
	double gapCellWall;
	double variationRatio;
	int minSlice;
	int maxSlice;
	vector<double> cellDiameter;
	int numFiles;

	double innestCellDiameter;
	int innerLayerNum;

	double verticalLengthThresholdRatio;
	double tangentRingRadiusRatio;
	int steleCellNumBetween;
	int num;
	double averageRingRadius;
	int surroundingCellRingNum;

	double gapRadius;
	double surroundingCellRingRadius;

	int cellNum;

	double hydraulicConductance;
	double reflectionCoeffecient;
	double waterPressureDiff;
	double osmoticPressureDiff;
	double radialConductivity;
	double pressurePotentialSurface;
	double pressurePotentialXylem;
	double effectiveReflectionCoefficient;
	double osmoticPotentialSurface;
	double osmoticPotentialXylem;

	int dotNum;
	int setUpRowNum;
	int setDownRowNum;

	double setUpAppendParallelLengthThresholdRatio;

	string nutriName;
	vector<double> simTimes;
	vector<double> initialConcentration;
	double V_max;
	double k_m;
	double surfaceConcentration;
	double surface_epi_permeability;
	double permeability;
	double utilisation;
	double plasmodesmaRadius;

	struct CellData {
		int ID;
		double x, y, z, radius, distanceCenter, height, Conc;
		vector<int> neighbours;
		string type;
	};
};
#endif // GLOBALS_H_INCLUDED