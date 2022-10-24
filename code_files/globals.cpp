#include "globals.h"

vector<string> globals::allFileNames;
string globals::outputFolderPrefix;

int globals::setUResolution = 12;
int globals::setVResolution = 12;
int globals::setWResolution = 12;
double globals::initZPosition = -225;
double globals::vectorNum = 200;
double globals::corticalCellMultiplyRatio = 0.1;
double globals::cortexRadiusInput = 0;
int globals::corticalAddRadiusDBSelectInput = 1;
int globals::corticalCellNumSelectInput = 1;
double globals::baseRadius = 0;
double globals::thickness = 0;
double globals::totalHeight = 0;
double globals::rcaRatio = 0;
bool globals::type_dicot = false;

/// Cortical
vector<double> corticalAddRadiusInputData;
vector<int> corticalCellNumInputData;
int corticalAddRadiusDBSelectInput;

/// Sclerenchyma
double sclerenAddRadiusData;

void globals::addToFileNamesVector(string filename)
{
	globals::allFileNames.push_back(filename);
}

void globals::resetFileNameList()
{
	globals::allFileNames.clear();
}

void globals::setFolderName(string folderName)
{
	globals::outputFolderPrefix = folderName+"/";
}

string globals::getFolderName()
{
	return globals::outputFolderPrefix;
}

void globals::writePVDFile(string pvdFileName)
{
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);
	TiXmlElement* elementVTK = new TiXmlElement("VTKFile");
	doc.LinkEndChild(elementVTK);
	elementVTK->SetAttribute("type", "Collection");
	elementVTK->SetAttribute("version", "0.1");
	TiXmlElement* elementCollection = new TiXmlElement("Collection");
	elementVTK->LinkEndChild(elementCollection);
	int numFileNames = globals::allFileNames.size();
	for (int i = 0; i < numFileNames; i++)
	{
		const char* vtpFileName = globals::allFileNames.at(i).c_str();
		TiXmlElement* elementDataSet = new TiXmlElement("DataSet");
		elementCollection->LinkEndChild(elementDataSet);
		elementDataSet->SetAttribute("part", i);
		elementDataSet->SetAttribute("file", vtpFileName);
	}
	pvdFileName = globals::getFolderName() + pvdFileName;
	doc.SaveFile(pvdFileName.c_str());
}