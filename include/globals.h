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

	double cellWallWidth;
	double plasmaMembraneThickness;
	double gapCytoTono;
	double gapCellWall;
	double variationRatio;
	int minSlice;
	int maxSlice;
	double cellDiameter;
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
};
#endif // GLOBALS_H_INCLUDED